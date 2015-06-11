/*
 * ClientUDPListener.h
 * Authors:Niv Moran-Rabin 301220778 & Liran Sheinbox 032557225
 */

#ifndef CLIENTUDPLISTENER_H_
#define CLIENTUDPLISTENER_H_
#include "MThread.h"
#include "UDPSocket.h"

using namespace std;

class ClientUDPListener : public MThread {
	UDPSocket* listener;

public:
	bool flag;
	ClientUDPListener(int port);
	UDPSocket* getUDPSocket();
	void run();
	virtual ~ClientUDPListener();
};

#endif /* CLIENTUDPLISTENER_H_ */
