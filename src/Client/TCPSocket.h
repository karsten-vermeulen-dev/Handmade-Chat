#pragma once

#include <string>
#include <SDL.h>
#include <SDL_net.h>

class TCPSocket
{

public:

	TCPSocket();

	bool Initialize(Uint16 port, const char* ipAddress = nullptr);
	bool Open();
	void Close();
	void ShutDown();

protected:

	IPaddress IP;
	TCPsocket socket;

};