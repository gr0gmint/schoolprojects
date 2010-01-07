#include "spejleaeg.hpp"
#include <gloox/client.h>
#include "states.hpp"

void SpejleaegBot::connect() {
	this.client = new Client(this.jid, this.password);
	this.connect();
}

void SpejleaegBot::onConnect()
{
}
void SpejleaegBot::onDisconnect(ConnectionError e)
{
}
void SpejleaegBot::onTLSConnect( const CertInfo& info)
{
}

SpejleaegBot::SpejleaegBot(JID* jid, string& password)
{
	this.jid = jid;
	this.password = password;
	this.state
}
