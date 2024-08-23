#include <iostream>
#include "TCPSocket.h"

//======================================================================================================
TCPSocket::TCPSocket()
{
	IP = { 0, 0 };
	socket = nullptr;
}
//======================================================================================================
bool TCPSocket::Initialize(Uint16 port, const char* ipAddress)
{

	if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
	{
		std::cout << "SDL did not initialize properly." << std::endl << std::endl;
		return false;
	}

	if (SDLNet_Init() == -1)
	{
		std::cout << "Networking sub-system did not initialize properly." << std::endl << std::endl;
		return false;
	}

	if (SDLNet_ResolveHost(&IP, ipAddress, port) == -1)
	{
		std::cout << "Could not resolve IP address." << std::endl << std::endl;
		return false;
	}

	return true;
}
//======================================================================================================
bool TCPSocket::Open()
{
	//Open a connection socket using resolved IP and port number
	socket = SDLNet_TCP_Open(&IP);

	if (!socket)
	{
		std::cout << "Could not open socket connection." << std::endl << std::endl;
		return false;
	}

	return true;
}
//======================================================================================================
void TCPSocket::Close()
{
	//Close down socket connection if it hasn't already been done
	if (!socket)
	{
		std::cout << "Invalid socket. Socket may already be closed." << std::endl << std::endl;
	}

	else
	{
		SDLNet_TCP_Close(socket);
		socket = nullptr;
	}
}
//======================================================================================================
void TCPSocket::ShutDown()
{
	SDLNet_Quit();
	SDL_Quit();
}