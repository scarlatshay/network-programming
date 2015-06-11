
#include "User.h"

User::User(string username, string password, TCPSocket* socket) {
	this->socket = socket;
	this->username = username;
	this->password = password;
	this->connected = true;
	this->authenticated = false;
	this->inSession=false;
}

bool User::registerUser(User* user) {
	// Open the users file for writing
	ofstream usersFile;
	usersFile.open(USER_FILE_NAME);

	// Make sure the file is indeed open
	if (!usersFile.is_open()) {
		cout << "Could not open users file: " << USER_FILE_NAME << endl;
		return false;
	}

	// Write user data into the user file
	// username,password
	try {
		usersFile << user->getUsername() << USER_FILE_DELIMETER << user->getPassword() << endl;
	}
	catch (...) {
		perror("Failed to register user.");
	}

	// Close file and return true
	usersFile.close();
	return true;
}

bool User::isRegistered(User* user) {
	// Open the users file for reading
    ifstream usersFile;
    usersFile.open(USER_FILE_NAME);

    // Make sure the file is indeed open
    if (!usersFile.is_open()) {
    	cout << "Could not open users file: " << USER_FILE_NAME << endl;
        return false;
    }

    // Locate the username in the file
    bool registered = false;
    try {
        string line;
        while (getline(usersFile, line) && !registered) {
            long i = line.find(user->getUsername());
            if (i > -1)
                registered = true;
        }
    }
    catch (...) {
        perror("Failed to check if user is registered.");
    }

    // Close file and return
    usersFile.close();
    return registered;
}

bool User::isAuthenticated(User* user) {
	// Open file for reading
    ifstream usersFile;
    usersFile.open(USER_FILE_NAME);

    // Make sure it is indeed open
    if (!usersFile.is_open()) {
    	cout << "Could not open users file: " << USER_FILE_NAME << endl;
        return false;
    }

    // Check if user's authentication details are correct
    bool authenticated = false;
    try {
        string line = string();
        while (getline(usersFile, line) && !authenticated) {
            long i = line.find(user->getUsername() + USER_FILE_DELIMETER + user->getUsername());
            if (i > -1)
                authenticated = true;
        }

    }
    catch (...) {
        perror("Failed to read information about the user");
    }

    // Close file and return
    usersFile.close();
    return authenticated;
}

string User::getIP() {
	return this->socket->fromAddr();
}

string User::getUsername() {
	return this->username;
}

string User::getPassword() {
	return this->password;
}

string User::getUdpPort() {
	return this->udpPort;
}

TCPSocket* User::getSocket() {
	return this->socket;
}

bool User::isConnected() {
	return this->connected;
}

bool User::isInSession() {
	return this->inSession;
}

void User::setUdpPort(string port) {
	this->udpPort = port;
}

void User::setSocket(TCPSocket* socket) {
	this->socket = socket;
}

void User::closeSession() {
	// TODO: User.cpp closeSession()
}

void User::login() {
	this->authenticated = true;
	this->connected = true;
}

void User::logout() {
	this->authenticated = false;
	this->connected = false;
	if (this->socket != NULL) {
		this->socket->cclose();
		delete this->socket;
	}
}

User::~User() {
	delete socket;
}

