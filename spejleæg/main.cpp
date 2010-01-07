#include <iostream>
#include <ctime>
#include "spejleaeg.hpp"

int main (int argc, char * argv[]) {
	
	string password;
	
	if (argc > 3 || argc < 2 ) {
		std::cout << "Usage:\nspejleaeg <XMPP-login> [<MUC-server>]\n";
		return -1;
	}
	JID jid ( string(argv[1]) );
	if (!jid) {
		std::cout << "XMPP-login is invalid\n";
		return -1;
	}
	std::cout << "Indtast password: ";
	std::cin >> password;
	SpejleaegBot* bot = new SpejleaegBot(jid,)
}
