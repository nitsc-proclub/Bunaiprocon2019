#pragma once
#include"SpriteCore.h"
#include"SpriteViews.h"
#include"Sprites.h"
#include"ProgressBar.h"
#include"Share.h"
#include"HPGauge.h"

class LeftPlayer : public ISprite
{
public:
	//��{�ړ��X�s�[�h
	double Speed = 5;
	int HP = 100;
	Font fnt;
	int ShotCount;
	//�����ړ��c�莞��
	int dcount;
	int cooltime;

	bool Muteki;
	//����ړ���
	bool FastMove;
	std::shared_ptr<ISprite> TekkiPtr;
	int SP = 50;
	int SP_count = 0;
	int way = 1;

	LeftPlayer()
	{
		View = vRect;
		Info.Width = 20;
		Info.Height = 20;
		Info.Angle = 270;
		Info.X = Random(639);
		Info.Y = Random(480, 959);
		Info.Color = Palette::Forestgreen;
		Tag = L"LeftPlayer";
	}

	void Start() override
	{
		TekkiPtr = Manager->FindTag(L"RightPlayer");
		ShotCount = 0,way=1,
			dcount = 10, Muteki = 0, cooltime = 60;
		Info.X = 300;
		Info.Y = 800;
	}

	void Draw() override
	{
		ISprite::Draw();
		//fnt(Format(L"(", Info.X, L",", Info.Y, L")")).draw();

		//debag�悤
		//fnt(Format(L"(", way, L")")).draw(100,100);
		//fnt(Format(L"(", Info.Angle, L")")).draw(100, 200);
		//fnt(Format(L"(", avoid, L")")).draw(100, 300);
		//fnt(Format(L"(", cooltime, L")")).draw(100, 400);
		HPGauge(HP, 100).Draw(10, 10);
		ProgressBar(SP, 200).Draw(10, 450);
	}

	void DoEvent(const SpriteEvent e,const int val) override
	{
		switch (e)
		{
		case SpriteEvent::Damage:
			if (!Muteki)
			{
				HP-=val;
			}
			break;
		}
	}

	void Update() override
	{
		//�ړ����t���O
		bool IsMoving = false;
		//�ړ���
		double MoveX = 0, MoveY = 0;

		//�ړ����x
		double SpdBuff = Input::KeyShift.pressed ? Speed / 2 : Speed;

		if (Info.Angle > 360)
		{
			Info.Angle =0;
		
		}
		if (Info.Angle < 0)
		{
			Info.Angle = 360;
			
		}

		//�X�L����
		SP_count = (SP_count + 1) % 10;
		if (SP_count == 0)
		{
			SP += 1;

			if (SP >= 200)
			{
				SP = 200;
			}
		}

		#pragma region �ړ�����(�ʏ�)
		//�ړ�����
		if (Input::KeyW.pressed)
		{
			MoveY -= SpdBuff;
			IsMoving = true;
		}
		if (Input::KeyS.pressed)
		{
			MoveY += SpdBuff;
			IsMoving = true;
		}
		if (Input::KeyA.pressed)
		{
			MoveX -= SpdBuff;
			IsMoving = true;
		}
		if (Input::KeyD.pressed)
		{
			MoveX += SpdBuff;
			IsMoving = true;
		}
		#pragma endregion

		#pragma region ����@�\
		//�����ړ�����
		if (FastMove)
		{
			//�����ړ���
			if (IsMoving && Input::KeyR.pressed && dcount > 0)
			{
				//�����ړ��p��
			}
			else
			{
				//�����ړ��I��
				Info.Color = Palette::Forestgreen;
				Muteki = false;
				FastMove = false;
				cooltime = 0;
			}
			dcount--;
		}
		else
		{
			//�����ړ����ĂȂ�
			if (IsMoving && Input::KeyR.pressed && cooltime == 60)
			{
				//�����ړ��J�n
				dcount = 10;
				Info.Color = Palette::Aqua;
				Muteki = true;
				FastMove = true;
			}
			else
			{
				//�ʏ�
				if (cooltime < 60 && !Input::KeyR.pressed)
				{
					cooltime++;
				}
			}
		}
		//����@�\�L���̎�
		if (FastMove)
		{
			//�ړ����x3�{
			MoveX = MoveX * 3;
			MoveY = MoveY * 3;
		}
		#pragma endregion

		Info.X += MoveX;
		Info.Y += MoveY;
		Info.X = Max<double>(Min<double>(Info.X, 639), 0);
		Info.Y = Max<double>(Min<double>(Info.Y, 959), 500);

		//�e����

		if (Input::KeySpace.pressed && Input::KeyG.pressed&& Input::KeyH.pressed)
		{

		}
		else if (Input::KeyH.pressed&&Input::KeySpace.pressed)
		{
			if (ShotCount == 0 && SP <=  0)
			{
				SP = 0;
			}
			else if (ShotCount == 0 && SP >= 1)
			{
				SP -= 4;
				HomingShot* b = new HomingShot(Info.X, Info.Y, Info.Angle, TekkiPtr);

				b->Speed = 10;
				b->Tag = L"Shot";
				b->Precision = 4;

				Manager->Add(b);
			}
			ShotCount = (ShotCount + 1) % 5;

		}
		else if (Input::KeySpace.pressed)
		{
			if (ShotCount == 0)
			{

				Shot* b = new Shot(Info.X, Info.Y, Info.Angle);

				b->Speed = 10;
				b->Tag = L"Shot";
				b->Target = TekkiPtr;

				Manager->Add(b);
			}

			
			//�܂�Ԃ���

			while (Input::KeyF.pressed)
			{
				
				if (Info.Angle > 290)
				{
					//Info.Angle = 240;
					way = 1;
				}
				if (Info.Angle < 250)
				{
					//Info.Angle = 320;
					way = -1;
				}
				Info.Angle += way * -3;
				break;

			}
			
			while (!Input::KeyF.pressed)
			{
				if (Info.Angle > 310)
				{
					way = -1;
				}
				if (Info.Angle < 230)
				{
					way = 1;
				}
				Info.Angle += way * 3;
				break;
			}



			//�܂�Ԃ���


		
			
			ShotCount = (ShotCount + 1) % 5;
			//�X�L������
			if (Input::KeyG.pressed)
			{
				if (SP <= 0)
				{
					SP = 0;
				}
				else
				{
					SP -= 1;
					ShotCount = 0;
				}
			}
		}

		//���͍U��
		if (Input::KeyQ.pressed)
		{
			if (SP == 200)
			{
				if (RandomBool())
				{
					gEvent.Launch(L"CounterRight");
				}
				else
				{
					gEvent.Launch(L"BlockRight");
				}
				SP = 0;
			}
		}

		//�����蔻��
		//�u���b�N
		if (GetHitSp(L"Shot_Counter_Right") != nullptr)
		{
			DoEvent(SpriteEvent::Damage,1);
		}
		//���ާ
		if (GetHitSp(L"Bullets_Counter_Left") != nullptr)
		{
			DoEvent(SpriteEvent::Damage,3);
		}

		//���S����
		if (HP <= 0)
		{
			Manager->DestroyMe();
			Winner = RIGHT;
			CurrentScene = Scene::Result;
		}
	}
};