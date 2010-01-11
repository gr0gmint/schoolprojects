#ifndef _SPIL_HPP
#define _SPIL_HPP
#include <gloox/client.h>
#include <gloox/jid.h>
#include <gloox/messagesession.h>
#include <gloox/messagesessionhandler.h>
#include <gloox/messagehandler.h>
#include <gloox/message.h>
#include <gloox/mucroomhandler.h>
#include <gloox/uniquemucroom.h>

#include <vector>

using namespace gloox;
using namespace std;

class SpejleaegSpil : public MUCRoomHandler
{
	int state;
	Client* client;
	vector <JID> invitees;
	vector <JID> players;
	JID moderator;
	vector <short> playereggs;
	bool eggholes[5];
	short turn;
	UniqueMUCRoom* room;
	public:
		virtual void handleMUCParticipantPresence(MUCRoom* room, const MUCRoomParticipant participant, const Presence& presence);
		virtual void handleMUCMessage(MUCRoom* room, const Message& msg, bool priv);
		virtual bool handleMUCRoomCreation(MUCRoom* room);
		virtual void handleMUCSubject(MUCRoom* room, const string& nick, const string& subject);
		virtual void handleMUCInviteDecline(MUCRoom* room, const JID& invitee, const string& reason);
		virtual void handleMUCError(MUCRoom* room, StanzaError error);
		virtual void handleMUCInfo(MUCRoom* room, int features, const string& name, const DataForm* infoForm);
		virtual void handleMUCItems(MUCRoom* room, const Disco::ItemList& items);
		SpejleaegSpil (Client* client, const JID& invitee);
		//~SpejleaegSpil();
};

#endif
