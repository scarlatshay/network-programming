#ifndef MULTIPLETCPSOCKETSLISTENER_H_
#define MULTIPLETCPSOCKETSLISTENER_H_

#include <iostream>
#include <stdio.h>
#include <vector>
#include <algorithm>
#include <sys/types.h>
#include <sys/select.h>
#include "TCPSocket.h"

using namespace std;


class MultipleTCPSocketsListener{
	typedef vector<TCPSocket*> tSocketsContainer;
	tSocketsContainer sockets;

public:
	/*
	 * Add the given socket to the socket list to be listen on
	 */
	void addSocket(TCPSocket* socket);

	/*
	 * Remove the given socket from the list
	 */
	void removeSocket(TCPSocket * socket);

	/*
	 * Add the given sockets to the socket list to be listen on
	 */
	void addSockets(vector<TCPSocket*> socketVec);

	/*
	 * This method checks to see if any of the previous given sockets are ready for reading
	 * It returns one of the Sockets that are ready.
	 */
	TCPSocket* listenToSocket(int timeout=0);
};


#endif /* MULTIPLETCPSOCKETSLISTENER_H_ */
