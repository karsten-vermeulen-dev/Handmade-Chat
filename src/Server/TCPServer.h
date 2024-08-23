#pragma once

#include <map>
#include <string>
#include <SDL_net.h>
#include "TCPSocket.h"

class TCPServer : public TCPSocket
{

public:

	TCPServer();

	bool Listen();
	bool Send(const std::string& message);
	bool Receive(std::string& message);
	void Close();

private:

	TCPsocket clientSocket;

};