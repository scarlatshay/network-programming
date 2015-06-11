#include <iostream>
#include <fstream>
#include "TCPSocket.h"
#include "MThread.h"
using namespace std;

class MessageServerApp : public MThread {
private:
	bool running;
	TCPSocket* serverSocket;
	ofstream outputUsersFile;
	ifstream inputUsersFile;

public:
	MessageServerApp();

	// Main functional methods
	void run();
	void close();

	// CLI Methods
	void listAllUsers(); 						// lu
	void listAllConnectedUsers(); 				// lcu
	void listAllSessions(); 					// ls
	void listAllRooms(); 						// lr
	void listAllUsersInRooms(string roomName);	// lru

	virtual ~MessageServerApp();
};
