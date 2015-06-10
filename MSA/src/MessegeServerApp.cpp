
#include "MessegeServerApp.h"

#define USER_FILE_NAME "users.txt"
#define USER_FILE_DELIMETER ","

MessegeServerApp::MessegeServerApp() {
	// TODO:Create constructor
	// Open listening port
	serverSocket = new TCPSocket(5050);

	// Open users file
	usersFile.open(USER_FILE_NAME);
}

void MessegeServerApp::listAllUsers() {
	// TODO: Create listAllUsers()
	cout << "list all users" << endl;

	string line;
	if (usersFile.is_open()) {
		while (getline(usersFile, line)) {
			cout << line << endl;
		}
	}
	else {
		cout << "Users file not open." << endl;
	}
}

void MessegeServerApp::listAllConnectedUsers() {
	// TODO: Create listAllConnectedUsers()
	cout << "list all connected users" << endl;
}

void MessegeServerApp::listAllSessions() {
	// TODO: Create listAllSessions()
	cout << "list all sessions" << endl;
}

void MessegeServerApp::listAllRooms() {
	// TODO: Create listAllRooms()
	cout << "list all rooms" << endl;
}

void MessegeServerApp::listAllUsersInRooms(string roomName) {
	// TODO: Create listAllUsersInRoom()
	cout << "list all users in a specific room" << endl;
}

MessegeServerApp::~MessegeServerApp() {
	// TODO Create destructor

	usersFile.close();
	delete serverSocket;
}
