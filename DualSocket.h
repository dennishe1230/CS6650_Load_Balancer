#ifndef __DUALSOCKET_H__
#define __DUALSOCKET_H__

#include <string>

#include "Socket.h"


class DualSocket: public Socket {
public:
	DualSocket() {}
	~DualSocket() {}

	int Init(std::string ip, int port);
};


#endif // end of #ifndef __DUALSOCKET_H__
