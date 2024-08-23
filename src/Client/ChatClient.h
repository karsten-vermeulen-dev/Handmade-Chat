#pragma once

#include <string>
#include <Windows.h>
#include "TCPClient.h"

class ChatClient
{

public:

	enum class Color
	{ 
		Default = 7, 
		Blue = 9, 
		Green = 10
	};

	ChatClient();

	bool Start();
	void Send();
	void Receive();
	void Stop();

private:

	bool isChatRunning;
	std::string IPString;
	HANDLE consoleHandle;
	TCPClient client;

};