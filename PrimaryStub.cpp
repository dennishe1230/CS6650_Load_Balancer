#include "PrimaryStub.h"

PrimaryStub::PrimaryStub() {
	activeCode = 0;
	ip = "";
	port = 0;
}

int PrimaryStub::Init(std::string ip, int port) {
	return socket.Init(ip, port);
}

Status PrimaryStub::SendUpdate(Protocol protocol) {
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

int PrimaryStub::SendIdentity(Identity identity) {
	char buffer[32];
	int size;
	identity.Marshal(buffer);
	size = identity.Size();
	return socket.Send(buffer, size, 0);
}

void PrimaryStub::SetActiveCode(int code) {
	activeCode = code;
}

int PrimaryStub::GetActiveCode() {
	return activeCode;
}

void PrimaryStub::SetIp(std::string ipAddress) {
	ip = ipAddress;
}

std::string PrimaryStub::GetIp() {
	return ip;
}

void PrimaryStub::SetPort(int portNum) {
	port = portNum;
}

int PrimaryStub::GetPort() {
	return port;
}
