#pragma once
#include<thread>
#include<queue>
#include"SpriteCore.h"

/// <summary>
/// 送信パケット
/// </summary>
class Packet
{
public:
	enum PacketState { Info=0,Plus=1,Minus=2,End=3 };
	Packet(SpriteInfo inf)
	{
		state = Info;
		info = inf;
	}
	PacketState state;
	SpriteInfo info;
};

class TCPSender : public SpriteManager
{
public:
	TCPServer server;//サーバー本体
	std::queue<Packet> queue;//送信キュー

	/// <summary>
	/// コンストラクター
	/// </summary>
	/// <param name="port">解放するポート</param>
	TCPSender(uint16 port)
	{
		server.startAccept(port);
	}

	//根底クラスのUpdateAll()にPacketを生成する機能をつけたもの
	void UpdateAll() override
	{
		Calling = true;
		for (Call_i = 0; Call_i < Sprites.size(); Call_i++)
		{
			std::shared_ptr<ISprite> sp = Sprites[Call_i];
			if (!sp->IsInit)
			{
				sp->Start();
				sp->IsInit = true;
			}
			sp->Update(*this);
			queue.push(Packet(sp->Info));//パケットを生成
		}
		Calling = false;
	}

	//パケットをバックグラウンドで送信する関数
	void SyncThread()
	{
		do
		{
			if (!queue.empty())
			{
				server.send(queue.front());
				queue.pop();
			}
		} while (Calling);
	}
};