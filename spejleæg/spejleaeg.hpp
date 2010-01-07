#include <gloox/gloox.h>
#include <gloox/jid.h>
#include <gloox/presence.h>
#include <gloox/client.h>
#include <gloox/connectionlistener.h>
#include <gloox/messagesession.h>
#include <gloox/uniquemucroom.h>
#include <stdint.h>

using namespace gloox;

class SpejleaegBot : public ConnectionListener, PresenceHandler
{
	JID* jid;
	string password;
	Client* client;
	int32_t state;
		
    public:
        virtual void onConnect();
        virtual void onDisconnect(ConnectionError e);
        virtual bool onTLSConnect( const CertInfo& info);
        SpejleaegBot (JID* jid, string & password);
        
        
        void start();
}

class SpejleaegPresence : public PresenceHandler
{
    public:
        virtual void handlePresence( const Presence& presence );
}

class SpejleaegSpil
{
	
}

class SpejleaegCommandHandler : public MessageSessionHandler
{
	public:
		virtual void handleMessageSession(MessageSession * session);
	
}

