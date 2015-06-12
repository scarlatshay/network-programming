#ifndef DISPATCHER_H_
#define DISPATCHER_H_
#include <strings.h>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include <map>
#include <vector>
#include "TCPSocket.h"
#include "User.h"
#include "MessageServerApp.h"
#include "MThread.h"
#include "MultipleTCPSocketsListener.h"
#include "MessageServerAppProtocol.h"
#include "MessageServerAppPrivateProtocol.h"
#include "Chat.h"

class MessageServerApp;

using namespace std;

class Dispatcher : public MThread {
	typedef map<string, User*> tConnectedClients; // name -> user*
	tConnectedClients* connectedClients;

	typedef map<string, User*> tSessionClients; //session name(to who connected) -> user*
	tSessionClients* sessionClients;

	typedef map<string, Chat*> tChatClients; //nameOfChatRoom -> pointerToAllocatedChatRoom
	tChatClients* chatClients;

	MultipleTCPSocketsListener* multiListener;
	MessageServerApp* msa;
	bool serverRunning;

	//private methods:
	void clientDisconnected(TCPSocket* peer);
	void openSession(TCPSocket* peer);
	void closeSession(TCPSocket* peer);
	void openChat(TCPSocket* peer);
	void closeChat(TCPSocket* peer);
	void joinChat(TCPSocket* peer);
	void leaveChat(TCPSocket* peer);
	void sendData(string data, TCPSocket* peer);
	void sendUserList(TCPSocket* peer);
	void sendConnectedUserList(TCPSocket* peer);
	void sendRoomsList(TCPSocket* peer);
	void sendConnectedUsersToRoom(TCPSocket* peer);
	void lock();
	void unlock();

public:
	Dispatcher(tConnectedClients* connectedClients, MessageServerApp* server);
	void run();
	void listSessions();
	void printRoom();
	void printUsersInRooms(string roomName);
	virtual ~Dispatcher();

	friend class MessageServerApp;
};
#endif /* DISPATCHER_H_ */
