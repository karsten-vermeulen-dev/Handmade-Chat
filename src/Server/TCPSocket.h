#ifndef TCP_SOCKET_H
#define TCP_SOCKET_H

#include <string>
#include <SDL.h>
#include <SDL_net.h>

class TCPSocket
{

public:

	TCPSocket();

public:

	bool Initialize(Uint16 port, const char* ipAddress = nullptr);
	bool Open();
	void Close();
	void ShutDown();

protected:

	IPaddress m_IP;
	TCPsocket m_socket;

};

#endif 