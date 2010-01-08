#ifndef _SPEJLEAEG_HPP
#define _SPEJLEAEG_HPP

#include <gloox/gloox.h>
#include <gloox/jid.h>
#include <gloox/presence.h>
#include <gloox/presencehandler.h>
#include <gloox/client.h>
#include <gloox/connectionlistener.h>
#include <gloox/messagesession.h>
#include <gloox/messagesessionhandler.h>
#include <gloox/messagehandler.h>
#include <gloox/message.h>
#include <gloox/disco.h>
#include <stdint.h>
#include <vector>
#include "spil.hpp"

using namespace gloox;
using namespace std;


class SpejleaegBot : public ConnectionListener, PresenceHandler,
							MessageSessionHandler, MessageHandler
{
	JID* jid;
	string password;
	Client* client;
	int32_t state;
	vector <SpejleaegSpil> games;
	
	
	private:
		
		
    public:
        virtual void onConnect();
        virtual void onDisconnect(ConnectionError e);
        virtual bool onTLSConnect( const CertInfo& info);
        virtual void handleMessageSession(MessageSession * session);
        virtual void handleMessage( const Message& message, MessageSession * session=0);
        virtual void handlePresence(const Presence& presence);
        SpejleaegBot (JID* jid, string & password);
        ~SpejleaegBot ();
        
        void connect();
};

#endif
