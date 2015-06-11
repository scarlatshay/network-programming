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

int main()
{
	MessageClientApp* mca = new MessageClientApp();

	cout << "Welcome to the Message Client App!" << endl;
	printInstructions();

	bool loop = true;
	string roomname;
	string username;

	while (loop)
	{
		string msg;
		string command;
		cout << "input> ";
		cin >> command;

		if(command == "c")
		{
			cout<<"login / signup ?"<<endl;
			string tmp;
			cin>>msg;
			cin>>tmp;
			if(tmp == "login")
				mca->connectToServer(msg,LOGIN);
			else if(tmp == "signup")
				mca->connectToServer(msg,REGISTER);
			else
				cout<<"Connection could not be established. please try again"<<endl;
				printInstructions();
		}
		else if(command == "lu")
		{
			mca->listAllActiveUsers();
		}
		else if(command == "lcu")
		{
			mca->LIST_CONNECTED_USERS();
		}
		else if(command == "lr")
		{
			mca->listAllOpenRooms();
		}
		else if(command == "lru")
		{
			cin>>msg;
			mca->listUsersOnChatRoom(msg);
		}
		else if(command == "o")
		{
			cin>>msg;
			mca->openSessionWithPeer(msg);
		}
		else if(command == "jr")
		{
			cin>>msg;
			mca->joinAChatRoom(msg);
		}
		else if(command == "cr")
		{
			cin>>msg;
			mca->createNewChatRoom(msg);
		}
		else if(command == "clr")
		{
			cin>>msg;
			mca->deleteChatRoom(msg);
		}
		else if(command == "s")
		{
			cin>>msg;
			mca->sendMessageToPeer(msg);
		}
		else if(command == "l")
		{
			mca->printClientStatus();
		}
		else if(command == "cs")
		{
			mca->closeSession();
		}
		else if(command == "d")
		{
			mca->disconnect();
		}
		else if(command == "help")
		{
			printInstructions();
		}
		else if(command == "x")
		{
			loop = false;
		}
		else
		{
			cout<<"wrong input"<<endl;
			printInstructions();
		}

	cout << "Messenger Client App shutdown. Bye bye." << endl;
	return 0;
	}

}
