#pragma once
#include<thread>
#include"SpriteCore.h"

class TCPReciever : public SpriteManager
{
public:
	TCPClient client;
	TCPReciever(IPv4 ip,uint16 port)
	{
		client.connect(ip, port);
	}
	void UpdateAll() override
	{
		
	}
	void SyncThread()
	{

	}
};

