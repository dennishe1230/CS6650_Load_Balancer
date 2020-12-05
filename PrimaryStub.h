#ifndef __PRIMARY_STUB_H__
#define __PRIMARY_STUB_H__

#include <string>

#include "DualSocket.h"
#include "Messages.h"

class PrimaryStub {
private:
  DualSocket socket;
  int activeCode;
  std::string ip;
  int port;
public:
  PrimaryStub();
  int Init(std::string ip, int port);
  Status SendUpdate(Protocol protocol);
  int SendIdentity(Identity identity);
  void SetActiveCode(int activeCode);
  int GetActiveCode();
  void SetIp(std::string ipAddress);
  std::string GetIp();
  void SetPort(int portNum);
  int GetPort();
};

#endif // end of #ifndef __PRIMARY_STUB_H__
