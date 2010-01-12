#include "spejleaeg.hpp"
#include "states.hpp"
#include <boost/regex.h>
#include <iostream>

boost::regex splitter("^(\w)\s([\\w\\d(?=\s))*");

void SpejleaegSpil::handleMUCParticipantPresence(MUCRoom* room, const MUCRoomParticipant participant, const Presence& presence)
{
	//Presence::PresenceType ptype;
	//ptype == Presence::Chat
	
	std::cout << "handleMUCParticipantPresence:\n    nick:" << participant.nick->full() <<"\n";
	if (presence.presence() != Presence::Unavailable) {
		
		if (this->state == GAME_INITIAL) {
			//Denne kode bliver kørt når vi selv har joinet rummet.
			this->room->setSubject("Æggemad");
			this->state = GAME_FIRSTINVITE;
			this->room->invite(this->invitees[0], "Spil spejleæg!");
			
		} else if (this->state == GAME_FIRSTINVITE) {
			//Moderatoren har joinet rummet
			this->moderator = participant.nick;
			this->state = GAME_INVITEPHASE;
			vector<cmd_callback> *invitephase_cmdset = new vector<cmd_callback>;
			invitephase_cmdset->push_back(&moderator::invite);
			
			this->room->send("For at invitere andre til spillet, skriv 'invite <JID> ... '");
		}
	} else {	//Participanten er gået ud af 
		if (participant.nick->resource() == "æggebot") {
			std::cout << "Blev smidt ud af rummet? \n";
		}
	}
	
}
void SpejleaegSpil::handleMUCMessage(MUCRoom* room, const Message& msg, bool priv)
{
	
	std::cout << "MUC message: [" << msg.subject() << "] - [" << msg.body() << "] \n";
}
bool SpejleaegSpil::handleMUCRoomCreation(MUCRoom* room)
{
	std::cout << "handleMUCRoomCreation\n";
	return true;
}
void SpejleaegSpil::handleMUCSubject(MUCRoom* room, const string& nick, const string& subject)
{
	std::cout << "handleMUCSubject\n";
}
void SpejleaegSpil::handleMUCInviteDecline(MUCRoom* room, const JID& invitee, const string& reason)
{
	std::cout << "handleMUCInviteDecline\n";
}
void SpejleaegSpil::handleMUCError(MUCRoom* room, StanzaError error)
{
	std::cout << "handleMUCError\n";
}
void SpejleaegSpil::handleMUCInfo(MUCRoom* room, int features, const string& name, const DataForm* infoForm)
{
	std::cout << "handleMUCInfo\n";
}
void SpejleaegSpil::handleMUCItems(MUCRoom* room, const Disco::ItemList& items)
{
	std::cout << "handleMUCInfo\n";
}

SpejleaegSpil::SpejleaegSpil (Client* client, const JID& invitee) {
	this->client = client;
	this->state = GAME_INITIAL;
	this->invitees.push_back(invitee);
	JID nick("conference.jabber.org/æggebot");
	this->room = new UniqueMUCRoom(client, nick, this);
	this->room->join();
}

void handleCommand(MUCRoom* room, const Message& msg, bool priv, const string &cmd, const vector <string> &arguments)
{
	
}
