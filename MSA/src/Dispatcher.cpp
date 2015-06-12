
#include "Dispatcher.h"

Dispatcher::Dispatcher(tConnectedClients* connectedClients, MessageServerApp* server) {
	this->serverRunning = true;
	this->connectedClients = connectedClients;
	this->msa = server;
	this->multiListener = NULL;
	this->chatClients = NULL;
	this->sessionClients = NULL;
}

void Dispatcher::sendData(string data, TCPSocket* client)
{
	// Prepare data to be sent through the network, and send it
	int msgLen = data.length();
	msgLen = htonl(msgLen);
	client->send((char*)&msgLen,4);
	client->send(data.data(), data.length());
}

void Dispatcher::sendUserList(TCPSocket* client)
{
	string line;
	string data = "User List:\n";
	ifstream usersFile(MSA_USER_FILE);

	if(usersFile.is_open())
	{
		while(getline(usersFile, line))
			data = data + line.substr(line.find(MSA_USER_FILE_DELIMETER)+1, line.length()) + "\n";

		usersFile.close();
	}
	else { // ERROR !
		cout << "Error reading usersFile." << endl;
		msa->sendCommand(ERROR, client);
		return;
	}

	//sending client the user list:
	msa->sendCommand(LIST_USERS, client);
	cout<<"Sending user list to: "<< client->getIPandPort() << endl;
	sendData(data, client);
}


void Dispatcher::sendConnectedUserList(TCPSocket* client)
{
	string key;
	string data ="Connected User List:\n";

	for( tConnectedClients::iterator iter = connectedClients->begin(); iter!=connectedClients->end() ; iter++)
	{
		key = (*iter).first;

		//printing the information:
		data = data + key + "\n";
	}

	// sending data to client
	msa->sendCommand(LIST_CONNECTED_USERS, client);
	cout << "Sending connected users list to: "<< client->getIPandPort() << endl;
	sendData(data, client);
}


void Dispatcher::sendRoomsList(TCPSocket* client)
{
	string data ="Room List:\n";
	Chat* chat = NULL;

	for(tChatClients::iterator iter = chatClients->begin() ; iter!=chatClients->end() ; iter++) {
		// Geting chat info
		chat = (*iter).second;
		// TODO
//		data = data + chat->getName() + ", owner: " + chat->getUserOwner()->getUsername() + "\n";
	}

	// Sending data to client
	msa->sendCommand(LIST_ROOMS, client);
	cout << "Sending rooms list to: " << client->getIPandPort() << endl;
	sendData(data, client);
}


void Dispatcher::sendConnectedUsersToRoom(TCPSocket* client)
{
	bool roomExists = false;
	string roomName = msa->readData(client);
	string data = "Room Users List:\n";
	Chat* chat = NULL;
	for(tChatClients::iterator iter = chatClients->begin() ; iter!=chatClients->end() ; iter++) {
		// Getting chat info
		chat = (*iter).second;
		// TODO
		/*if(chat->getName() == roomName) {
			roomExists = true;//if there is such room
			data = data + chat->getName() + ": ";

			// Gather usernames
			vector<User*> chatUsers = chat->getUsers();
			for(vector<User*>::iterator iter1=chatUsers.begin(); iter1!=chatUsers.end(); iter1++)
				data = data + (*iter1)->getUsername() + " ";
			data = data + "\n";
		}*/
	}
	//if there is no such room will send this:
	if(roomExists == false)
		data = "Room does not exist!\n";

	// Sending data to client
	msa->sendCommand(LIST_USERS_IN_ROOM, client);
	cout<<"Sending users in room list to: " << client->getIPandPort() << endl;
	sendData(data, client);
}


void Dispatcher::run()
{
	while(serverRunning)
	{
		if (multiListener!=NULL)
			delete multiListener;

		multiListener = new MultipleTCPSocketsListener();

		TCPSocket* client;

		// Adding all peers to multiple listener
		for(tConnectedClients::iterator iter = connectedClients->begin() ; iter!=connectedClients->end() ; iter++)
		{
			//getting information:
			client = (*iter).second->getSocket();

			//adding to list:
			multiListener->addSocket(client);
		}

		// Clients that are connected to others
		for(tSessionClients::iterator iter = sessionClients->begin() ; iter != sessionClients->end() ; iter++) {
			//getting information:
			client = (*iter).second->getSocket();

			//adding to list:
			multiListener->addSocket(client);
		}

		// Clients that connected to chats
		// TODO
		/*for(tChatClients::iterator iter = chatClients->begin(); iter!=chatClients->end() ; iter++){
			Chat* chat = (*iter).second;
			vector<User*> chatUsers = chat->getUsers();


			for(vector<User*>::iterator iter2 = chatUsers.begin() ; iter2!=chatUsers.end() ; iter2++) {
				// Getting info and add to the multi list
				client = (*iter2)->getSocket();
				multiListener->addSocket(client);
			}
		}*/


		// Listening to all clients connected to the server
		client = multiListener->listenToSocket(2);
		if (client == NULL ) continue; //if nothing returned from multiple tcp listener.

		// Read client command
		int command = msa->readCommand(client);

		// Handle command
		switch(command) {

/*		case OPENSESSION:
			openSession(client);
			break;

		case CLOSESESSION:
			closeSession(client);
			break;

		case OPEN_CR:
			openChat(client);
			break;

		case CLOSE_CR:
			closeChat(client);
			break;

		case JOIN_CR:
			joinChat(client);
			break;

		case LEAVE_CR:
			leaveChat(client);
			break;

		case SEND_USER_LIST:
			sendUserList(client);
			break;

		case SEND_CONNECTED_USER_LIST:
			sendConnectedUserList(client);
			break;

		case SEND_ROOM_LIST:
			sendRoomsList(client);
			break;

		case SEND_ROOM_USERS:
			sendConnectedUsersToRoom(client);
			break;*/

		default:
			//user disconnected:
			clientDisconnected(client);
			break;
		}
	}
}

void Dispatcher::clientDisconnected(TCPSocket* client)
{
	// So that we won't crash
	if(client == NULL) return;

	string key = client->getIPandPort();
	string data;
	User* tmpUser = NULL;

	// Iterate "connected" clients
	for(tConnectedClients::iterator iter = connectedClients->begin() ; iter != connectedClients->end() ; iter++) {
		if(key == (*iter).second->getSocket()->getIPandPort())
			tmpUser = (*iter).second;
	}

	// If user found -> delete it
	if(tmpUser != NULL) {
		lock();
		connectedClients->erase(tmpUser->getUsername());
		unlock();
	}


	// Iterate clients in a session
	for(tSessionClients::iterator iter = sessionClients->begin() ; iter != sessionClients->end() ; iter++) {
		if(key == (*iter).second->getSocket()->getIPandPort()){
			tmpUser = (*iter).second;
			data = (*iter).first;
		}
	}

	// If found -> delete it
	sessionClients->erase(data); //deleting the user that already disconnected:
	tSessionClients::iterator iter = sessionClients->find(tmpUser->getUsername());
	if(iter != sessionClients->end()) {
		msa->sendCommand(CLOSE_SESSION, (*iter).second->getSocket());
		lock();
		connectedClients->insert(pair<string,User*>((*iter).second->getUsername(), (*iter).second));
		unlock();
		cout << (*iter).second->getUsername() << " moved to connected clients from session clients due to disconnection!" << endl;
		sessionClients->erase((*iter).first);
	}


	// Iterate chats
	Chat* chat = NULL;

	// TODO
	/*for( tChatClients::iterator iter = chatClients->begin(); iter != chatClients->end() ; iter++) {
		chat = (*iter).second;
		vector<User*> chatUsers = chat->getUsers();

		for(vector<User*>::iterator iter2 = chatUsers.begin(); iter2 != chatUsers.end(); iter2++) {
			if(key == (*iter2)->getSocket()->getIPandPort()) {
				tmpUser = (*iter2);
				chat->removeUser(tmpUser);
			}
		}
	}
*/
	// Delete user from mem
	if(tmpUser != NULL) {
		cout << tmpUser->getUsername() << " disconnected from server. So long s***er." << endl;
		delete tmpUser;
	}
}


void Dispatcher::openSession(TCPSocket* client) {
	User* tmpUser1=NULL;
	User* tmpUser2=NULL;

	// Get username for connection from client
	string username = msa->readData(client);

	// Find the username
	for(tConnectedClients::iterator iter = connectedClients->begin(); iter != connectedClients->end() ; iter++) {
		// Get info
		if ((*iter).second->getSocket() == client)
			tmpUser1 = (*iter).second;
		if ((*iter).second->getUsername() == username)
			tmpUser2 = (*iter).second;
	}

	// Checking if username found
	if (tmpUser1 != NULL && tmpUser2 != NULL) {
		// Deleting from Connected Clients because other users can't open a session with them
		lock();
		connectedClients->erase(tmpUser1->getUsername());
		connectedClients->erase(tmpUser2->getUsername());
		unlock();
		// Inserting both users to session peers list:
		sessionClients->insert(pair<string,User*>(tmpUser2->getUsername(),tmpUser1));
		sessionClients->insert(pair<string,User*>(tmpUser1->getUsername(),tmpUser2));

		// Changing status and names of sessions:
//		tmpUser1->setStatus(STATUS_SESSION);
//		tmpUser2->setStatus(STATUS_SESSION);
		tmpUser1->setSessionName(tmpUser2->getUsername());
		tmpUser2->setSessionName(tmpUser1->getUsername());

		// Send messages to users
		msa->sendCommand(OPEN_SESSION, tmpUser2->getSocket());
		sendData(tmpUser1->getUsername(), tmpUser2->getSocket());
		sendData(tmpUser1->getSocket()->getIPandPort(), tmpUser2->getSocket());
		msa->sendCommand(OK, tmpUser1->getSocket());
		sendData(tmpUser2->getUsername(), tmpUser1->getSocket());
		sendData(tmpUser2->getSocket()->getIPandPort(), tmpUser1->getSocket()); // Sending the address of the connected peer.

		// Status to screen
		cout << tmpUser1->getUsername() << " and " << tmpUser2->getUsername() << " should now start talking." << endl;
	}
	else
		if (tmpUser2==NULL)
			msa->sendCommand(ERROR, client);
}


void Dispatcher::closeSession(TCPSocket* peer) {
	// TODO Dispatcher::closeSession()
	/*User* tmpUser1=NULL;
	User* tmpUser2=NULL;

	//finding the username:

	connectedPeers::iterator iter;
	for( iter = peersOnSession.begin() ; iter!=peersOnSession.end() ; iter++)
	{
		//getting information:
		if((*iter).second->getPeer()==peer)
			tmpUser1 = (*iter).second;
	}
	//finding the other user:
	if(tmpUser1!=NULL)
	{

		for( iter = peersOnSession.begin(); iter!=peersOnSession.end() ; iter++)
		{
			//getting information:
			if((*iter).first == tmpUser1->getName())
				tmpUser2 = (*iter).second;
		}

		//after finding both:
		if(tmpUser2 != NULL)
		{
			peersOnSession.erase(tmpUser2->getName());
			lock();
			openedPeers->insert(pair<string,User*>(tmpUser2->getName(),tmpUser2));
			unlock();
			msa->sendCommand(CLOSESESSION, tmpUser2->getPeer());

			//printing:
			cout<<tmpUser1->getName()<<" and "<<tmpUser2->getName()<<" stop talking."<<endl;
		}
		peersOnSession.erase(tmpUser1->getName());
		lock();
		openedPeers->insert(pair<string,User*>(tmpUser1->getName(),tmpUser1));
		unlock();
		msa->sendCommand(CLOSESESSION, tmpUser1->getPeer());
	}*/
}


void Dispatcher::openChat(TCPSocket* peer) {
	// TODO Dispatcher::openChat
	/*User* tmpUser=NULL;

	//finding the username which want to open the chat room:
	for(connectedPeers::iterator iter = openedPeers->begin() ; iter!=openedPeers->end() ; iter++)
	{
		//getting information:
		if((*iter).second->getPeer()==peer)
			tmpUser = (*iter).second;
	}

	if(tmpUser != NULL)
	{
		//creating new Chat:
		string ChatName = msa->readData(peer);

		//checking if already exists chat room with this name:
		for(tChatClients::iterator iter1 = chatClients.begin() ; iter1!=chatClients.end() ; iter1++)
		{
			if(ChatName == ((*iter1).first))
			{
				msa->sendCommand(ROOM_ALREADY_EXISTS,peer);
				return;
			}
		}
		//if name doesn't exists then will create room and send the right data:
		Chat* tmpChat = new Chat(ChatName, tmpUser);

		//insert into chat rooms list and deleting from opened peers:
		chatClients.insert(pair<string,Chat*>(ChatName,tmpChat));
		lock();
		openedPeers->erase(tmpUser->getName());
		unlock();


		//sending command to user that succeed:
		msa->sendCommand(OPEN_CR,peer);
		sendData(ChatName, peer);

		//editing user:
		tmpUser->setStatus(STATUS_Chat);
		tmpUser->setSessionName(ChatName);

		//printing:
		cout<<"New chat room: "<<tmpChat->getName()<<" owened by: "<<tmpUser->getName()<<endl;
	}
	else
		//we didn't found the user on open peers so we send connection refused:
		msa->sendCommand(CONNECTION_REFUSED, peer);*/
}


void Dispatcher::closeChat(TCPSocket* peer) {
	// TODO Dispatcher::closeChat()
	/*string ChatName = msa->readData(peer);
	string requestByUserName = msa->readData(peer);

	//finding the Chat:
	tChatClients::iterator iter = chatClients.find(ChatName);
	if(iter != chatClients.end())
	{
		Chat* tmpChat = (*iter).second;
		//checking if the user is the owner:
		if(peer == tmpChat->getOwner()->getPeer() || requestByUserName == tmpChat->getOwnerName())//*********************
		{
			tmpChat->sendMessageCloseChat();//letting all user know that chat room is closed.
			//getting vector of users:
			vector<User*> tmpUsersVector = tmpChat->getUsers();
			//inserting all specific users to opened peers list:

			for(vector<User*>::iterator iter=tmpUsersVector.begin(); iter!=tmpUsersVector.end(); iter++)
			{
				lock();
				openedPeers->insert(pair<string,User*>((*iter)->getName(),(*iter)));
				unlock();
			}
			//deleting the Chat from list:
			chatClients.erase(tmpChat->getName());
			cout<<"Chat room: "<<tmpChat->getName()<<" deleted!"<<endl;
			delete tmpChat;
		}
		else
			msa->sendCommand(ERROR, peer);
	}
	else
		msa->sendCommand(ERROR, peer);*/
}


void Dispatcher::joinChat(TCPSocket* peer) {
	// TODO Dispatcher::joinChat()
	/*User* tmpUser = NULL;
	string ChatName = msa->readData(peer);
	//finding the chat room:
	tChatClients::iterator iter = chatClients.find(ChatName);
	if(iter != chatClients.end())
	{
		//finding the user:
		for(connectedPeers::iterator iter1 = openedPeers->begin() ; iter1!=openedPeers->end() ; iter1++)
		{
			//getting information:
			if((*iter1).second->getPeer()==peer)
				tmpUser = (*iter1).second;
		}

		if(tmpUser != NULL)
		{
			//deleting from open peers:
			lock();
			openedPeers->erase(tmpUser->getName());
			unlock();
			//adding to chat room:
			((*iter).second)->addUser(tmpUser);
			//changing status:
			tmpUser->setStatus(STATUS_Chat);
			tmpUser->setSessionName(((*iter).second)->getName());

			//printing:
			cout<<tmpUser->getName()<<" joined the chat room: "<<((*iter).second)->getName()<<endl;
			msa->sendCommand(JOIN_CR, peer);//sending succeed command.

			//sending the list of peers inside the chat room:
			string chatClients;
			vector<User*> tmpUsersVector = (*iter).second->getUsers();

			for(vector<User*>::iterator iter2=tmpUsersVector.begin(); iter2!=tmpUsersVector.end(); iter2++)
				if((*iter2) != tmpUser)
					chatClients += (*iter2)->getPeer()->destIpAndPort()+","+(*iter2)->getName()+";";
			sendData(chatClients, peer);
		}
	}
	else
		msa->sendCommand(CONNECTION_REFUSED, peer);*/
}


void Dispatcher::leaveChat(TCPSocket* peer) {
	// TODO Dispatcher::leaveChat()
	/*string ChatName = msa->readData(peer);

	User* tmpUser = NULL;

	//finding the chat room:
	tChatClients::iterator iter = chatClients->find(ChatName);
	if(iter != chatClients->end())
	{
		Chat* tmpChat = (*iter).second;

		//finding and deleting the user:
		vector<User*> tmpUsersVector = tmpChat->getUsers();
		vector<User*>::iterator iter1;
		for(iter1=tmpUsersVector.begin(); iter1!=tmpUsersVector.end(); iter1++)
			if((*iter1)->getPeer() == peer)
				tmpUser = (*iter1);
		if(tmpUser != NULL)
		{
			//deleting from chat room and adding to opened peers:
			tmpChat->deleteUser(tmpUser);
			lock();
			openedPeers->insert(pair<string,User*>(tmpUser->getName(),tmpUser));
			unlock();
			//setting status:
			tmpUser->setStatus(STATUS_OPEN);

			//printing:
			cout<<"User: "<<tmpUser->getName()<<" left chat room "<<tmpChat->getName()<<endl;
		}
		else
			msa->sendCommand(ERROR, peer);
	}
	else
		msa->sendCommand(ERROR, peer);*/
}

//Prints all the session from the session map
void Dispatcher::listSessions() {
	// TODO Dispatcher::listSessions()
	/*User* user = NULL;

	for(tSessionPeers::iterator iter = peersOnSession.begin() ; iter!=peersOnSession.end() ; iter++)
	{
		//getting and printing information:
		user = (*iter).second;
		cout<<"The user: "<<user->getName()<<" is talking with: "<<user->getSessionName()<<endl;
	}*/
}

//Prints all the rooms from the room's map
void Dispatcher::printRoom() {
	// TODO Dispatcher::printRoom()
	/*Chat* Chat = NULL;

	for(tChatClients::iterator iter = chatClients.begin(); iter!=chatClients.end() ; iter++)
	{
		//getting and printing information:
		Chat = (*iter).second;
		cout<<"Chat room: "<<Chat->getName()<<" is open. owner: "<<Chat->getOwner()->getName()<<endl;
	}*/
}


void Dispatcher::printUsersInRooms(string roomName) {
	// TODO Dispatcher::printUsersInRooms
	/*Chat* Chat = NULL;

	for(tChatClients::iterator iter = chatClients.begin() ; iter!=chatClients.end() ; iter++)
	{
		//getting and printing information:
		Chat = (*iter).second;
		if(Chat->getName() == roomName)
		{
			cout<<"List of users on "<<Chat->getName()<<":"<<endl;
			//printing users:
			vector<User*> tmpUsersVector = Chat->getUsers();

			for(vector<User*>::iterator iter1=tmpUsersVector.begin(); iter1!=tmpUsersVector.end(); iter1++)
				cout<<(*iter1)->getName()<<endl;
		}
	}*/
}

void Dispatcher::lock() {
	pthread_mutex_lock(msa->getMutex());
}

void Dispatcher::unlock() {
	pthread_mutex_unlock(msa->getMutex());
}

Dispatcher::~Dispatcher() {
	// Deleting connected clients
	User* tmpUser = NULL;

	for(tConnectedClients::iterator iter = connectedClients->begin() ; iter != connectedClients->end() ; iter++) {
		// Getting and deleting information:
		tmpUser = (*iter).second;
		msa->sendCommand(DISCONNECT, tmpUser->getSocket());
		tmpUser->getSocket()->cclose();
		lock();
		connectedClients->erase(tmpUser->getUsername());
		unlock();
		delete tmpUser;
	}

	// Deleting clients in session
	for(tSessionClients::iterator iter = sessionClients->begin() ; iter!=sessionClients->end() ; iter++)
	{
		// Getting and deleting
		tmpUser = (*iter).second;
		msa->sendCommand(DISCONNECT, tmpUser->getSocket());
		tmpUser->getSocket()->cclose();
		sessionClients->erase(tmpUser->getUsername());
		delete tmpUser;
	}

	// Deleting chat rooms and the clients on them
	Chat* chat = NULL;

	for( tChatClients::iterator iter = chatClients->begin(); iter != chatClients->end() ; iter++) {
		//getting and printing information:
		chat = (*iter).second;

		// Deleting users
		// TODO
/*
		vector<User*> tmpUsersVector = chat->getUsers();

		for(vector<User*>::iterator iter2=tmpUsersVector.begin(); iter2 != tmpUsersVector.end(); iter2++) {
			tmpUser = (*iter2);
			msa->sendCommand(DISCONNECT, tmpUser->getSocket());
			tmpUser->getSocket()->cclose();
			delete tmpUser;
		}
*/

		// Deleting the chat room itself
		// TODO
//		chatClients->erase(chat->getName());
		delete chat;
	}
}
