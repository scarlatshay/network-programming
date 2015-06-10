#include <iostream>
#include <fstream>
#include "TCPSocket.h"
using namespace std;

class MessegeServerApp {
private:
	TCPSocket* serverSocket;
	ofstream outputUsersFile;
	ifstream inputUsersFile;

public:
	MessegeServerApp();

	// CLI Methods
	void listAllUsers(); 						// lu
	void listAllConnectedUsers(); 				// lcu
	void listAllSessions(); 					// ls
	void listAllRooms(); 						// lr
	void listAllUsersInRooms(string roomName);	// lru

	virtual ~MessegeServerApp();
};
