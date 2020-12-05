#include "ClientStub.h"

ClientStub::ClientStub() {}

int ClientStub::Init(std::string ip, int port) {
	return socket.Init(ip, port);
}

RobotInfo ClientStub::OrderRobot(RobotOrder order) {
	RobotInfo info;
	char buffer[32];
	int size;
	order.Marshal(buffer);
	size = order.Size();
	if (socket.Send(buffer, size, 0)) {
		size = info.Size();
		if (socket.Recv(buffer, size, 0)) {
			info.Unmarshal(buffer);
		}
	}
	return info;
}

RobotInfo ClientStub::Order(CustomerRequest request) {
	RobotInfo info;
	char buffer[32];
	int size;
	request.Marshal(buffer);
	size = request.Size();
	if (socket.Send(buffer, size, 0)) {
		size = info.Size();
		if (socket.Recv(buffer, size, 0)) {
			info.Unmarshal(buffer);
		}
	}
	return info;
}

CustomerRecord ClientStub::ReadRecord(CustomerRequest request) {
	CustomerRecord info;
	char buffer[32];
	int size;
	request.Marshal(buffer);
	size = request.Size();
	if (socket.Send(buffer, size, 0)) {
		size = info.Size();
		if (socket.Recv(buffer, size, 0)) {
			info.Unmarshal(buffer);
		}
	}
	return info;
}

Status ClientStub::SendUpdate(Protocol protocol) {
	Status info;
	char buffer[32];
	int size;
	protocol.Marshal(buffer);
	size = protocol.Size();
	if (socket.Send(buffer, size, 0)) {
		size = info.Size();
		if (socket.Recv(buffer, size, 0)) {
			info.Unmarshal(buffer);
		}
	}
	return info;
}

int ClientStub::SendIdentity(Identity identity) {
	//Identity info;
	char buffer[32];
	int size;
	identity.Marshal(buffer);
	size = identity.Size();
	return socket.Send(buffer, size, 0);
	// if (socket.Send(buffer, size, 0)) {
	// 	// size = info.Size();
	// 	// if (socket.Recv(buffer, size, 0)) {
	// 	// 	info.Unmarshal(buffer);
	// 	// }
	// 	//identity.Print();
	// }
	//return info;
}

void ClientStub::CloseStub() {
	socket.Close();
}
