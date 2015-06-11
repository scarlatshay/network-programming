#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <stdlib.h>
#include "TCPSocket.h"
#include "MessageServerAppProtocol.h"
#include "ClientUDPListener.h"
#include "MThread.h"

using namespace std;

class MessageClientApp:MThread {

	bool connectedToserver;
	bool clientOnSession;
	bool flag;
	string name;
	string peerName;
	int listenerPort;
	int status;
	TCPSocket* server;
	typedef map<string, string> tOpenedPeers;//name : ip&port
	tOpenedPeers peers;
	TCPSocket* serverSocket;
	fstream usersFile;
	string userName;
	string password;
	ClientUDPListener* listener; //TODO

public:
	MessageClientApp();

	// CLI Methods
	int readCommand(TCPSocket* peer);
	string readData(TCPSocket* peer);
	void sendCommand(int command, TCPSocket* peer);
	void sendData(string data, TCPSocket* peer);
	bool connectToServer(string ip, int command);
	bool isConnected();
	bool disconnect();
	void listAllActiveUsers();
	void listAllOpenRooms();
	void listUsersOnChatRoom(string roomName);
	void openSessionWithPeer(string peerName);
	void joinAChatRoom(string chatRoomName);
	void createNewChatRoom(string roomName);
	void deleteChatRoom(string roomName);
	void sendMessageToPeer(string massage);
	void printClientStatus();
	void closeSession();
	void close();
	void run();
	~MessageClientApp();

};
