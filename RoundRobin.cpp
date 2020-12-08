#include "RoundRobin.h"
#include <algorithm>
int RoundRobin::getGcd(int a, int b) {
    int c = 0;
    while(b>0) {
        c = b;
        b = a%b;
        a = c;
    }
    return a;
}

int RoundRobin::getMaxGcd() {
    int res = server[0].weight;
    int curMax=0, curMin=0;
    for (size_t i = 0; i < server.size(); i++)
    {
        curMax = int(std::max(res, server[i].weight));
        curMin = int(std::min(float(res), float(server[i].weight)));
        res = getGcd(curMax, curMin);
    }

    return res;
}

int RoundRobin::getMaxWeight() {
    int max = 0;
    for (size_t i = 0; i < server.size(); i++) {
        if (server[i].weight > max) {
            max = server[i].weight;
        }
    }

    return max;
}

int RoundRobin::getSelectServer(srv_info* serverInfo, int serverNum, int maxGcd, int maxWeight, int *curWeight, int *serverIndex) {
    while (true) {
        *serverIndex = (*serverIndex + 1) % serverNum;
        if (*serverIndex == 0) {
            *curWeight = *curWeight - maxGcd;
            if (*curWeight <= 0) {
                *curWeight = maxWeight;
                if (*curWeight == 0) {
                    return -1;
                }
            }
        }

        if (server[*serverIndex].weight >= *curWeight) {
            serverInfo->weight = server[*serverIndex].weight;
            memcpy(serverInfo->ip, server[*serverIndex].ip, BUFFER_SIZE);
            return *serverIndex;
        }
    }
}
