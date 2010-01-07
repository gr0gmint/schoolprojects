#include "spejleaeg.hpp"
#include <gloox/client.h>
#include "states.hpp"
#include <string>

void SpejleaegBot::connect() {
	this->client->connect();
	this->state = BOT_CONNECTING;
}

void SpejleaegBot::onConnect()
{
	this->state = BOT_CONNECTED;
}
void SpejleaegBot::onDisconnect(ConnectionError e)
{
	this->state = BOT_DISCONNECTED;
}
bool SpejleaegBot::onTLSConnect( const CertInfo& info )
{
	return true;
}

SpejleaegBot::SpejleaegBot(JID* jid, string& password)
{
	this->jid = jid;
	this->password = password;
	this->client = new Client(*(this->jid), this->password);
	this->client->registerConnectionListener( this );
	this->client->registerPresenceHandler( this );
	this->state = BOT_DEAD;
}

SpejleaegBot::~SpejleaegBot(){
	
}

void SpejleaegBot::handlePresence(const Presence& presence) {
	
}
