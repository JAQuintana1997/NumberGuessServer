#include <enet/enet.h>
#include <iostream>
#include <thread>
#include <string>

#include "NumberGuessServer.h"

using namespace std;

ENetAddress address;
ENetHost* server = nullptr;
ENetHost* client = nullptr;
ENetHost* clientName;


bool CreateServer()
{
    /* Bind the server to the default localhost.     */
/* A specific host address can be specified by   */
/* enet_address_set_host (& address, "x.x.x.x"); */
    address.host = ENET_HOST_ANY;
    /* Bind the server to port 1234. */
    address.port = 1234;
    server = enet_host_create(&address /* the address to bind the server host to */,
        32      /* allow up to 32 clients and/or outgoing connections */,
        2      /* allow up to 2 channels to be used, 0 and 1 */,
        0      /* assume any amount of incoming bandwidth */,
        0      /* assume any amount of outgoing bandwidth */);

    return server != nullptr;
}

int main()
{
    if (enet_initialize() != 0)
    {
        fprintf(stderr, "An error occurred while initializing ENet.\n");
        cout << "An error occurred while initializing ENet." << endl;
        return EXIT_FAILURE;
    }
    atexit(enet_deinitialize);

    cout << "Please create server name: " << endl;
    string serverName;
    cin >> serverName;

    if (!CreateServer())
    {
        fprintf(stderr,
            "An error occurred while trying to create an ENet server host.\n");
        exit(EXIT_FAILURE);
    }
    while (1)
    {
        ENetEvent event;
        /* Wait up to 1000 milliseconds for an event. */
        while (enet_host_service(server, &event, 1000) > 0)
        {
            switch (event.type)
            {
            case ENET_EVENT_TYPE_CONNECT:
                cout << "A new client connected from " << event.peer->address.host << event.peer->address.port << endl;

                /* Store any relevant client information here. */
                event.peer->data = (void*)("Client information");

                {

                }


                break;
            case ENET_EVENT_TYPE_RECEIVE:

                cout << clientName << " said: " << (char*)event.packet->data << endl;

                /* Clean up the packet now that we're done using it. */
                enet_packet_destroy(event.packet);

                break;

            case ENET_EVENT_TYPE_DISCONNECT:
                cout << (char*)event.peer->data << " disconnected." << endl;
                /* Reset the peer's client information. */
                event.peer->data = nullptr;
            }
        }
    }

    //Keeping Server AND Client destroy since the server holds the clients
    if (server != nullptr)
    {
        enet_host_destroy(server);
    }

    if (client != nullptr)
    {

        enet_host_destroy(client);
    }

    return EXIT_SUCCESS;
}

