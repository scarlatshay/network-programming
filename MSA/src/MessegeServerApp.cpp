
#include "MessegeServerApp.h"

#define USER_FILE_NAME "users.txt"
#define USER_FILE_DELIMETER ","

MessegeServerApp::MessegeServerApp() {
	// Open listening port
	serverSocket = new TCPSocket(5050);

	// Open users file
	outputUsersFile.open("users.txt", ios::app);
	inputUsersFile.open("users.txt", ios::app);
}

void MessegeServerApp::listAllUsers() {

	string line;

	// Make sure file is open
	if (inputUsersFile.is_open()) {
		// Go through all lines in the file
		while (getline(inputUsersFile, line)) {
			// Print the username only (without the password)
			size_t pos = line.find(USER_FILE_DELIMETER);
			if (pos == string::npos) break;
			cout << line.substr(0, pos) << endl;
		}
	}
	else cout << "Users file not open." << endl;
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
	outputUsersFile.close();
	inputUsersFile.close();
	delete serverSocket;
}
