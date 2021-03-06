#include <gloox/client.h>
#include <gloox/messagesession.h>
#include <gloox/messagesessionhandler.h>
#include <gloox/messagehandler.h>
#include "states.hpp"
#include <string>
#include <iostream>
#include "spejleaeg.hpp"
#include "spil.hpp"

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
	this->client->registerMessageHandler( this);
	this->client->registerMessageSessionHandler( this);
	this->state = BOT_DEAD;
}

SpejleaegBot::~SpejleaegBot(){
	
}

void SpejleaegBot::handlePresence(const Presence& presence) {
	std::cout << "A presence stanza was received\n";
}

void SpejleaegBot::handleMessageSession( MessageSession * session)
{
	session->registerMessageHandler( this);
	std::cout << "Message session created\n";
}
void SpejleaegBot::handleMessage( const Message& message, MessageSession* session) {
	std::cout << "Got a message:\n";
	std::cout << "Thread: " << message.thread() << std::endl;
	std::cout << "Body: " << message.body() << "\n\n";
	string body = message.body();
	if (body == "make") {
		SpejleaegSpil* game = new SpejleaegSpil(this->client, session->target());
	}
}
