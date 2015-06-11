/*
 * ClientUDPListener.cpp
 * Authors:Niv Moran-Rabin 301220778 & Liran Sheinbox 032557225
 */

#include "ClientUDPListener.h"

ClientUDPListener::ClientUDPListener(int port) {
	// TODO Auto-generated constructor stub
	flag = true;
	listener = new UDPSocket(port);
	//start listening
	this->start();
}

void ClientUDPListener::run()
{
	char buffer[1024];
	while(flag)
	{
		bzero(buffer, 1024);
		listener->recv(buffer, 1024);
		cout<<buffer<<endl;
	}
}

UDPSocket* ClientUDPListener::getUDPSocket(){
	return listener;
}


ClientUDPListener::~ClientUDPListener() {
	// TODO Auto-generated destructor stub
	flag = false;
	listener->cclose();
	delete listener;
	cout<<"Client UDP listener is off"<<endl;
}

