#include <string>
#include <iostream>
#include "TCPSocket.h"
#include <vector>
#include <fstream>

#define USER_FILE_NAME "users.txt"
#define USER_FILE_DELIMETER ","

using namespace std;

class User {

private:

	string udpPort;
	string username;
	string password;
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
	TCPSocket* getSocket();
	bool isConnected();
	bool isAuthenticated();
	bool isInSession();


	// Setters
	void setUdpPort(string port);
	void setSocket(TCPSocket* socket);

	// Other Methods
	void closeSession();
	void login();
	void logout();

	// DTOR
	virtual ~User();
};
