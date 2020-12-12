#include "RoundRobin.h"
#include "ServerSocket.h"
#include "ServerStub.h"
#include "ClientStub.h"
#include <iostream>
int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cout << "arguments not enough" << std::endl;
    }
    int num_srvs = atoi(argv[1]);
    int port = atoi(argv[2]);
    RoundRobin rr;
    for (int i = 0; i < num_srvs; i++){
        char* ip = argv[i + 3];
        srv_info srvInfo;
        srvInfo.ip = ip;
        srvInfo.weight = i;
        rr.server.push_back(srvInfo);
    }
    std::unique_ptr<ServerSocket> new_socket;
    ServerSocket socket;
    int maxGcd = rr.getMaxGcd();
    int maxWeight = rr.getMaxWeight();

    srv_info serverInfo;
//    int retIndex = -1;
//    int count = 0;
//    std::map<int,int> mapIndex2Count;
//    std::map<int, int>::iterator iter;
    int curWeight = 0;
    int serverIndex = -1;

    if (!socket.Init(port)){
        std::cout << "server initialization failed" << std::endl;
        return -1;
    }

    while ((new_socket = socket.Accept())){
        ServerStub serverStub;
        ClientStub clientStub;

        serverStub.Init(std::move(new_socket));
        CustomerRequest request = serverStub.ReceiveRequest();

        int srv_idx = rr.getSelectServer(&serverInfo, num_srvs, maxGcd, maxWeight, &curWeight, &serverIndex);
        srv_info target_srv = rr.server[srv_idx];

        clientStub.Init(target_srv.ip, 12345);
        RobotInfo robotInfo = clientStub.Order(request);

        serverStub.ShipRobot(robotInfo);

    }

}
