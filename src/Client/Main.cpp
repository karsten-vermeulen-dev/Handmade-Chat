#include <thread>
#include "ChatClient.h"

ChatClient chatApp;

int main(int argc, char* args[])
{
	if (!chatApp.Start())
	{
		return 0;
	}

	//Create separate threads for sending and receiving messages. We use the
	//address of the 'chatApp' object so that we don't use different copies
	//If we use copies, the threads will use different flag variables and hence
	//one thread's manipulation of a flag will not affect the other thread
	std::thread sendThread(&ChatClient::Send, &chatApp);
	std::thread receiveThread(&ChatClient::Receive, &chatApp);

	//Wait until all sending is done and only close client socket afterwards
	sendThread.join();
	chatApp.Stop();

	//Allow the second thread to finish up before shutting down everything
	//Because the client sockets are closed at this point the receiving
	//thread will end automatically because no more messages will come through 
	receiveThread.join();
	return 0;
}