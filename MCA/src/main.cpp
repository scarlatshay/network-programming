#include <iostream>
#include "MessageClientApp.h"
using namespace std;

//○ s <message> - send a message
//○ l - print the current status of the client (connected to “xyz”/not
//connected)



void printInstructions() {

	cout << "To list all users: lu" << endl;
	cout << "To list all connected users: lcu" << endl;
	cout << "To list all sessions: ls" << endl;
	cout << "To list all rooms: lr" << endl;
	cout << "To list all users in a specific room: lru <room name>" << endl;
	cout << "To open a session with the user: o <username>" << endl;
	cout << "To enter a chat room: ○ or <room name>" << endl;
	cout << "To send a message: ○ s <message>" << endl;
	cout << "To print the current status of the client: ○ l" << endl;
	cout << "To connect to a server with the given ip: c" << endl;
	cout << "To login with the user and password: login <user> <password>" << endl;
	cout << "To register the new user with the given password and login: register <user> <password>" << endl;
	cout << "To disconnect the open session / exit from a room: cs" << endl;
	cout << "To disconnect from server: d" << endl;
	cout << "To close the app: x" << endl;
}

int main() {
	MessageClientApp* mca = new MessageClientApp();

	cout << "Welcome to the Message Client App!" << endl;
	printInstructions();

	bool loop = true;
	string roomname;
	string username;

	while (loop) {
		string msg;
		string command;
		cout << "input> ";
		cin >> command;

		if (command == "lu") {
			mca->listAllUsers();
		}
		else if (command == "lcu") {
			mca->listAllConnectedUsers();
		}
		else if (command == "ls") {
			mca->listAllSessions();
		}
		else if (command == "lr") {
			mca->listAllRooms();
		}
		else if (command == "lru") {
			// TODO: switch from equals to contains, put room number into function
			mca->listAllUsersInRooms("STAM");
		}
		else if (command == "x") {
			loop = false;
			delete mca;
		}
		else if (command == "d") {
			//disconnect from server: d
			mca->disconnect();
		}
		else if (command == "cs") {
			//Disconnect the open session / exit from a room
			mca->disconnectSession();

		}
		else if (command == "register") {
			//To register the new user with the given password and login: register <user> <password> //TODO
			mca->registerNewUser();

		}
		else if (command == "login") {
			//To login with the user and password: login <user> <password> //TODO
			mca->loginWithCreds();

		}
		else if (command == "c") {
			//To connect to a server with the given ip
			mca->connectToClientWithIP();

		}
		else if (command == "o l") {
			//To print the current status of the client
			mca->printStatus();

		}
		else if (command == "o s") {
			//To send a message: ○ s <message>
			mca->sendMessage();

		}
		else if ((command == "o") && (command == username)) {
			//To open a session with the user: o <username>
			mca->openSessionWithUame();

		}
		else if ((command == "o") || (command == roomname)) {
			//To enter a chat room: ○ or <room name>
			mca->enterChatRoom();

		}

		else if ((command == "h") || (command == "help")) {
			printInstructions();
		}
		else {
			cout << "Wrong command: \"" << command << "\"." << endl;
			cout << "For instructions type \"h\" or \"help\"" << endl;
		}
	}

	cout << "Messenger Client App shutdown. Bye bye." << endl;
	return 0;
}
