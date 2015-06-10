#include "MultipleTCPSocketsListener.h"

using namespace std;

void MultipleTCPSocketsListener::addSocket(TCPSocket* socket)
{
	this->sockets.push_back(socket);
}

void MultipleTCPSocketsListener::removeSocket(TCPSocket * socket){
	vector<TCPSocket*>::iterator position = find(this->sockets.begin(), this->sockets.end(), socket);
	if(position != this->sockets.end())
		this->sockets.erase(position);
}

void MultipleTCPSocketsListener::addSockets(vector<TCPSocket*> socketVec)
{
	this->sockets = socketVec;
}

TCPSocket* MultipleTCPSocketsListener::listenToSocket(int timeout)
{
	struct timeval tv = {timeout, 0};

	tSocketsContainer::iterator iter = this->sockets.begin();

	tSocketsContainer::iterator endIter = this->sockets.end();

	fd_set fdset;

	FD_ZERO(&fdset);
	int highfd = 0;

	//fill the set with file descriptors
	for (;iter != endIter;iter++)
	{
		highfd++;
		FD_SET((*iter)->getSocketFid(), &fdset);
	}

	//perform the select
	int returned;
	if (timeout>0)
	{
		returned = select(sizeof(fdset)*8, &fdset, NULL, NULL, &tv);
	}
	else
	{
		returned = select(sizeof(fdset)*8, &fdset, NULL, NULL, NULL);
	}

	if (returned > 0)
	{
		for (int i = 0; i < highfd; i++)
		{
			TCPSocket* tmpSocket = this->sockets[i];
			if (FD_ISSET(tmpSocket->getSocketFid(), &fdset))
			{
				return tmpSocket;
			}
		}
	}

	return NULL;
}
