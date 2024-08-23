#include <iostream>
#include "ChatClient.h"

//------------------------------------------------------------------------------------------------------
//constructor that initializes all default values
//------------------------------------------------------------------------------------------------------
ChatClient::ChatClient()
{

	m_isChatRunning = false;
	m_consoleHandle = nullptr;

}
//------------------------------------------------------------------------------------------------------
//function that sets up console pointer and initializes client
//------------------------------------------------------------------------------------------------------
bool ChatClient::Start()
{
	
	//first get a handle on the console window so that 
	//we can manipulate the text colors individually
	m_consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);

	//display configuration screen 
	std::cout << "#==============================#" << std::endl;
	std::cout << "|   CHAT 2000 Setup (Client)   |" << std::endl;
	std::cout << "#==============================#" << std::endl << std::endl;

	//prompt user to enter an IP address to connect to
	std::cout << ">Please enter an IP address to connect to: ";
	std::getline(std::cin, m_IPString);

	//setup all SDL systems and initialize the client 
	if (!m_client.Initialize(1234, m_IPString.c_str()))
	{
		system("pause");
		return false;
	}

	//open up a client socket for server connections
	if (!m_client.Open())
	{
		system("pause");
		return false;
	}

	system("cls");

	std::cout << "#==============================#" << std::endl;
	std::cout << "|     Welcome to CHAT 2000     |" << std::endl;
	std::cout << "#==============================#" << std::endl;

	m_isChatRunning = true;

	return true;

}
//------------------------------------------------------------------------------------------------------
//function that manages the sending of messages to the server
//------------------------------------------------------------------------------------------------------
void ChatClient::Send()
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
			m_client.Send(message);
		}

	}

}
//------------------------------------------------------------------------------------------------------
//function that manages the received messages from the server
//------------------------------------------------------------------------------------------------------
void ChatClient::Receive()
{

	std::string message;

	//as long as the chat is still running wait for messages to come through
	//chat ends if the message is "end" otherwise the received message is shown
	while (m_isChatRunning)
	{

		//if something goes wrong with receiving messages it is likely the 
		//client or server socket has closed therefore the chat will end
		if (!m_client.Receive(message))
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
			//set text color to GREEN for server messages and then  
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
//function that closes the client socket and all SDL systems
//------------------------------------------------------------------------------------------------------
void ChatClient::Stop()
{

	m_client.Close();
	m_client.ShutDown();

}