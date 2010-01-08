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
#include <gloox/uniquemucroom.h>
#include <gloox/disco.h>
#include <stdint.h>
#include <vector>

using namespace gloox;
using namespace std;


class SpejleaegSpil : public MUCRoomHandler
{
	Client* client;
	
	vector <JID> players;
	
	
	public:
		virtual void handleMUCParticipantPresence(MUCRoom* room, const MUCRoomParticipant participant, const Presence& presence);
		virtual void handleMUCMessage(MUCRoom* room, const Message& msg, bool priv);
		virtual void handleMUCRoomCreation(MUCRoom* room);
		virtual void handleMUCSubject(MUCRoom* room, const string& nick, const string& subject);
		virtual void handleMUCInviteDecline(MUCRoom* room, const JID& invitee, const string& reason);
		virtual void handleMUCError(MUCRoom* room, StanzaError error);
		virtual void handleMUCInfo(MUCRoom* room, int features, const string& name, const DataForm* infoForm);
		virtual void handleMUCItems(MUCRoom* room, const Disco::ItemList& items);
		SpejleaegSpil (Client* client, JID& jid);
		SpejleaegSpil (Client* client, vector<JID> jids);
		//~SpejleaegSpil();
};


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
