#include <iostream>
#include "TCPServer.h"

//======================================================================================================
TCPServer::TCPServer()
{
	clientSocket = nullptr;
}
//======================================================================================================
bool TCPServer::Listen()
{
	TCPsocket tempSocket{ nullptr };

	//First check if listening socket is still valid before continuing to accept 
	//We do this because the accept routine could crash if the socket is invalid
	if (!socket)
	{
		std::cout << "Invalid socket. Cannot listen for connections." << std::endl << std::endl;
		return false;
	}

	//If client has connected, server will establish a connection and save it
	tempSocket = SDLNet_TCP_Accept(socket);

	//If no client is available to connect pause a few milliseconds and return
	if (!tempSocket)
	{
		SDL_Delay(500);
		return false;
	}

	//Otherwise store the client socket connection for later use
	clientSocket = tempSocket;
	return true;
}
//======================================================================================================
bool TCPServer::Send(const std::string& message)
{
	//First check if client socket is still valid before continuing to send a message
	//We do this because the client may have disconnected from the server in the meantime
	if (!clientSocket)
	{
		std::cout << "Invalid socket. Cannot send message." << std::endl << std::endl;
		return false;
	}

	//The length of the message must include the '\0'
	int length = message.length() + 1;

	if (SDLNet_TCP_Send(clientSocket, message.c_str(), length) < length)
	{
		std::cout << "Error sending message." << std::endl << std::endl;
		return false;
	}

	return true;
}
//======================================================================================================
bool TCPServer::Receive(std::string& message)
{
	//First check if client socket is still valid before continuing to receive a message
	//We do this because the client may have disconnected from the server in the meantime
	if (!clientSocket)
	{
		std::cout << "Invalid socket. Cannot receive message." << std::endl << std::endl;
		return false;
	}

	//Fill the entire array with terminating null so that when we then fill 
	//the array with a message there will always be a terminating null present
	char tempMessage[2000] = { '\0' };

	if (SDLNet_TCP_Recv(clientSocket, tempMessage, 2000) <= 0)
	{
		std::cout << "Error receiving message." << std::endl << std::endl;
		return false;
	}

	message = tempMessage;
	return true;
}
//======================================================================================================
void TCPServer::Close()
{
	//First close down listening socket
	TCPSocket::Close();

	//Then close down client socket connection if it hasn't already been done
	if (!clientSocket)
	{
		std::cout << "Invalid socket. Cannot close socket." << std::endl << std::endl;
	}

	else
	{
		SDLNet_TCP_Close(clientSocket);
		clientSocket = nullptr;
	}
}