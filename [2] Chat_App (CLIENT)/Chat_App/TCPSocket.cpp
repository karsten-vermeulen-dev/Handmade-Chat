#include <iostream>
#include "TCPSocket.h"

//------------------------------------------------------------------------------------------------------
//constructor that assigns all default values
//------------------------------------------------------------------------------------------------------
TCPSocket::TCPSocket()
{

	m_IP = { 0, 0 };
	m_socket = nullptr;

}
//------------------------------------------------------------------------------------------------------
//function that sets up the SDL, the networking sub-system and the server/client 
//------------------------------------------------------------------------------------------------------
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

	if (SDLNet_ResolveHost(&m_IP, ipAddress, port) == -1)
	{
		std::cout << "Could not resolve IP address." << std::endl << std::endl;
		return false;
	}

	return true;

}
//------------------------------------------------------------------------------------------------------
//function that opens up a connection socket using resolved IP and port number 
//------------------------------------------------------------------------------------------------------
bool TCPSocket::Open()
{

	m_socket = SDLNet_TCP_Open(&m_IP);

	if (!m_socket)
	{
		std::cout << "Could not open socket connection." << std::endl << std::endl;
		return false;
	}

	return true;

}
//------------------------------------------------------------------------------------------------------
//function that closes down a connection socket 
//------------------------------------------------------------------------------------------------------
void TCPSocket::Close()
{

	//close down socket connection if it hasn't already been done
	if (!m_socket)
	{
		std::cout << "Invalid socket. Socket may already be closed." << std::endl << std::endl;
	}

	else
	{
		SDLNet_TCP_Close(m_socket);
		m_socket = nullptr;
	}

}
//------------------------------------------------------------------------------------------------------
//function that closes down SDL and the networking sub-system
//------------------------------------------------------------------------------------------------------
void TCPSocket::ShutDown()
{

	SDLNet_Quit();
	SDL_Quit();

}