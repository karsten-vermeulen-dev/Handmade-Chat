#ifndef TCP_CLIENT_H
#define TCP_CLIENT_H

#include <string>
#include "TCPSocket.h"

class TCPClient : public TCPSocket
{

public:

	bool Send(const std::string& message);
	bool Receive(std::string& message);
	
};

#endif