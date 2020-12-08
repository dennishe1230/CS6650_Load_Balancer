#ifndef CS6650_LOAD_BALANCER_ROUNDROBIN_H
#define CS6650_LOAD_BALANCER_ROUNDROBIN_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>

#include <map>
#define BUFFER_SIZE 1024

struct srv_info {
    srv_info() {
        ip  = new char[BUFFER_SIZE];
        weight = 0;
    }

    char* ip;
    int weight;
};

class RoundRobin {
public:
    static std::vector<srv_info> server;
    int getGcd(int a, int b);
    int getMaxGcd();
    int getMaxWeight();
    int getSelectServer(srv_info* serverInfo, int serverNum, int maxGcd, int maxWeight, int *curWeight,int *serverIndex); //轮询调度
};


#endif //CS6650_LOAD_BALANCER_ROUNDROBIN_H
