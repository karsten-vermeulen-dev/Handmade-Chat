#include <iostream>
#include "TCPServer.h"

//------------------------------------------------------------------------------------------------------
//constructor that assigns all default values
//------------------------------------------------------------------------------------------------------
TCPServer::TCPServer()
{

	m_clientSocket = nullptr;

}
//------------------------------------------------------------------------------------------------------
//function that listens for an incoming client connection 
//------------------------------------------------------------------------------------------------------
bool TCPServer::Listen()
{

	TCPsocket tempSocket = nullptr;

	//first check if listening socket is still valid before continuing to accept 
	//we do this because the accept routine could crash if the socket is invalid!
	if (!m_socket)
	{
		std::cout << "Invalid socket. Cannot listen for connections." << std::endl << std::endl;
		return false;
	}

	//if client has connected, server will establish a connection and save it
	tempSocket = SDLNet_TCP_Accept(m_socket);

	//if no client is available to connect pause a few milliseconds and return
	if (!tempSocket)
	{
		SDL_Delay(500);
		return false;
	}

	//otherwise store the client socket connection for later use
	m_clientSocket = tempSocket;

	return true;

}
//------------------------------------------------------------------------------------------------------
//function that sends a passed message via the connection socket
//------------------------------------------------------------------------------------------------------
bool TCPServer::Send(const std::string& message)
{

	//first check if client socket is still valid before continuing to send a message
	//we do this because the client may have disconnected from the server in the meantime
	if (!m_clientSocket)
	{
		std::cout << "Invalid socket. Cannot send message." << std::endl << std::endl;
		return false;
	}

	//the length of the message must include the '\0'
	int length = message.length() + 1;

	if (SDLNet_TCP_Send(m_clientSocket, message.c_str(), length) < length)
	{
		std::cout << "Error sending message." << std::endl << std::endl;
		return false;
	}

	return true;

}
//------------------------------------------------------------------------------------------------------
//function that receives a message via the connection socket and stores it in passed string
//------------------------------------------------------------------------------------------------------
bool TCPServer::Receive(std::string& message)
{

	//first check if client socket is still valid before continuing to receive a message
	//we do this because the client may have disconnected from the server in the meantime
	if (!m_clientSocket)
	{
		std::cout << "Invalid socket. Cannot receive message." << std::endl << std::endl;
		return false;
	}

	//fill the entire array with terminating null
	//when we then fill the array with a message
	//there will always be a terminating null present
	char tempMessage[2000] = { '\0' };

	if (SDLNet_TCP_Recv(m_clientSocket, tempMessage, 2000) <= 0)
	{
		std::cout << "Error receiving message." << std::endl << std::endl;
		return false;
	}

	message = tempMessage;

	return true;

}
//------------------------------------------------------------------------------------------------------
//function that closes down all connection sockets 
//------------------------------------------------------------------------------------------------------
void TCPServer::Close()
{

	//first close down listening socket
	TCPSocket::Close();

	//then close down client socket connection if it hasn't already been done
	if (!m_clientSocket)
	{
		std::cout << "Invalid socket. Cannot close socket." << std::endl << std::endl;
	}

	else
	{
		SDLNet_TCP_Close(m_clientSocket);
		m_clientSocket = nullptr;
	}

}