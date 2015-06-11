
#include "MessageClientApp.h"

MessageClientApp::MessageClientApp() {

	this -> name = "tempUser";
	this -> peerName ="";
	this -> connectedToserver = false;
	this -> clientOnSession = false;
	this -> flag = true;
	this -> server = NULL;
	this -> status = -1;
	this -> listener = NULL;
	this -> listenerPort = -1;
}

int MessageClientApp::readCommand(TCPSocket* peer)
{
	int command;
	//Receiving the command
	int rc = peer->recv((char*)&command,4);
	command = ntohl(command);
	if(rc<4)
		return -1;
	return command;
}


string MessageClientApp::readData(TCPSocket* peer)
{
	int msgLen;
	//Receiving the command
	peer->recv((char*)&msgLen,4);
	msgLen = ntohl(msgLen);

	char buffer[1024];
	peer->recv(buffer,msgLen);

	string tmp = ((string)buffer).substr(0,msgLen);

	return tmp;
}

//Send a command to the server
void MessageClientApp::sendCommand(int command, TCPSocket* peer)
{
	int cmd = command;
	cmd = htonl(cmd);
	peer->send((char*)&cmd,4);
}

//Send data to server
void MessageClientApp::sendData(string data, TCPSocket* peer)
{
	int msgLen = data.length();
	msgLen = htonl(msgLen);
	peer->send((char*)&msgLen,4);
	peer->send(data.data(),data.length());
}


//Thread function with loop
void MessageClientApp::run()
{
	while(flag)
	{
		int command = readCommand(server);
		string peerName;
		string peerIpAndPort;
		string roomName;privte:

		string tmp;
		switch(command)
		{
		/*case USER_EXISTS:
			cout<<"Nope, already used, please choose another one"<<endl;
			//Disconnecting and deleting the temporally socket to server
			disconnect();
			status = -1;
			break;

		case USER_CREATED:
			cout<<"you are now a registered client, please login"<<endl;
			status = -1;
			break;

		case USER_LOGGEDIN:
			cout<<"You are logged in, I CARAMBA!"<<endl;
			connectedToserver = true;
			status = STATUS_OPEN;
			break;

		case ERROR_LOGIN:
			cout<<"Error with the login process, please try again"<<endl;
			disconnect(); //disconnecting and deleting the temporally socket to server.
			status = -1;
			break;
		 */
		case OPEN_SESSION:
			//Receiving data from server:
			peerName = readData(server);
			peerIpAndPort = readData(server);
			peers.insert(pair<string, string>(peerName, peerIpAndPort));
			//setting fields:
			clientOnSession = true;
			this->peerName = peerName;
			cout<<"New session from "<<peerName<<", you can now start talking."<<endl;
			status = SESSION_STATUS;
			break;

		case ENTER_ROOM:
			//updating list of peers connected to this user:
			tmp = readData(server);
			while(tmp.length() != 0)
			{
				peerIpAndPort = tmp.substr(0, tmp.find(";"));
				peerName = peerIpAndPort.substr(peerIpAndPort.find(",")+1, peerIpAndPort.length());
				peerIpAndPort = peerIpAndPort.substr(0 , peerIpAndPort.find(","));
				tmp = tmp.substr(tmp.find(";") + 1, tmp.length());

				peers.insert(pair<string, string>(peerName, peerIpAndPort));
				cout<<"New peer added to the peers list: "<<peerName<<" - "<<peerIpAndPort<<endl;
			}
			cout<<"Request accepted, you are now inside the chat room and you can start chatting!"<<endl;
			clientOnSession = true;
			status = STATUS_CHATROOM;
			break;

/*
		case CONNECTION_ESTABLISHED:
			//Receiving data from server:
			peerName = readData(server);
			peerIpAndPort = readData(server);
			peers.insert(pair<string, string>(peerName, peerIpAndPort));
			//setting fields:
			clientOnSession = true;
			//listener->start();//****
			this->peerName = peerName;
			cout<<"You and "<<peerName<<" can start chatting..."<<endl;
			status = STATUS_SESSION;
			break;

		case OPEN_CHATROOM:
			//Receiving data from server:
			roomName = readData(server);
			//printing and setting fields:
			cout<<"Room "<<roomName<<" Created! you are now in the room and you can start chatting!"<<endl;
			clientOnSession = true;
			status = STATUS_CHATROOM;
			this->peerName = roomName;
			break;

		case CLOSE_CHATROOM:
			status = STATUS_OPEN;
			clientOnSession = false;
			peers.clear();
			cout<<"Chat room "<<this->peerName<<" has been close by it's owner!"<<endl;
			this->peerName = "";
			break;

		case CONNECTION_REFUSED:
			cout<<"There is a problem with connection(CONNECTION_REFUSED)."<<endl;
			clientOnSession = false;
			break;
*/
/*

		case CLOSE_SESSION:
			clientOnSession = false;
			cout<<"Client disconnected from "<<this->peerName<<endl;
			this->peerName = "";

			//closing the session from udp peers vector:
			status = STATUS_OPEN;
			clientOnSession = false;
			peers.clear();
			break;
*/
		case ERROR:
			cout<<"General ERROR!"<<endl;
			break;

/*
		case ROOM_EXISTS:
			cout<<"Room already exists, choose another name!"<<endl;
			break;


		case CLOSE:
			cout<<"Shutting down."<<endl;
			close();
			break;
*/

		case LIST_USERS:
			//Receiving data from server and printing:
			tmp.clear();
			tmp = readData(server);
			cout<<tmp<<endl;
			break;

	/*	case LIST_CONNECTED_USERS:
			//Receiving data from server and printing:
			tmp.clear();
			tmp = readData(server);
			cout<<tmp<<endl;
			break;
*/

		case LIST_ROOMS:
			//Receiving data from server and printing:
			tmp.clear();
			tmp = readData(server);
			cout<<tmp<<endl;
			break;


		case LIST_USERS_IN_ROOM:
			//Receiving data from server and printing:
			tmp.clear();
			tmp = readData(server);
			cout<<tmp<<endl;
			break;

/*
		case UPDATE_USER_LIST_DEL:
			//getting the name, ip and port from server:
			peerName = readData(server);
			peerIpAndPort = readData(server);

			//deleting from list:
			peers.erase(peerName);
			break;

		case UPDATE_USER_LIST_ADD:
			//getting the name, ip and port from server:
			peerName = readData(server);
			peerIpAndPort = readData(server);
			//inserting into list:
			peers.insert(pair<string, string>(peerName, peerIpAndPort));
			break;
*/

		default:
			cout<<"Thread is ended!"<<endl;
			close();
			return;
		}
	}
}


//connect to a given server ip
bool MessageClientApp::connectToServer(string ip, int command)
{
	if(server == NULL)
	{
		flag = true;
		server = new TCPSocket(ip, SERVER_PORT);

		//getting port listening:
		this->listenerPort = readCommand(server);

		//creating new listener:
		listener = new ClientUDPListener(listenerPort);
		cout<<"New ClientUDPListener on port:"<<listenerPort<<" so client can receive & send messages"<<endl;

		//sending command to server:
		sendCommand(command,server);
		//getting & sending username & password:
		cout<<"Please enter username:"<<endl;
		string msg;
		cin>>msg;
		name = msg;
		sendData(msg,server);
		cout<<"Please enter password:"<<endl;
		cin>>msg;
		sendData(msg, server);

		//after connection - client is not on session, and starting the thread so will be able to receive messages:
		connectedToserver = true;
		clientOnSession = false;
		this->start();
		return true;
	}
	cout<<"Satla, You are already connected.."<<endl;
	return false;
}

//return true if connected to the server
bool MessageClientApp::isConnected()
{
	return connectedToserver;
}


bool MessageClientApp::disconnect() //disconnect from messenger server
{
	if(connectedToserver)
	{
		//if there is session, it will be closed
		if(clientOnSession)
			closeSession();

		//set the status & bools to false
		clientOnSession = false;
		connectedToserver = false;
		status = -1;

		//End the thread and close all socket and listeners:
		flag = false;
		server -> cclose();
		this -> waitForThread();
		delete server;
		server = NULL;
		delete listener;

		//Print disconnection info:
		cout<<"User has disconnected from the server, please connect in order to open a session" << endl;
		return true;
	}

	//Returning to the client original state.
	cout<<"Mate, you are not connected to the server.." << endl;
	flag = true;
	status = -1;
	server = NULL;
	return true;
}

//List all the users that are connected to the server
void MessageClientApp::listAllActiveUsers()
{
	//Checking if connected to server
	if(connectedToserver)
	{
		//Sending server command
		sendCommand(LIST_USERS, server);
	}
	else
	{
		cout<<"Mate, you are not connected to server.. in oredr to recive the users list, please connect to the server" << endl;
		return;
	}
}

//List all active rooms that open on the server
void MessageClientApp::listAllOpenRooms()
{
	//Check if client is connected to server
	if(connectedToserver)
	{
		//Send a command to the server
		sendCommand(LIST_ROOMS, server);
	}
	else
	{
		cout<<"Mate, you are not connected to server.. in oredr to recive the room list, please connect to the server"<<endl;
		return;
	}
}

//List all users inside a specific room
void MessageClientApp::listUsersOnChatRoom(string roomName)
{
	//Check if client is connected to the server
	if(connectedToserver)
	{
		//Send command to the server
		sendCommand(LIST_USERS_IN_ROOM, server);
		//Send requested room name
		sendData(roomName, server);
	}
	else
	{
		cout<<"Mate, you are not connected to server.. in order to recive room- "<<roomName<<" user list, please connect to the server"<<endl;
		return;
	}
}

//Open session with peer
void MessageClientApp::openSessionWithPeer(string peerName)
{
	//Check if there is a connection already
	if(status == SESSION_STATUS || status == ROOM_STATUS)
	{
		cout<<"There is an open session already, close all sessions and try opening a new one"<<endl;
		return;
	}
	else if(status < STATUS_OPEN)
	{
		cout<<"Mate, you are not connected to the server.."<<endl;
		return;
	}
	else
	{
		//Send command to server
		sendCommand(OPEN_SESSION, server);
		//Send name of peer to session
		sendData(peerName, server);
		cout<<"Sending session request to the server..."<<endl;
	}
}

void MessageClientApp::joinAChatRoom(string chatRoomName)
{
	//Check if there is a connection already
	if(status == SESSION_STATUS || status == ROOM_STATUS)
	{
		cout<<"There is an open session already, close all sessions and try opening a new one"<<endl;
		return;
	}
	else if(status < STATUS_OPEN)
	{
		cout<<"Mate, you are not connected to the server.."<<endl;
		return;
	}
	else
	{
		//Set the peer name
		peerName = chatRoomName;

		//Send a command to the server
		sendCommand(ENTER_ROOM, server);

		//Send name of peer to the session
		sendData(chatRoomName, server);
		cout<<"Sending request to join chat room - "<<chatRoomName<<endl;
	}
}

void MessageClientApp::createNewChatRoom(string roomName)
{
	//Check if you are already connected
	if(status == SESSION_STATUS || status == ROOM_STATUS)
	{
		cout<<"There is an open session already, close all sessions and try opening a new one"<<endl;
		return;
	}
	else if(status < STATUS_OPEN)
	{
		cout<<"Mate, you are not connected to the server.."<<endl;
		return;
	}
	else
	{
		//Send a command to the server
		sendCommand(OPEN_CHATROOM, server);

		//Send the name of the room to the server
		sendData(roomName, server);
	}
}

void MessageClientApp::deleteChatRoom(string roomName)
{
	//Check if you are already connected
	if(status < STATUS_OPEN)
		cout<<"Mate, you are not connected to the server.."<<endl;
	else
	{
		//Send a command to the server
		sendCommand(CLOSE__CHATROOM, server);

		//Send the name of the room to the server
		sendData(roomName, server);

		//Send the name of the requested user to the server:
		sendData(name, server);
	}
}

//sends message to a peer or a chat room
void MessageClientApp::sendMessageToPeer(string message)
{
	//Check if you are connected
	if(status < STATUS_OPEN)
		cout<<"Mate, you are not connected to the server.."<<endl;
	else if(status == STATUS_OPEN)
		cout<<"Mate, you need to open a session first.. What a child.."<<endl;
	else
	{
		//List of peers that are connected
		tOpenedPeers::iterator iter;
		for(iter = peers.begin(); iter != peers.end() ; iter++)
		{
			string peer = (*iter).second;
			int tmp = peer.find(":");
			string ipString = peer.substr(0,tmp);
			string portString = peer.substr(tmp+1, peer.length());
			int port = atoi(portString.c_str());
			//Send the message:
			listener->getUDPSocket()->sendTo(("["+name+"]: "+message), ipString, port);
		}
	}
}

//print client status
void MessageClientApp::printClientStatus()
{
	switch(status)
	{
	case STATUS_OPEN:
		cout<<"Client status is 'open' and it is connected to the server ("<<server->fromAddr()<<")."<<endl;
		break;

	case SESSION_STATUS:
		cout<<"Client status is 'Session' and it is connected to user: "<<peerName<<endl;
		break;

	case ROOM_STATUS:
		cout<<"Client status is 'Chat Room' and it is connected to room: "<<peerName<<endl;
		break;

	default:
		cout<<"Mate, you need to be connected to server first.. What a child.."<<endl;
		break;
	}
}

//Close session with peer or Close chat room
void MessageClientApp::closeSession()
{
	if(status == SESSION_STATUS)
		sendCommand(CLOSE_SESSION, server);
	else if(status == ROOM_STATUS)
	{
		//Sending everyone message that you are exiting - bey bey fuckers!
		sendMessageToPeer(name+" has left the room! I will be back!\n");

		//Send command to the server - I Obay YOU!
		sendCommand(CLOSE__CHATROOM, server);
		sendData(peerName, server);

		//Print info
		cout<<name<<" has left the chat room! bey bey fuckers "<<peerName<<endl;
		peerName = "";
		status = STATUS_OPEN;
		clientOnSession = false;
		peers.clear();
	}
	else
		cout<<"There are no sessions to close.. WHAT IS WRONG WITH YOU???"<<endl;
}

//Close the messenger
void MessageClientApp::close()
{
	if(connectedToserver)
		disconnect();
	flag = false;
	this -> waitForThread();
	cout<<"Bey Bey!"<<endl;
}


MessageClientApp::~MessageClientApp(){

}









































































