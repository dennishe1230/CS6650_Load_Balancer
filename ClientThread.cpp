#include "ClientThread.h"
#include "Messages.h"

#include <iostream>

ClientThreadClass::ClientThreadClass() {}

void ClientThreadClass::ThreadBody(std::string ip, int port, int id, int orders, int type) {
	customer_id = id;
	num_orders = orders;
	request_type = type;
	if (!stub.Init(ip, port)) {
		std::cout << "Thread " << customer_id << " failed to connect" << std::endl;
		return;
	}

	Identity identity;
	identity.SetIdentity(0);
	int check = stub.SendIdentity(identity);
	if (check == -1) {
		return;
	}

	if (request_type == 3) {
		CustomerRequest req;
		CustomerRecord rec;
		for (int i = 0; i < num_orders; i++) {
			req.SetRequest(i, -1, 2);
			rec = stub.ReadRecord(req);
			if (rec.GetCustomerId() != -1) {
				rec.Print();
				// std::cout << "Invalid record " << customer_id << std::endl;
				// break;
			}
		}
	}

	for (int i = 0; i < num_orders; i++) {
		//RobotOrder order;
		CustomerRequest request;
		RobotInfo robot;
		CustomerRecord record;
		//order.SetOrder(customer_id, i, request_type);
		request.SetRequest(customer_id, i, request_type);

		timer.Start();
		// check if the request type is and order or ReadRecord
		if (request_type == 1) {
			robot = stub.Order(request);
			if (!robot.IsValid()) {
				//std::cout << "Invalid robot " << customer_id << std::endl;
				break;
			} else {
				//robot.Print();
			}
		}
		else if (request_type == 2) {
			record = stub.ReadRecord(request);
			if (!record.IsValid()) {
				//std::cout << "Invalid record " << customer_id << std::endl;
				break;
			} else {
				//record.Print();
			}
		}
		//robot = stub.OrderRobot(order);
		timer.EndAndMerge();

		// if (!robot.IsValid()) {
		// 	std::cout << "Invalid robot " << customer_id << std::endl;
		// 	break;
		// }
		//
		// if (!record.IsValid()) {
		// 	std::cout << "Invalid record " << customer_id << std::endl;
		// 	break;
		// }
	}
}

ClientTimer ClientThreadClass::GetTimer() {
	return timer;
}
