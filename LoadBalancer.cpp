//
// Created by Yanchi on 2020/12/7.
//
#include "RoundRobin.h"
#include "ServerSocket.h"
#include <iostream>
int main(int argc, char *argv[]) {
    if (argc <= 2) {
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
    int retIndex = -1;
    int count = 0;
    std::map<int,int> mapIndex2Count;
    std::map<int, int>::iterator iter;
    int curWeight = 0;
    int serverIndex = -1;

    if (!socket.Init(port)){
        std::cout << "server initialization failed" << std::endl;
        return -1;
    }

    while ((new_socket = socket.Accept())){
        int srv_idx = rr.getSelectServer(&serverInfo, num_srvs, maxGcd, maxWeight, &curWeight, &serverIndex);
        //todo: add load balancer thread to receive requests from client and distribute requests


        iter = mapIndex2Count.find(retIndex);
        if (iter != mapIndex2Count.end()) {
            count = mapIndex2Count[retIndex];
            mapIndex2Count[retIndex] = ++count;
        } else {
            mapIndex2Count[retIndex] = 1;
        }

    }




    return 0;
}
