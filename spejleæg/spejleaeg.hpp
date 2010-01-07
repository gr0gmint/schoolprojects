#include <gloox/gloox.h>
#include <gloox/jid.h>
#include <gloox/presence.h>
#include <gloox/presencehandler.h>
#include <gloox/client.h>
#include <gloox/connectionlistener.h>
#include <gloox/messagesession.h>
#include <gloox/messagesessionhandler.h>
#include <gloox/uniquemucroom.h>
#include <stdint.h>
#include <vector>

using namespace gloox;
using namespace std;


class SpejleaegSpil
{
	vector <JID> players;
	
	public:
		SpejleaegSpil ();
		//~SpejleaegSpil();
};


class SpejleaegBot : public ConnectionListener, PresenceHandler, MessageSessionHandler
{
	JID* jid;
	string password;
	Client* client;
	int32_t state;
	vector <SpejleaegSpil> games;
	
		
    public:
        virtual void onConnect();
        virtual void onDisconnect(ConnectionError e);
        virtual bool onTLSConnect( const CertInfo& info);
        virtual void handleMessageSession(MessageSession * session);
        
        virtual void handlePresence(const Presence& presence);
        
        SpejleaegBot (JID* jid, string & password);
        ~SpejleaegBot ();
        
        void connect();
};
