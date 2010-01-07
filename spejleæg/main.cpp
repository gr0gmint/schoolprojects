#include <iostream>
#include <ctime>
#include "spejleaeg.hpp"
#include <gloox/jid.h>
#include <string>

using namespace gloox;
using namespace std;

int main (int argc, char * argv[]) {
	
	string password;
	
	if (argc > 3 || argc < 2 ) {
		std::cout << "Usage:\nspejleaeg <XMPP-login> [<MUC-server>]\n";
		return -1;
	}
	string ggnore = argv[1];
	JID jid (ggnore);
	if (!(jid)) {
		std::cout << "XMPP-login er ugyldigt\n";
		return -1;
	}
	if (jid.resource().empty()) {
		jid.setResource("ff");
	}
	std::cout << "Indtast kodeord: ";
	std::cin >> password;
	SpejleaegBot* bot = new SpejleaegBot(&(jid),password);
	bot->connect();
}
