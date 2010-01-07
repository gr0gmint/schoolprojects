#include <gloox/gloox.h>
#include <gloox/jid.h>
#include <gloox/presence.h>
#include <gloox/client.h>
#include <gloox/connectionlistener.h>
#include <gloox/messagesession.h>
#include <gloox/uniquemucroom.h>

using namespace gloox;


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

class SpejleaegBot : public ConnectionListener, PresenceHandler
{
	JID* jid;
	string password;
	
    public:
        virtual void onConnect();
        virtual bool onTLSConnect( const CertInfo& info);
        SpejleaegBot (JID* jid, string & password);
        
        void connect();
}
