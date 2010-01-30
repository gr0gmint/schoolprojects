#include "spejleaeg.hpp"
#include "states.hpp"
#include <boost/regex.hpp>
#include <iostream>

const string BOT_NICK = "eggbot";

using namespace gloox;
using namespace std;

void SpejleaegSpil::handleMUCParticipantPresence(MUCRoom* room, const MUCRoomParticipant participant, const Presence& presence)
{
	
	std::cout << "handleMUCParticipantPresence:\n    nick:" << participant.nick->full() <<"\n";
	
	if (presence.presence() == Presence::Available) {
		
		if (this->state == GAME_INITIAL) {
			//Denne kode bliver kørt når vi selv har joinet rummet.
			this->room->setSubject("Æggemad");
			this->state = GAME_FIRSTINVITE;
			this->room->invite(this->invitees[0], "Spil spejleæg!");
			
		} else if (this->state == GAME_FIRSTINVITE) {
			//Moderatoren har joinet rummet
			this->moderator = new JID(participant.nick->full());
			MUCRoomRole role = RoleModerator;
			MUCRoomAffiliation affiliation = AffiliationOwner;
			string nick = participant.nick->resource();
			this->room->setRole(nick, role);
			this->room->setAffiliation(nick, affiliation, "Du er moderator!");
			this->state = GAME_INVITEPHASE;
			
			
			this->room->send("Invitér flere spillere for at spille");
		} else if (this->state == GAME_INVITEPHASE) {
			JID * lol = new JID(participant.nick->full());
			this->players.push_back(*lol);
		}
	} else if (presence.presence() == Presence::Unavailable) { 
		if (participant.nick->resource() == BOT_NICK) {
			std::cout << "Blev smidt ud af rummet? \n";
		} else {
			//En 
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
	if (!priv && msg.from().resource() != BOT_NICK) {
		
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
			bool unspecified_argc = false;
			
			//Kommandoer med uspecificeret antal argumenter kodes her:
			if (command == "invite" && arguments.size() > 0) {
				for (i = 0; i < arguments.size(); i++) {
					this->room->invite(JID(arguments[i]), "Join TEH GAME");
				}
			}

			//Kommandoer med 0 argumenter kodes her:
			else if (arguments.size() == 0) {
				if        ( command == "start") {
				} else if ( command == "stop") {
				} else if ( command == "roll") {
				} else {
					unknown_command = true;
				}
			//Kommandoer med 1 argument kodes her:
			} else if (arguments.size() == 1) {
				if        ( command == "kick") {
				} else {
					unknown_command = true;
				}
			} else {
				unknown_command = true;
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
	JID nick("conference.jabber.org/"+BOT_NICK);
	this->room = new UniqueMUCRoom(client, nick, this);
	this->room->join();
}

void handleCommand(const Message& msg, bool priv, const string &cmd, const vector <string> &arguments)
{
	
}
