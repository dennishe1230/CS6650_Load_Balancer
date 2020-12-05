#include "ServerStub.h"

ServerStub::ServerStub() {}

void ServerStub::Init(std::unique_ptr<ServerSocket> socket) {
	this->socket = std::move(socket);
}

// RobotOrder ServerStub::ReceiveOrder() {
// 	char buffer[32];
// 	RobotOrder order;
// 	if (socket->Recv(buffer, order.Size(), 0)) {
// 		order.Unmarshal(buffer);
// 	}
// 	return order;
// }

CustomerRequest ServerStub::ReceiveRequest() {
	char buffer[32];
	CustomerRequest request;
	if (socket->Recv(buffer, request.Size(), 0)) {
		request.Unmarshal(buffer);
	}
	return request;
}

Protocol ServerStub::ReceiveProtocol() {
	char buffer[32];
	Protocol protocol;
	if (socket->Recv(buffer, protocol.Size(), 0)) {
		protocol.Unmarshal(buffer);
	}
	return protocol;
}

Identity ServerStub::ReceiveIdentity() {
	char buffer[32];
	Identity identity;
	if (socket->Recv(buffer, identity.Size(), 0)) {
		identity.Unmarshal(buffer);
	}
	return identity;
}

int ServerStub::ShipRobot(RobotInfo info) {
	char buffer[32];
	info.Marshal(buffer);
	return socket->Send(buffer, info.Size(), 0);
}

int ServerStub::ReturnRecord(CustomerRecord record) {
	char buffer[32];
	record.Marshal(buffer);
	return socket->Send(buffer, record.Size(), 0);
}

int ServerStub::SendStatus(Status status) {
	char buffer[32];
	status.Marshal(buffer);
	return socket->Send(buffer, status.Size(), 0);
}

void ServerStub::CloseStub() {
	socket->Close();
}
