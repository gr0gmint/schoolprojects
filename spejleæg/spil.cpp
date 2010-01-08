#include "spejleaeg.hpp"

void handleMUCParticipantPresence(MUCRoom* room, const MUCRoomParticipant participant, const Presence& presence) {
	
}
void handleMUCMessage(MUCRoom* room, const Message& msg, bool priv);
void handleMUCRoomCreation(MUCRoom* room);
void handleMUCSubject(MUCRoom* room, const string& nick, const string& subject);
void handleMUCInviteDecline(MUCRoom* room, const JID& invitee, const string& reason);
void handleMUCError(MUCRoom* room, StanzaError error);
void handleMUCInfo(MUCRoom* room, int features, const string& name, const DataForm* infoForm);
void handleMUCItems(MUCRoom* room, const Disco::ItemList& items);
SpejleaegSpil (Client* client, JID& jid);
SpejleaegSpil (Client* client, vector<JID> jids);
