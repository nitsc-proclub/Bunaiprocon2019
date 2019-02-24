#pragma once
#include<thread>
#include<queue>
#include"SpriteCore.h"

/// <summary>
/// ���M�p�P�b�g
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
	TCPServer server;//�T�[�o�[�{��
	std::queue<Packet> queue;//���M�L���[

	/// <summary>
	/// �R���X�g���N�^�[
	/// </summary>
	/// <param name="port">�������|�[�g</param>
	TCPSender(uint16 port)
	{
		server.startAccept(port);
	}

	//����N���X��UpdateAll()��Packet�𐶐�����@�\����������
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
			queue.push(Packet(sp->Info));//�p�P�b�g�𐶐�
		}
		Calling = false;
	}

	//�p�P�b�g���o�b�N�O���E���h�ő��M����֐�
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