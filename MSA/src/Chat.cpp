// TODO Chat.cpp
/*

#include "Chat.h"

Chat::Chat(string name, User* userOwner) {
	//printing massage:
	cout<<"New chat room created: "<<name<<endl;
	this->name = name;
	this->ownerName = userOwner->getUsername();
	this->userOwner = userOwner;
	users.push_back(userOwner);
}

void Chat::addUser(User* user)
{
	users.push_back(user);

	//sending the new list of users to every user:
	sendUpdateToUsersList(user, UPDATE_USER_LIST_ADD);
}


void Chat::removeUser(User* user)
{
	//searching with iterators for the specific user on vector:
	vector<User*>::iterator iter;
	for(iter=users.begin(); iter!=users.end(); iter++)
	{
		if((*iter)==user)
		{
			//if found, delete it from vector:
			users.erase(iter);
			break;
		}
	}
	//sending the new list of users to every user:
	sendUpdateToUsersList(user, UPDATE_USER_LIST_DEL);
}


void Chat::sendUpdateToUsersList(User* user, int command)
{
	User* tempUser = NULL;
	vector<User*>::iterator iter;
	for(iter=users.begin(); iter!=users.end(); iter++)
	{
		tempUser = (*iter);
		if(tempUser != user)
		{
			sendCommand(command, tempUser->getSocket());
			sendData(user->getUsername(), tempUser->getSocket());
			sendData(user->getSocket()->destIpAndPort(),tempUser->getSocket());
		}
	}
}


string Chat::getName()
{
	return name;
}

string Chat::getOwnerName()
{
	return ownerName;
}


User* Chat::getUserOwner()
{
	return userOwner;
}


vector<User*> Chat::getUsers()
{
	return users;
}


void Chat::sendMessageCloseChat()
{
	User* tmpUser=NULL;

	vector<User*>::iterator iter;
	for(iter=users.begin(); iter!=users.end(); iter++)
	{
		tmpUser = (*iter);
		sendCommand(CLOSE_CR,tmpUser->getPeer());
		tmpUser->setStatus(STATUS_OPEN);
		//We will insert the user to open peers list on dispatcher.
	}
}


void Chat::sendCommand(int command, TCPSocket* peer)
{
	int cmd = command;
	cmd = htonl(cmd);
	peer->send((char*)&cmd,4);
}


void Chat::sendData(string data, TCPSocket* peer)
{
	int msgLen = data.length();
	msgLen = htonl(msgLen);
	peer->send((char*)&msgLen,4);
	peer->send(data.data(),data.length());
}


Chat::~Chat() {}
*/
