#include <iostream>

#include "MessageServerApp.h"
using namespace std;

void printInstructions() {
	cout << "To list all users: lu" << endl;
	cout << "To list all connected users: lcu" << endl;
	cout << "To list all sessions: ls" << endl;
	cout << "To list all rooms: lr" << endl;
	cout << "To list all users in a specific room: lru <room name>" << endl;
	cout << "To shutdown the server: x" << endl;
}

int main() {
	MessageServerApp msa;

	cout << "Welcome to the Messege Server App!" << endl;
	printInstructions();

	bool loop = true;

	while (loop) {
		string msg;
		string command;
		cout << "input> ";
		cin >> command;

		if (command == "lu") {
			msa.listUsers();
		}
		else if (command == "lcu") {
			msa.listConnectedUsers();
		}
		else if (command == "ls") {
			msa.listSessions();
		}
		else if (command == "lr") {\
			msa.listRooms();
		}
		else if (command == "lru") {
			// TODO: switch from equals to contains, put room number into function
			msa.listUsersInRooms("STAM");
		}
		else if (command == "x") {
			loop = false;
		}
		else if ((command == "h") || (command == "help")) {
			printInstructions();
		}
		else {
			cout << "Wrong command: \"" << command << "\"." << endl;
			cout << "For instructions type \"h\" or \"help\"" << endl;
		}
	}

	cout << "Messenger Server App shutdown. Bye bye." << endl;
	return 0;
}
