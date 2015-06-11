
#include "MessageClientApp.h"

void MessageClientApp::listAllUsers() {
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

void MessageClientApp::listAllConnectedUsers() {
	// TODO: Create listAllConnectedUsers()
	cout << "list all connected users" << endl;
}

void MessageClientApp::listAllSessions() {
	// TODO: Create listAllSessions()
	cout << "list all sessions" << endl;
}

void MessageClientApp::listAllRooms() {
	// TODO: Create listAllRooms()
	cout << "list all rooms" << endl;
}

void MessageClientApp::listAllUsersInRooms(string roomName) {
	// TODO: Create listAllUsersInRoom()
	cout << "list all users in a specific room" << endl;
}

void MessageClientApp::disconnect() {
	cout << "list all rooms" << endl;

}
//d

void MessageClientApp::disconnectSession() {
	cout << "list all rooms" << endl;

}
// cs

void MessageClientApp::registerNewUser() {
	cout << "list all rooms" << endl;

}
// register <user> <password>

void MessageClientApp::loginWithCreds() {
	cout << "list all rooms" << endl;

}
// login <user> <password>

void MessageClientApp::connectToClientWithIP() {
	cout << "list all rooms" << endl;

}
// c

void MessageClientApp::printStatus() {
	cout << "list all rooms" << endl;

}
// o l

void MessageClientApp::sendMessage() {
	cout << "list all rooms" << endl;

}
// ○ s <message>

void MessageClientApp::openSessionWithUame() {
	cout << "list all rooms" << endl;

}
// o <username>

void MessageClientApp::enterChatRoom() {
	cout << "list all rooms" << endl;

} 						// ○ or <room name>


MessageClientApp::~MessageClientApp() {
	// TODO Create destructor

	usersFile.close();
	delete serverSocket;
}


