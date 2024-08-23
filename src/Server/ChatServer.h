#pragma once

#include <Windows.h>
#include "TCPServer.h"

class ChatServer
{

public:

	enum class Color
	{
		Default = 7,
		Blue = 9,
		Green = 10
	};

	ChatServer();

	bool Start();
	void Listen();
	void Send();
	void Receive();
	void Stop();

private:

	bool isChatRunning;
	HANDLE consoleHandle;
	TCPServer server;

};