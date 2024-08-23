#include <iostream>
#include <string>
#include "ChatServer.h"

//------------------------------------------------------------------------------------------------------
//constructor that initializes all default values
//------------------------------------------------------------------------------------------------------
ChatServer::ChatServer()
{

	m_isChatRunning = false;
	m_consoleHandle = nullptr;

}
//------------------------------------------------------------------------------------------------------
//function that sets up console pointer, initializes server and opens its listening socket
//------------------------------------------------------------------------------------------------------
bool ChatServer::Start()
{
	
	//first get a handle on the console window so that 
	//we can manipulate the text colors individually
	m_consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);

	//display configuration screen 
	std::cout << "#==============================#" << std::endl;
	std::cout << "|   CHAT 2000 Setup (Server)   |" << std::endl;
	std::cout << "#==============================#" << std::endl << std::endl;

	//setup all SDL systems and initialize the server 
	if (!m_server.Initialize(1234))
	{
		system("pause");
		return false;
	}

	//open up a server socket for client connections
	if (!m_server.Open())
	{
		system("pause");
		return false;
	}

	std::cout << ">Socket open for client connection." << std::endl << std::endl;
	std::cout << ">Waiting for client";

	return true;

}
//------------------------------------------------------------------------------------------------------
//function that listens in for incoming client connection
//------------------------------------------------------------------------------------------------------
void ChatServer::Listen()
{

	while (!m_isChatRunning)
	{
		m_isChatRunning = m_server.Listen();
		std::cout << ".";
	}

	system("cls");

	std::cout << "#==============================#" << std::endl;
	std::cout << "|     Welcome to CHAT 2000     |" << std::endl;
	std::cout << "#==============================#" << std::endl;

}
//------------------------------------------------------------------------------------------------------
//function that manages the sending of messages to the client
//------------------------------------------------------------------------------------------------------
void ChatServer::Send()
{

	std::string message;

	//as long as the chat is still running wait for user to enter a message
	//chat ends if the message is "end" otherwise the entered message is sent
	while (m_isChatRunning)
	{

		//set text color back to DEFAULT
		SetConsoleTextAttribute(m_consoleHandle, static_cast<WORD>(Color::DEFAULT));

		std::cout << ">";

		//set text color to BLUE for our messages 
		SetConsoleTextAttribute(m_consoleHandle, static_cast<WORD>(Color::BLUE));
		std::getline(std::cin, message, '\n');

		//because getline() above creates a block call the chat may have 
		//ended on the other thread so we need to check the status of the chat
		if (!m_isChatRunning)
		{
			break;
		}

		else if (message == "end")
		{
			m_isChatRunning = false;
		}

		else
		{
			m_server.Send(message);
		}

	}

}
//------------------------------------------------------------------------------------------------------
//function that manages the received messages from the client
//------------------------------------------------------------------------------------------------------
void ChatServer::Receive()
{

	std::string message;

	//as long as the chat is still running wait for messages to come through
	//chat ends if the message is "end" otherwise the received message is shown
	while (m_isChatRunning)
	{

		//if something goes wrong with receiving messages it is likely the 
		//client or server socket has closed therefore the chat will end
		if (!m_server.Receive(message))
		{
			m_isChatRunning = false;

			//set text color back to DEFAULT
			SetConsoleTextAttribute(m_consoleHandle, static_cast<WORD>(Color::DEFAULT));

			std::cout << "#==============================#" << std::endl;
			std::cout << "|         Chat ended.          |" << std::endl;
			std::cout << "#==============================#" << std::endl << std::endl;

		}

		else
		{
			//set text color to GREEN for client messages and then  
			//make it DEFAULT to display the '>' before reverting it 
			//straight back to BLUE so we don't type in the wrong color 
			SetConsoleTextAttribute(m_consoleHandle, static_cast<WORD>(Color::GREEN));
			std::cout << message << std::endl;
			SetConsoleTextAttribute(m_consoleHandle, static_cast<WORD>(Color::DEFAULT));
			std::cout << ">";
			SetConsoleTextAttribute(m_consoleHandle, static_cast<WORD>(Color::BLUE));

			m_isChatRunning = message != "end";
		}

	}

}
//------------------------------------------------------------------------------------------------------
//function that closes the listening and client socket and all SDL systems
//------------------------------------------------------------------------------------------------------
void ChatServer::Stop()
{

	m_server.Close();
	m_server.ShutDown();

}