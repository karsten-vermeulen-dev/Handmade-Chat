#ifndef CHAT_CLIENT_H
#define CHAT_CLIENT_H

#include <string>
#include <Windows.h>
#include "TCPClient.h"

class ChatClient
{

public:

	enum class Color{ DEFAULT = 7, BLUE = 9, GREEN = 10};

public:

	ChatClient();

public:

	bool Start();
	void Send();
	void Receive();
	void Stop();

private:

	bool m_isChatRunning;
	std::string m_IPString;
	HANDLE m_consoleHandle;
	TCPClient m_client;

};

#endif