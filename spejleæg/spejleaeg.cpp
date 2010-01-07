#include "spejleaeg.hpp"
#include <gloox/client.h>
#include "states.hpp"

void SpejleaegBot::connect() {
	this.connect();
}

void SpejleaegBot::onConnect()
{
	this.state = BOT_CONNECTED;
}
void SpejleaegBot::onDisconnect(ConnectionError e)
{
	this.state = BOT_DISCONNECTED;
}
bool SpejleaegBot::onTLSConnect( const CertInfo& info )
{
	return true;
}

SpejleaegBot::SpejleaegBot(string& jid, string& password)
{
	this.jid = new JID(jid);
	this.password = password;
	this.client = new Client(this.jid, this.password);
	this.state = BOT_DEAD;
}

void SpejleaegBot::handlePresence(Presence* presence) {
}

