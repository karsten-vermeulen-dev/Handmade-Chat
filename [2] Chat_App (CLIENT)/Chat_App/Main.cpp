#include <thread>
#include "ChatClient.h"

//create a chat app client-side 
ChatClient chatApp;

//------------------------------------------------------------------------------------------------------
//main function that processes everything  
//------------------------------------------------------------------------------------------------------
int main(int argc, char* args[])
{
	
	//start up the chat app
	if (!chatApp.Start())
	{
		return 0;
	}

	//create separate threads for sending and receiving messages. We use the
	//address of the 'chatApp' object so that we don't use different copies
	//If we use copies, the threads will use different flag variables and hence
	//one thread's manipulation of a flag will not affect the other thread
	std::thread sendThread(&ChatClient::Send, &chatApp);
	std::thread receiveThread(&ChatClient::Receive, &chatApp);

	//wait until all sending is done and only close client socket afterwards
	sendThread.join();
	chatApp.Stop();

	//let the second thread finish up before shutting down everything!
	//because the client sockets are closed at this point the receiving
	//thread will end automatically because no more messages will come through 
	receiveThread.join();

	return 0;

}