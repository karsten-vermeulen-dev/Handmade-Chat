#pragma once

#include <string>
#include "TCPSocket.h"

class TCPClient : public TCPSocket
{

public:

	bool Send(const std::string& message);
	bool Receive(std::string& message);
	
};