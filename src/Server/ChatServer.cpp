#include <iostream>
#include <string>
#include "ChatServer.h"

//======================================================================================================
ChatServer::ChatServer()
{
	isChatRunning = false;
	consoleHandle = nullptr;
}
//======================================================================================================
bool ChatServer::Start()
{
	//First get a handle on the console window so that 
	//we can manipulate the text colors individually
	consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);

	std::cout << "#==============================#" << std::endl;
	std::cout << "|   CHAT 2000 Setup (Server)   |" << std::endl;
	std::cout << "#==============================#" << std::endl << std::endl;

	//Setup all SDL systems and initialize the server 
	if (!server.Initialize(1234))
	{
		system("pause");
		return false;
	}

	//Open up a server socket for client connections
	if (!server.Open())
	{
		system("pause");
		return false;
	}

	std::cout << ">Socket open for client connection." << std::endl << std::endl;
	std::cout << ">Waiting for client";
	return true;
}
//======================================================================================================
void ChatServer::Listen()
{
	while (!isChatRunning)
	{
		isChatRunning = server.Listen();
		std::cout << ".";
	}

	system("cls");

	std::cout << "#==============================#" << std::endl;
	std::cout << "|     Welcome to CHAT 2000     |" << std::endl;
	std::cout << "#==============================#" << std::endl;
}
//======================================================================================================
void ChatServer::Send()
{
	std::string message;

	//As long as the chat is still running wait for user to enter a message
	//chat ends if the message is "end" otherwise the entered message is sent
	while (isChatRunning)
	{
		SetConsoleTextAttribute(consoleHandle, static_cast<WORD>(Color::Default));
		std::cout << ">";

		SetConsoleTextAttribute(consoleHandle, static_cast<WORD>(Color::Blue));
		std::getline(std::cin, message, '\n');

		//Because getline() above creates a block call the chat may have 
		//ended on the other thread so we need to check the status of the chat
		if (!isChatRunning)
		{
			break;
		}

		else if (message == "end")
		{
			isChatRunning = false;
		}

		else
		{
			server.Send(message);
		}
	}
}
//======================================================================================================
void ChatServer::Receive()
{
	std::string message;

	//As long as the chat is still running wait for messages to come through
	//Chat ends if the message is "end" otherwise the received message is shown
	while (isChatRunning)
	{
		//If something goes wrong with receiving messages it is likely the 
		//client or server socket has closed therefore the chat will end
		if (!server.Receive(message))
		{
			isChatRunning = false;
			SetConsoleTextAttribute(consoleHandle, static_cast<WORD>(Color::Default));

			std::cout << "#==============================#" << std::endl;
			std::cout << "|         Chat ended.          |" << std::endl;
			std::cout << "#==============================#" << std::endl << std::endl;
		}

		else
		{
			//Set text color to green for client messages and then  
			//make it default to display the '>' before reverting it 
			//straight back to blue so we don't type in the wrong color 
			SetConsoleTextAttribute(consoleHandle, static_cast<WORD>(Color::Green));
			std::cout << message << std::endl;
			SetConsoleTextAttribute(consoleHandle, static_cast<WORD>(Color::Default));
			std::cout << ">";
			SetConsoleTextAttribute(consoleHandle, static_cast<WORD>(Color::Blue));

			isChatRunning = message != "end";
		}
	}
}
//======================================================================================================
void ChatServer::Stop()
{
	server.Close();
	server.ShutDown();
}