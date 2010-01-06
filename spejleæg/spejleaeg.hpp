#include <gloox/gloox.h>
#include <gloox/presence.h>
#include <gloox/client.h>
#include <gloox/connectionlistener.h>
#include <gloox/messagesession.h>
#include <gloox/uniquemucroom.h>


using namespace gloox;

class SpejleaegPresence : public PresenceHandler
{
    public:
        virtual void handlePresence( const Presence& presence );s
}

class SpejleaegBot : public ConnectionListener
{
    public:
        virtual void onConnect();
        virtual bool onTLSConnect( const CertInfo& info);
}
