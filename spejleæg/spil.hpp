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

typedef bool (*cmd_callback)(vector <string>); //Denne typedef er nødvendig for at lave en vector af 
											   //function pointers. Bruges til have en liste af callbacks,
											   //som bliver affyret af de rette kommandoer.


/*
 * Denne klasse er ansvarlig for at joine et MUCRoom (Multi-user Chat), på en offentlig MUC-server 
 * (conference.jabber.org), og iscenesætte spillet (invitere brugere osv.)
 * Derefter tager den sig af at styre spillet, med regler osv.)
*/
class SpejleaegSpil : public MUCRoomHandler
{
	int state;				
	Client* client;				
	vector <JID> invitees;		//Liste over folk der skal inviteres til spillet
	vector <JID> players;		//Spillerne
	JID moderator;				//JID på moderatoren
	vector<short> *playereggs;	//Hvor mange æg hver spiller har. Er i samme rækkefølge tilsvarende til SpejleaegSpil::players
	bool eggholes[5]; 			//De 5 huller som kan være fyldt et æg
	short turn;					//Hvems tur er det
	UniqueMUCRoom* room;		
	vector <cmd_callback> commandset;
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
		
		void handleCommand(MUCRoom* room, const Message& msg, bool priv, const string &cmd, const vector <string> &arguments);
};

#endif
