#include <iostream>
#include "ChatClient.h"

//======================================================================================================
ChatClient::ChatClient()
{
	isChatRunning = false;
	consoleHandle = nullptr;
}
//======================================================================================================
bool ChatClient::Start()
{
	//First get a handle on the console window so that 
	//we can manipulate the text colors individually
	consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);

	//Display configuration screen 
	std::cout << "#==============================#" << std::endl;
	std::cout << "|   CHAT 2000 Setup (Client)   |" << std::endl;
	std::cout << "#==============================#" << std::endl << std::endl;

	//Prompt user to enter an IP address to connect to
	std::cout << ">Please enter an IP address to connect to: ";
	std::getline(std::cin, IPString);

	//Setup all SDL systems and initialize the client 
	if (!client.Initialize(1234, IPString.c_str()))
	{
		system("pause");
		return false;
	}

	//Open up a client socket for server connections
	if (!client.Open())
	{
		system("pause");
		return false;
	}

	system("cls");

	std::cout << "#==============================#" << std::endl;
	std::cout << "|     Welcome to CHAT 2000     |" << std::endl;
	std::cout << "#==============================#" << std::endl;

	isChatRunning = true;
	return true;
}
//======================================================================================================
void ChatClient::Send()
{
	std::string message;

	//As long as the chat is still running wait for user to enter a message
	//Chat ends if the message is "end" otherwise the entered message is sent
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
			client.Send(message);
		}
	}
}
//======================================================================================================
void ChatClient::Receive()
{
	std::string message;

	//As long as the chat is still running wait for messages to come through
	//Chat ends if the message is "end" otherwise the received message is shown
	while (isChatRunning)
	{
		//If something goes wrong with receiving messages it is likely the 
		//client or server socket has closed therefore the chat will end
		if (!client.Receive(message))
		{
			isChatRunning = false;

			SetConsoleTextAttribute(consoleHandle, static_cast<WORD>(Color::Default));

			std::cout << "#==============================#" << std::endl;
			std::cout << "|         Chat ended.          |" << std::endl;
			std::cout << "#==============================#" << std::endl << std::endl;
		}

		else
		{
			//Set text color to green for server messages and then  
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
void ChatClient::Stop()
{
	client.Close();
	client.ShutDown();
}