
#include "MessageServerApp.h"

MessageServerApp::MessageServerApp() {
	// Init mutex
	pthread_mutex_init(&(this->mutex), NULL);

	// Init all dynamically allocated variables
	serverSocket = new TCPSocket(MSA_SERVER_PORT);
	dispatcher = new Dispatcher(&openClients, this);

	// Start the server thread
	start();

	// Change the server's status to running
	this->serverRunning = true;
	cout << "Message Server App Started !" << endl;
}

pthread_mutex_t* MessageServerApp::getMutex() {
	return &mutex;
}

void MessageServerApp::run() {
	// TODO MesageServerApp run
	dispatcher->start();
	TCPSocket* client;

	while(serverRunning) {
		client->listenAndAccept();
		//if (client == NULL) continue;

		// Get client's incoming port
		string ipAndPort = client->getIPandPort();
		ipAndPort = ipAndPort.substr(ipAndPort.find(":")+1, ipAndPort.length());
		int port = atoi(ipAndPort.c_str());

		// Sending the port back to the client, so that it will listen to it on UDP
		sendCommand(port, client);

		// Get command from client
		int command = readCommand(client);

		string username = readData(client);
		string password = readData(client);

		// handle command by user
		if (command == LOGIN) {
			if (authenticate(username, password)) {
				User* newUser = new User(username, password, client);
				bool userAlreadyLoggedIn = false;
				string key;
				for (tOpenClients::iterator iter = openClients.begin(); iter != openClients.end(); iter++) {
					key = (*iter).first;
					 if (key == newUser->getUsername()) { // user already logged in
						 userAlreadyLoggedIn = true;
						 cout << "User " << username << " is already logged in." << endl;
						 sendCommand(ERROR, client);
						 break;
					 }
				}

				if (userAlreadyLoggedIn) break;

				pthread_mutex_lock(&mutex);
				openClients.insert(pair<string, User*>(newUser->getUsername(), newUser));
				pthread_mutex_unlock(&mutex);

				sendCommand(OK, client);
				cout << "User " << newUser->getUsername() << " is now logged in." << endl;
			}
			else
				sendCommand(ERROR, client);
		}
	}
}

void MessageServerApp::close() {
	// TODO MesageServerApp close
	serverRunning = false;
	serverSocket->cclose();
	this->waitForThread();
	dispatcher->serverRunning = false;
	dispatcher->waitForThread();
	delete dispatcher;
	delete serverSocket;
	cout << "Message Server App closed. Bye bye." << endl;
}

int MessageServerApp::readCommand(TCPSocket* client) {
	int command;

	// receive the first 4 bits of the transmission
	int readLength = client->recv((char*)&command, 4);
	command = ntohl(command);

	// If received less than 4 bits, send back an error -1
	if (readLength < 4)
		return -1;

	// All OK
	return command;
}

string MessageServerApp::readData(TCPSocket* client) {
	int readLength;
	int messageLength;

	// Receive the first 4 bits of the transmission
	readLength = client->recv((char*)&messageLength, 4);
	messageLength = ntohl(messageLength);

	// If received less than 4 bits, send back an empty string
	if ((readLength < 4) || (messageLength > 2048))
		return "";

	// Receive message itself
	char buffer[2048];
	readLength = client->recv((char*)&buffer, messageLength);

	if (readLength != messageLength) // ERROR !
		return "";

	// Convert the buffer into a string and return it
	return ((string)buffer).substr(0, messageLength);
}

void MessageServerApp::sendCommand(int command, TCPSocket* client) {
	// Prepare command to be sent through the network, then send it
	int netCommand = htonl(command);
	client->send((char*)&netCommand, 4);

}

bool MessageServerApp::authenticate(string username, string password) {
	// Open the usersFile for reading
	ifstream usersFile;
	usersFile.open(MSA_USER_FILE);

	// If it is indeed open, look for the username & password combo
	string line;
	if (usersFile.is_open()) {
		while (getline(usersFile, line)) {
			if (line.find(username) == 0)
				if (line == (username + MSA_USER_FILE_DELIMETER + password))
					return true;
		}
		return false;
	}
	else { // ERROR !
		cout << "Error reading usersFile." << endl;
		return false;
	}
}

bool MessageServerApp::userExists(string username) {
	// TODO MesageServerApp userExists
	return true;
}

bool MessageServerApp::registerUser(string username, string password) {
	// Open the usersFile for writing
	ofstream usersFile;
	usersFile.open(MSA_USER_FILE);

	// If it is indeed open, write the username & password into it
	if (usersFile.is_open()) {
		usersFile << username << MSA_USER_FILE_DELIMETER << password << endl;
		usersFile.close();
		cout << "User " << username << " added to the usersFile." << endl;
		return true;
	}
	else { // ERROR !
		cout << "Error writing to usersFile." << endl;
		return false;
	}
}

void MessageServerApp::listUsers() {
	// TODO MesageServerApp listAllUsers
	cout << "List users" << endl;
}

void MessageServerApp::listConnectedUsers() {
	// TODO MesageServerApp listAllConnectedUsers
	cout << "List connected users" << endl;
}

void MessageServerApp::listSessions() {
	// TODO MesageServerApp listAllSessions
	cout << "List sessions" << endl;
}

void MessageServerApp::listRooms() {
	// TODO MesageServerApp listAllRooms
	cout << "List rooms" << endl;
}

void MessageServerApp::listUsersInRooms(string roomName) {
	// TODO MesageServerApp listAllUsersInRooms
	cout << "List users in rooms" << endl;
}

MessageServerApp::~MessageServerApp() {
	// TODO MesageServerApp DTOR
}
