#include "spejleaeg.hpp"
#include "states.hpp"
#include <boost/regex.hpp>
#include <iostream>

using namespace gloox;

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
			this->moderator = new JID(participant.nick->full());
			MUCRoomRole role = RoleModerator;
			this->room->setRole(participant.nick->resource(), role);
			this->state = GAME_INVITEPHASE;
			
			
			this->room->send("Invitér flere spillere for at spille");
		}
	} else { 
		if (participant.nick->resource() == "æggebot") {
			std::cout << "Blev smidt ud af rummet? \n";
		} else {
			std::cout << "Stopping the game\n";
		}
	}
	
}
void SpejleaegSpil::handleMUCMessage(MUCRoom* room, const Message& msg, bool priv)
{
	string command;
	vector<string> arguments;

	
	boost::regex valid_command ("([\\w\\d]+)(\\s+(.*))?");
	boost::regex argument ("(.+)(\\s+(.*))?");
	string suffix;
	boost::smatch what;
	boost::smatch argmatch;
	JID* invitee;
	int i;
	
	std::cout << msg.from().resource() <<" - " << msg.body() << std::endl; 
	if (!priv && msg.from().resource() != "æggebot") {
		
		//Først tjek om det er en gyldig kommando
		if (boost::regex_match(msg.body(), what, valid_command, boost::match_default)) {
			std::cout << "Command: " << what[1] << "!"<<std::endl;
			command = what[1];
			suffix = what[3];
				do 
				{
					if (regex_match(suffix, argmatch, argument, boost::match_default)) {
						arguments.push_back(argmatch[1]);
						suffix = argmatch[3];
						continue;
					} else {
						break;
					}
				}	while (true);
			bool unknown_command = false;
			
			//Kommandoer med uspecificeret antal argumenter kodes her:


			//Kommandoer med 0 argumenter kodes her:
			if (arguments.size() == 0) {
				if        ( command == "start") {
				} else if ( command == "stop") {
				} else if ( command == "roll") {
				} else {
					unknown_command = true;
				}
			//Kommandoer med 1 argument kodes her:
			} else if (arguments.size() == 1) {
				if        ( command == "kick") {
				}
			}
			if (unknown_command)
				room->send("Ukendt kommando!");
		} else {
			room->send("Ugyldig kommando!");
		}
	}
	
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

void handleCommand(const Message& msg, bool priv, const string &cmd, const vector <string> &arguments)
{
	
}
