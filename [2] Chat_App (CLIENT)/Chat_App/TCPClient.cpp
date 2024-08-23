#include <iostream>
#include "TCPClient.h"

//------------------------------------------------------------------------------------------------------
//function that sends a passed message via the connection socket
//------------------------------------------------------------------------------------------------------
bool TCPClient::Send(const std::string& message)
{

	//first check if server socket is still valid before continuing to send a message
	//we do this because the server may have disconnected from the client in the meantime
	if (!m_socket)
	{
		std::cout << "Invalid socket. Cannot send message." << std::endl << std::endl;
		return false;
	}

	//the length of the message must include the '\0'
	int length = message.length() + 1;

	if (SDLNet_TCP_Send(m_socket, message.c_str(), length) < length)
	{
		std::cout << "Error sending message." << std::endl << std::endl;
		return false;
	}

	return true;

}
//------------------------------------------------------------------------------------------------------
//function that receives a message via the connection socket and stores it in passed string
//------------------------------------------------------------------------------------------------------
bool TCPClient::Receive(std::string& message)
{

	//first check if server socket is still valid before continuing to receive a message
	//we do this because the server may have disconnected from the client in the meantime
	if (!m_socket)
	{
		std::cout << "Invalid socket. Cannot receive message." << std::endl << std::endl;
		return false;
	}

	//fill the entire array with terminating null
	//when we then fill the array with a message
	//there will always be a terminating null present
	char tempMessage[2000] = { '\0' };

	if (SDLNet_TCP_Recv(m_socket, tempMessage, 2000) <= 0)
	{
		std::cout << "Error receiving message." << std::endl << std::endl;
		return false;
	}

	message = tempMessage;

	return true;

}