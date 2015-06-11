#include <iostream>
#include <fstream>
#include "TCPSocket.h"
using namespace std;

class MessageClientApp {

private:
	TCPSocket* serverSocket;
	fstream usersFile;

public:
	MessageClientApp();

	// CLI Methods
	void listAllUsers(); 						// lu
	void listAllConnectedUsers(); 				// lcu
	void listAllSessions(); 					// ls
	void listAllRooms(); 						// lr
	void listAllUsersInRooms(string roomName);	// lru
	void disconnect(); 							//d
	void disconnectSession(); 					// cs
	void registerNewUser(); 					// register <user> <password>
	void loginWithCreds(); 						// login <user> <password>
	void connectToClientWithIP(); 				// c
	void printStatus(); 						// o l
	void sendMessage(); 						// ○ s <message>
	void openSessionWithUame(); 				// o <username>
	void enterChatRoom(); 						// ○ or <room name>
	virtual ~MessageClientApp();
};
