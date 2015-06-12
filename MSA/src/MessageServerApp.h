#ifndef MESSAGE_SERVER_APP_H_
#define MESSAGE_SERVER_APP_H_
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include "TCPSocket.h"
#include "MThread.h"
#include "Dispatcher.h"
#include "MessageServerAppProtocol.h"
#include "MessageServerAppPrivateProtocol.h"

using namespace std;

class Dispatcher;

class MessageServerApp : public MThread {
private:
	typedef map<string, User*> tOpenClients;
	tOpenClients openClients;
	TCPSocket* serverSocket;
	pthread_mutex_t mutex;
	Dispatcher* dispatcher;
	bool serverRunning;

public:
	// CTOR
	MessageServerApp();

	// Getters
	pthread_mutex_t* getMutex();

	// Main functional methods
	void run();
	void close();
	int readCommand(TCPSocket* client);
	string readData(TCPSocket* client);
	void sendCommand(int command, TCPSocket* client);
	bool authenticate(string username, string password);
	bool userExists(string username);
	bool registerUser(string username, string password);

	// CLI Methods
	void listUsers(); 						// lu
	void listConnectedUsers(); 				// lcu
	void listSessions(); 					// ls
	void listRooms(); 						// lr
	void listUsersInRooms(string roomName);	// lru

	// DTOR
	virtual ~MessageServerApp();
};
#endif /* MESSAGE_SERVER_APP_H_ */
