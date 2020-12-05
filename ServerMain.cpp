#include <chrono>
#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

#include "ServerSocket.h"
#include "ServerThread.h"

int main(int argc, char *argv[]) {
	int port;
	int primaryId;
	//int peers;

	int engineer_cnt = 0;
	int num_experts;
	ServerSocket socket;
	RobotFactory factory;
	std::unique_ptr<ServerSocket> new_socket;
	std::unique_ptr<ServerSocket> primary_socket;
	std::vector<std::thread> thread_vector;
	std::vector<std::string> nodes_vector;
	std::vector<int> port_vector;

	// if (argc < 3) {
	// 	std::cout << "not enough arguments" << std::endl;
	// 	std::cout << argv[0] << "[port #] [# experts]" << std::endl;
	// 	return 0;
	// }

	if ((argc-1) % 3 != 0) {
		std::cout << "not enough arguments" << std::endl;
		std::cout << argv[0] << "[port #] [# experts]" << std::endl;
		std::cout << "argc" << argc << std::endl;
		return 0;
	}

	port = atoi(argv[1]);
	primaryId = atoi(argv[2]);
	//peers = atoi(argv[3]);

	for (int i = 5; i <= argc; i = i+3) {
		//std::cout << argv[i] << std::endl;
		nodes_vector.push_back(std::move(argv[i]));
	}

	for (int i = 6; i <= argc; i = i+3) {
		port_vector.push_back(std::move(atoi(argv[i])));
	}

	//num_experts = atoi(argv[2]);
	num_experts = 1;

	for (int i = 0; i < num_experts; i++) {
		std::thread expert_thread(&RobotFactory::ExpertThread, &factory, port, primaryId, nodes_vector, port_vector, engineer_cnt++);
		thread_vector.push_back(std::move(expert_thread));
	}

	if (!socket.Init(port)) {
		std::cout << "Socket initialization failed" << std::endl;
		return 0;
	}

	while ((new_socket = socket.Accept())) {
		std::thread engineer_thread(&RobotFactory::EngineerThread, &factory,
				std::move(new_socket), engineer_cnt++);
		thread_vector.push_back(std::move(engineer_thread));
	}
	return 0;
}
