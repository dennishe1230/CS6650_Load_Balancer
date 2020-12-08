#ifndef __SERVERTHREAD_H__
#define __SERVERTHREAD_H__

#include <condition_variable>
#include <future>
#include <mutex>
#include <queue>
#include <thread>
#include <map>

#include "Messages.h"
#include "ServerSocket.h"
#include "PrimaryStub.h"

struct ExpertRequest {
	RobotInfo robot;
	std::promise<RobotInfo> prom;
};

struct MapOp {
	int opcode;
	int arg1;
	int arg2;
};


class RobotFactory {
private:
	std::queue<std::unique_ptr<ExpertRequest>> erq;
	std::mutex erq_lock;
	std::condition_variable erq_cv;

	std::map<int, int> customer_record;
	std::vector<MapOp> smr_log;
	std::vector<std::shared_ptr<PrimaryStub>> backupNodes;
	std::vector<std::shared_ptr<PrimaryStub>> failedNodes;
	int lastIndex = -1;
	int committedIndex = -1;
	int myId = -1;
	int primaryNode = -1;

	RobotInfo CreateRegularRobot(CustomerRequest request, int engineer_id);
	RobotInfo CreateSpecialRobot(CustomerRequest request, int engineer_id);
	CustomerRecord GetCustomerRecord(CustomerRequest request);
public:
	void NodeThread(std::unique_ptr<ServerSocket> socket, int engineerId, int serverId);
	void EngineerThread(std::unique_ptr<ServerSocket> socket, int id);
	void ExpertThread(int port, int primaryId, std::vector<std::string> nodes_vector, std::vector<int> port_vector, int id);
};

#endif // end of #ifndef __SERVERTHREAD_H__
