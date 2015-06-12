#ifndef CHAT_H_
#define CHAT_H_
#include <strings.h>
#include <vector>
#include "User.h"
#include "MessageServerAppProtocol.h"

using namespace std;

class Chat {
	vector<User*> users;
	string name;
	string ownerName;
	User* userOwner;
public:
	Chat(string name, User* userOwner);

	string getName();
	string getOwnerName();
	User* getUserOwner();
	vector<User*> getUsers();

	void addUser(User* user);
	void removeUser(User* user);
	void sendMessageCloseChatRoom();
	void sendCommand(int command, TCPSocket* peer);
	void sendData(string data, TCPSocket* peer);
	void sendUpdateToUsersList(User* user, int command);
	virtual ~Chat();
};
#endif /* CHAT_H_ */
