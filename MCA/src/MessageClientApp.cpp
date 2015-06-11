
#include "MessageClientApp.h"

// TODO: Create listAllUsers()
void MessageClientApp::listAllUsers() {

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

// TODO: Create listAllConnectedUsers()
void MessageClientApp::listAllConnectedUsers() {

	cout << "list all connected users" << endl;
}

// TODO: Create listAllSessions()
void MessageClientApp::listAllSessions() {

	cout << "list all sessions" << endl;
}

// TODO: Create listAllRooms()
void MessageClientApp::listAllRooms() {

	cout << "list all rooms" << endl;
}

// TODO: Create listAllUsersInRoom()
void MessageClientApp::listAllUsersInRooms(string roomName) {

	cout << "list all users in a specific room" << endl;
}

//d
void MessageClientApp::disconnect() {
	cout << "list all rooms" << endl;

}

// cs
void MessageClientApp::disconnectSession() {
	cout << "list all rooms" << endl;

}

// register <user> <password>
void MessageClientApp::registerNewUser() {
	cout << "list all rooms" << endl;

}

// login <user> <password>
void MessageClientApp::loginWithCreds() {
	cout << "list all rooms" << endl;

}

// c
void MessageClientApp::connectToClientWithIP() {
	cout << "list all rooms" << endl;

}

// o l
void MessageClientApp::printStatus() {
	cout << "list all rooms" << endl;

}

// ○ s <message>
void MessageClientApp::sendMessage() {
	cout << "list all rooms" << endl;

}

// o <username>
void MessageClientApp::openSessionWithUame() {
	cout << "list all rooms" << endl;

}

// ○ or <room name>
void MessageClientApp::enterChatRoom() {
	cout << "list all rooms" << endl;

}

// TODO Create destructor
MessageClientApp::~MessageClientApp() {


	usersFile.close();
	delete serverSocket;
}


