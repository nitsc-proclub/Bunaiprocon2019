#pragma once
#include"SpriteCore.h"
#include"SpriteViews.h"
#include"Sprites.h"

class Jiki : public ISprite 
{
public :
	double Speed = 3, dodge = 0, count = 0,
		dcount = 10, avoid = 0, cooltime = 60;//���ύX�_
	
	
	Jiki()
	{
		View = vRect;
		Info.Width = 10;
		Info.Height = 10;
		Info.Angle = 0;
		Info.X = Random(640);
		Info.Y = Random(480);
		Info.Color = Palette::Forestgreen;
	}
	//�ύX�_��


	 
	
	void Start() override
	{
		Info.X = 540;
		Info.Y = 240;
		
	}

	void Update() override
	{
		// const Font font(30); font(L"dcount", dcount = dcount).draw({ 100,300 });
		
		++count;

		double SpdBuff = Input::KeyShift.pressed ? Speed / 2 : Speed;
		if (Input::KeyW.pressed)
		{
			Info.Y -= SpdBuff; 
			//�ύX�_��
			dodge = 1;
		}
		if (Input::KeyS.pressed)
		{
			Info.Y += SpdBuff; 
			//�ύX�_��
			dodge = 1;
		}
		if (Input::KeyA.pressed)
		{
			Info.X -= SpdBuff; 
			//�ύX�_��
			dodge = 1;
		}
		if (Input::KeyD.pressed)
		{
			Info.X += SpdBuff; 
			//�ύX�_��
			dodge = 1;
		}
		if (Input::KeyEnter.pressed)
		{
			Shot*b = new Shot(Info.X,Info.Y,Info.Angle);

			b->Speed = 10;
			b->Tag = L"Shot";

			Manager->Add(b);

			Info.Angle += 5;
		}
		//if (Input::KeyK.pressed) �V�����e��ǉ�����������
		//{
			//skill*b = new skill(Info.X, Info.Y, Info.Angle);
		
			//b->Speed = 10;
			
			
			//Manager->Add(b);

			
		//}

		//{
			//auto result = GetHitSp(L"Enemy");
			//Info.Color = result == nullptr ? Palette::Red : Palette::Orange;
		//}
		//����X�v���C�g�@�ړ��L�[��L�L�[�ŉ��
		if ( dodge == 1 &&Input::KeyL.pressed&&dcount == 10&&cooltime==60)//�ړ��L�[��L�L�[����������Ԃ��N�[���^�C�����^����������ԃ}�b�N�X�̎�
		{
			cooltime = 0;
			--dcount;
			Speed = 8;
			Info.Color = Palette::Aqua;
			avoid = 1;

		}
		else if (dodge == 1 && Input::KeyL.pressed&&dcount !=0&&cooltime==0 )//������ړ��L�[��L�L�[����������Ԃŉ�𒆁@�����ŃN�[���^�C���[��
		{
			--dcount;
			avoid = 1;
			Info.Color = Palette::Aqua;
			Speed = 8;
		}
		else if (dodge == 1 && Input::KeyL.pressed&&dcount == 0 && cooltime == 0)//������ړ��L�[��L�L�[����������ԃN�[���^�C���[����������ԃ[���̎�
		{
			
			Speed = 3;
			Info.Color = Palette::Forestgreen;
			avoid = 0;
		}

		else if (dcount != 10&&cooltime!=60)//�ړ��L�[��L�L�[�𗣂�����
		{
		
			cooltime++;
			Speed = 3;
			Info.Color = Palette::Forestgreen;
			avoid = 0;

		}
		else//�ړ��L�[��L�L�[�𗣂�����ԃN�[���^�C�����^����������ԃ}�b�N�X�̎��@�����̏��
		{
			dcount=10;
			Speed = 3;
			Info.Color = Palette::Forestgreen;
			avoid = 0;
		}

		dodge = 0;
		//�ύX�_��

		//const Font font(20); font(L"dcount").draw({ 100,100 });UI	��ǉ�����������
	}


};