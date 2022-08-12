#pragma once

#include <enet/enet.h>
#include <iostream>
#include <thread>
#include <string>
using namespace std;


class NumberGuessServer
{
public:

	ENetAddress address;
	ENetHost* server;
	ENetHost* client;

	bool CreateServer();
	void sendPacket();
	void getMessage();
};