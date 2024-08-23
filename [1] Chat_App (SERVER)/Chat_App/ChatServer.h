#ifndef CHAT_SERVER_H
#define CHAT_SERVER_H

#include <Windows.h>
#include "TCPServer.h"

class ChatServer
{

public:

	enum class Color{ DEFAULT = 7, BLUE = 9, GREEN = 10};

public:

	ChatServer();

public:

	bool Start();
	void Listen();
	void Send();
	void Receive();
	void Stop();

private:

	bool m_isChatRunning;
	HANDLE m_consoleHandle;
	TCPServer m_server;

};

#endif