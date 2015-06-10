
#include "MessageServerApp.h"

MessageServerApp::MessageServerApp() {
	running = false;
}

void MessageServerApp::run() {
	// Open listening port
	serverSocket = new TCPSocket(5050);

	// Open users file
	outputUsersFile.open("users.txt", ios::app);
	inputUsersFile.open("users.txt", ios::app);

	// Mark the server as running
	running = true;
}

void MessageServerApp::close() {
	running = false;
	outputUsersFile.close();
	inputUsersFile.close();
	serverSocket->cclose();
}

void MessageServerApp::listAllUsers() {
	// TODO: Create listAllUsers()
}

void MessageServerApp::listAllConnectedUsers() {
	// TODO: Create listAllConnectedUsers()
	cout << "list all connected users" << endl;
}

void MessageServerApp::listAllSessions() {
	// TODO: Create listAllSessions()
	cout << "list all sessions" << endl;
}

void MessageServerApp::listAllRooms() {
	// TODO: Create listAllRooms()
	cout << "list all rooms" << endl;
}

void MessageServerApp::listAllUsersInRooms(string roomName) {
	// TODO: Create listAllUsersInRoom()
	cout << "list all users in a specific room" << endl;
}

MessageServerApp::~MessageServerApp() {
	this->close();
}
