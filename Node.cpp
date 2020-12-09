#include <chrono>
#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

#include "ServerSocket.h"
#include "ServerThread.h"


int main(int argc, char *argv[]) {
  // This program accepts 2 params: port number and serverNumber for identification
  int port;
  int serverId;
  ServerSocket socket;
  RobotFactory factory;
  std::unique_ptr<ServerSocket> new_socket;
  std::unique_ptr<ServerSocket> primary_socket;
  std::vector<std::thread> thread_vector;
  int engineer_cnt = 0;

  port = atoi(argv[1]);
  serverId = atoi(argv[2]);

  if (!socket.Init(port)) {
    std::cout << "Socket initialization failed" << std::endl;
    return 0;
  }

  while ((new_socket = socket.Accept())) {
    std::thread request_thread(&RobotFactory::NodeThread, &factory,
        std::move(new_socket), engineer_cnt++, serverId);
    thread_vector.push_back(std::move(request_thread));
  }
}
