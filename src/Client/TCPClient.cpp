#include <iostream>
#include "TCPClient.h"

//======================================================================================================
bool TCPClient::Send(const std::string& message)
{
	//First check if server socket is still valid before continuing to send a message
	//We do this because the server may have disconnected from the client in the meantime
	if (!socket)
	{
		std::cout << "Invalid socket. Cannot send message." << std::endl << std::endl;
		return false;
	}

	//The length of the message must include the '\0'
	int length = message.length() + 1;

	if (SDLNet_TCP_Send(socket, message.c_str(), length) < length)
	{
		std::cout << "Error sending message." << std::endl << std::endl;
		return false;
	}

	return true;
}
//======================================================================================================
bool TCPClient::Receive(std::string& message)
{
	//First check if server socket is still valid before continuing to receive a message
	//We do this because the server may have disconnected from the client in the meantime
	if (!socket)
	{
		std::cout << "Invalid socket. Cannot receive message." << std::endl << std::endl;
		return false;
	}

	//Fill the entire array with terminating null so that when we then fill 
	//the array with a message there will always be a terminating null present
	char tempMessage[2000] = { '\0' };

	if (SDLNet_TCP_Recv(socket, tempMessage, 2000) <= 0)
	{
		std::cout << "Error receiving message." << std::endl << std::endl;
		return false;
	}

	message = tempMessage;
	return true;
}