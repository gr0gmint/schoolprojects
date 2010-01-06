#include <iostream>
#include <ctime>

int main (int argc, char * argv[]) {
	if (argc > 3 || argc < 2 ) {
		std::cout << "Usage:\nspejleaeg <XMPP-login> [<MUC-server>]\n";
	}
}
