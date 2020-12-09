#include <iostream>
#include <memory>

#include "ServerThread.h"
#include "ServerStub.h"
#include "PrimaryStub.h"
#include "Messages.h"

RobotInfo RobotFactory::CreateRegularRobot(CustomerRequest request, int engineer_id) {
	RobotInfo robot;
	//robot.CopyOrder(order);
	robot.CopyRequest(request);
	robot.SetEngineerId(engineer_id);
	//robot.SetAdminId(-1);

	std::promise<RobotInfo> prom;
	std::future<RobotInfo> fut = prom.get_future();

	std::unique_ptr<ExpertRequest> req = std::unique_ptr<ExpertRequest>(new ExpertRequest);

	req->robot = robot;
	req->prom = std::move(prom);

	erq_lock.lock();
	erq.push(std::move(req));
	erq_cv.notify_one();
	erq_lock.unlock();

	robot = fut.get();

	return robot;
}

CustomerRecord RobotFactory::GetCustomerRecord(CustomerRequest request) {
	CustomerRecord record;
	record.setCustomerId(request.GetCustomerId());

	if (customer_record.count(record.GetCustomerId()) > 0) {
		record.setOrderNumber(customer_record[request.GetCustomerId()]);
	} else {
		record.setCustomerId(-1);
		record.setOrderNumber(-1);
	}
	return record;
}

void RobotFactory::NodeThread(std::unique_ptr<ServerSocket> socket, int engineerId, int serverId) {
  CustomerRequest request;
	RobotInfo robot;

	ServerStub stub;
	stub.Init(std::move(socket));

	while (true) {
		request = stub.ReceiveRequest();

		if (!request.IsValid()) {
			break;
		}

		robot.CopyRequest(request);
		robot.SetEngineerId(engineerId);
		robot.SetAdminId(serverId); // using serverId here

		robot = CreateRegularRobot(request, engineerId);
		robot.Print();
		stub.ShipRobot(robot);
	}
}

void RobotFactory::EngineerThread(std::unique_ptr<ServerSocket> socket, int id) {
	int engineer_id = id;
	//int robot_type;
	//RobotOrder order;
	int request_type;
	CustomerRequest request;
	RobotInfo robot;
	CustomerRecord record;
	Protocol protocol;
	Status status;
	Identity identity;

	ServerStub stub;

	stub.Init(std::move(socket));
	identity = stub.ReceiveIdentity();

	while (true) {
		if (identity.GetIdentityCode() == 0) {
			request = stub.ReceiveRequest();
			//request.Print();
			if (!request.IsValid()) {
				break;
			}

			request_type = request.GetRequestType();
			switch (request_type) {
				case 1:
					// check if I am the PFA, if not then I am the NEW PFA
					if (myId != primaryNode) {
						std::unique_lock<std::mutex> ul(erq_lock, std::defer_lock);
						ul.lock();
						//since my map lags the old PFA by 1 logged MAPOP, add it myself and increment commitedIndex
						customer_record[smr_log.back().arg1] = smr_log.back().arg2;
						committedIndex++;
						ul.unlock();
					}

					robot = CreateRegularRobot(request, engineer_id);
					//robot.Print();
					stub.ShipRobot(robot);
					break;
				case 2:
					//robot = CreateSpecialRobot(request, engineer_id);
					record = GetCustomerRecord(request);
					stub.ReturnRecord(record);
					break;
				default:
					std::cout << "Undefined request type: "
						<< request_type << std::endl;
			}
		} // Client Request

		else if (identity.GetIdentityCode() == 1) {
			protocol = stub.ReceiveProtocol();
			//protocol.Print();
			if (!protocol.IsValid()) {
				break;
			}
			// Set primary id / add MapOp to smr_log / increment last index;
			primaryNode = protocol.GetFactoryId();
			MapOp log;
			MapOp *log_prt = &log;
			log_prt->opcode = 1;
			log_prt->arg1 = protocol.GetArg1(); // key
			log_prt->arg2 = protocol.GetArg2(); // value
			smr_log.push_back(*log_prt);
			lastIndex = protocol.GetLastIndex();

			if (protocol.GetCommitedIndex() != -1) {
				int index = protocol.GetCommitedIndex();
				//applies the logged operation to the customer record map
				customer_record[smr_log[index].arg1] = smr_log[index].arg2;
				committedIndex = index;
			}

			// std::cout << "last index: " << lastIndex << std::endl;
			// std::cout << "commitedIndex index: " << committedIndex << std::endl;

			status.SetStatus(0);
			int result = stub.SendStatus(status);
			if (result == 0) {
				primaryNode = -1;
				std::cout << "Could not send back status bc primary failed" << std::endl;
			}
			//std::cout << "Sent back status" << std::endl;
		} // PFA Protocol

	} // end while
}

void RobotFactory::ExpertThread(int port, int primaryId, std::vector<std::string> nodes_vector, std::vector<int> port_vector, int id) {
	std::unique_lock<std::mutex> ul(erq_lock, std::defer_lock);
	while (true) {
		ul.lock();

		if (erq.empty()) {
			// Check if failed nodes came back live if so give all MapOp
			// if (failedNodes.size() != 0) {
			// 	Identity identity;
			// 	identity.SetIdentity(1);
			// 	for (size_t i = 0; i < failedNodes.size(); i++) {
			// 		auto pstub = failedNodes[i];
			// 		int connected = pstub->Init(pstub->GetIp(), pstub->GetPort());
			// 		if (connected) {
			// 			pstub->SetActiveCode(0);
			// 			failedNodes.erase(failedNodes.begin() + i);
			// 		}
			//
			// 		pstub->SendIdentity(identity);
			//
			// 		int tempLastIndex = -1;
			// 		int tempCommittedIndex = -1;
			// 		while (tempLastIndex < lastIndex) {
			// 			tempLastIndex++;
			// 			Protocol protocol;
			// 			protocol.SetProtocol(tempLastIndex, tempCommittedIndex, primaryId, smr_log[tempLastIndex].opcode, smr_log[tempLastIndex].arg1, smr_log[tempLastIndex].arg2);
			// 			tempCommittedIndex++;
			// 		}
			// 	}
			// }

			erq_cv.wait(ul, [this]{ return !erq.empty(); });
		}

		auto req = std::move(erq.front());
		erq.pop();

		//append necessary ooperation to update the customer record to the log
		MapOp log;
		MapOp *log_prt = &log;
		log_prt->opcode = 1;
		log_prt->arg1 = req->robot.GetCustomerId();
		log_prt->arg2 = req->robot.GetOrderNumber();
		smr_log.push_back(*log_prt);

		// initialize Ids and last index
		myId = primaryId;
		primaryNode = primaryId;
		lastIndex++;

		Identity identity;
		identity.SetIdentity(1);
		bool response = true;

		if (backupNodes.size() == 0) {
			for (size_t i = 0; i < nodes_vector.size(); i++) {
				auto pstub = std::shared_ptr<PrimaryStub>(new PrimaryStub());
				int connected = pstub->Init(nodes_vector[i], port_vector[i]);
				pstub->SetIp(nodes_vector[i]);
				pstub->SetPort(port_vector[i]);

				if (!connected) {
					pstub->SetActiveCode(-1);
					backupNodes.push_back(std::move(pstub));
					//failedNodes.push_back(std::move(pstub));
					continue;
				}

				pstub->SendIdentity(identity);

				Protocol protocol;
				protocol.SetProtocol(lastIndex, committedIndex, primaryId, log_prt->opcode, log_prt->arg1, log_prt->arg2);
				Status status = pstub->SendUpdate(protocol);

				// if any of this case occurs then the backup node failed
				// if (connected == 0 || identitySent == 0 || status.GetStatusCode() < 0) {
				// 	pstub->SetActiveCode(-1);
				// }

				response = response	&& status.GetStatusCode() == 0;

				backupNodes.push_back(std::move(pstub));
			}
		}
		else {
			for (auto& pstub : backupNodes) {
				if (pstub->GetActiveCode() == -1) {
					continue;
				}

				Protocol protocol;
				protocol.SetProtocol(lastIndex, committedIndex, primaryId, log_prt->opcode, log_prt->arg1, log_prt->arg2);
				Status status = pstub->SendUpdate(protocol);
				//status.Print();

				// backup node failed
				if (status.GetStatusCode() < 0) {
					pstub->SetActiveCode(-1);
					//failedNodes.push_back(std::move(pstub));
					continue;
				}

				response = response	&& status.GetStatusCode() == 0;
			}
		}

		if(!response) {
			std::cout << "Error replicating MapOp to backup nodes" << std::endl;
		}

		committedIndex++;
    // End

		//applies the logged operation to the customer record map
		customer_record[smr_log.back().arg1] = smr_log.back().arg2;

		// std::cout << "customer_id " << smr_log.back().arg1 << " Updating last order to "
		// << smr_log.back().arg2 << " Map value is " << customer_record[smr_log.back().arg1] << std::endl;

		ul.unlock();

		std::this_thread::sleep_for(std::chrono::microseconds(100));
		req->robot.SetAdminId(id);
		req->prom.set_value(req->robot);
	}
}
