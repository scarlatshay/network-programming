#ifndef USER_H_
#define USER_H_
#include <string>
#include <iostream>
#include "TCPSocket.h"
#include <vector>
#include <fstream>

#define USER_FILE_NAME "users.txt"
#define USER_FILE_DELIMETER ","

using namespace std;

class TCPSocket;

class User {

private:

	string udpPort;
	string username;
	string password;
	string sessionName;
	bool connected;
	bool authenticated;
	bool inSession;
	TCPSocket* socket;

public:
	// CTOR
	User(string username, string password, TCPSocket* socket);

	// Static Methods
	static bool registerUser(User* user);
	static bool isRegistered(User* user);
	static bool isAuthenticated(User* user);

	// Getters
	string getIP();
	string getUsername();
	string getPassword();
	string getUdpPort();
	string getSessionName();
	TCPSocket* getSocket();
	bool isConnected();
	bool isAuthenticated();
	bool isInSession();

	// Setters
	void setUdpPort(string port);
	void setSocket(TCPSocket* socket);
	void setSessionName(string sessionName);

	// Other Methods
	void closeSession();
	void login();
	void logout();

	// DTOR
	virtual ~User();
};

#endif /* USER_H_ */
