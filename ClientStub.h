#ifndef __CLIENT_STUB_H__
#define __CLIENT_STUB_H__

#include <string>

#include "DualSocket.h"
#include "Messages.h"

class ClientStub {
private:
	DualSocket socket;
public:
	ClientStub();
	int Init(std::string ip, int port);
	RobotInfo OrderRobot(RobotOrder order);
	RobotInfo Order(CustomerRequest request);
	CustomerRecord ReadRecord(CustomerRequest request);
	Status SendUpdate(Protocol protocol);
	int SendIdentity(Identity identity);
	void CloseStub();
};


#endif // end of #ifndef __CLIENT_STUB_H__
