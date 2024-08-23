#ifndef TCP_SERVER_H
#define TCP_SERVER_H

#include <map>
#include <string>
#include <SDL_net.h>
#include "TCPSocket.h"

class TCPServer : public TCPSocket
{

public:

	TCPServer();

public:

	bool Listen();
	bool Send(const std::string& message);
	bool Receive(std::string& message);
	void Close();

private:

	TCPsocket m_clientSocket;

};

#endif