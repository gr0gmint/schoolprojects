#include "spejleaeg.hpp"
#include "states.hpp"


#include <iostream>

void SpejleaegSpil::handleMUCParticipantPresence(MUCRoom* room, const MUCRoomParticipant participant, const Presence& presence)
{
	std::cout << "handleMUCParticipantPresence - " << participant.nick->resource() <<"\n";
	if (participant.nick->resource() == "ggbot") {
		this->room->invite(this->invitees[0], "JOIN ME FOR LULZ");
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
	JID nick("conference.jabber.org/ggbot");
	this->room = new UniqueMUCRoom(client, nick, this);
	this->room->join();
}

