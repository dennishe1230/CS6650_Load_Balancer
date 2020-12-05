#ifndef __SERVER_STUB_H__
#define __SERVER_STUB_H__

#include <memory>

#include "ServerSocket.h"
#include "Messages.h"

class ServerStub {
private:
	std::unique_ptr<ServerSocket> socket;
public:
	ServerStub();
	void Init(std::unique_ptr<ServerSocket> socket);
	//RobotOrder ReceiveOrder();
	CustomerRequest ReceiveRequest();
	Protocol ReceiveProtocol();
	Identity ReceiveIdentity();
	int ShipRobot(RobotInfo info);
	int ReturnRecord(CustomerRecord record);
	int SendStatus(Status status);
	void CloseStub();
};

#endif // end of #ifndef __SERVER_STUB_H__
