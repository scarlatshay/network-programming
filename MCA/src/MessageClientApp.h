#include <iostream>
#include <fstream>
#include "TCPSocket.h"
using namespace std;

class MessageClientApp {

private:
	TCPSocket* serverSocket;
	fstream usersFile;
	bool connectedToserver;
	bool clientOnSession;
	string peerName;
	string userName;
	string password;

public:
	MessageClientApp();

	// CLI Methods
	void listAllUsers(); 						// lu
	void listAllConnectedUsers(); 				// lcu
	void listAllSessions(); 					// ls
	void listAllRooms(); 						// lr
	void listAllUsersInRoom(string roomName);	// lru
	void disconnect(); 							// d
	void closeSession(); 						// cs
	void registerNewUser(string userName, string password); 					// register <user> <password>
	void loginWithCreds(string userName, string password); 						// login <user> <password>
	void connectToClientWithIP(string serverIP); 				// c
	void printStatus(); 						// o l
	void sendMessageToPeer(string message); 						// ○ s <message>
	void openSessionWithPeer(string peerName); 				// o <username>
	void enterChatRoom(string roomName); 						// ○ or <room name>
	void printClientStatus();
	virtual ~MessageClientApp();
};
