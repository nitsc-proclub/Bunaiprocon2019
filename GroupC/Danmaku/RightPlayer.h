#pragma once
#include"SpriteCore.h"
#include"SpriteViews.h"
#include"Sprites.h"
#include"ProgressBar.h"
#include"Share.h"
#include"HPGauge.h"

class RightPlayer : public ISprite
{
public:
	//基本移動スピード
	double Speed = 5;
	int HP = 100;
	Font fnt;
	int ShotCount;
	//高速移動残り時間
	int dcount;
	int cooltime;

	bool Muteki;
	//回避移動中
	bool FastMove;
	std::shared_ptr<ISprite> TekkiPtr;
	int SP = 50;
	int SP_count = 0;
	int way = 1;

	RightPlayer()
	{
		View = vRect;
		Info.Width = 20;
		Info.Height = 20;
		Info.Angle = 90;
		Info.X = Random(639);
		Info.Y = Random(479);
		Info.Color = Color(197, 78, 160);
		Tag = L"RightPlayer";
	}

	void Draw() override
	{
		ISprite::Draw();
		//fnt(Format(L"(", Info.X, L",", Info.Y, L")")).draw(642,0);
		HPGauge(HP, 100).Draw(1067, 10);
		ProgressBar(SP, 200).Draw(1067, 450);
	}

	void Start() override
	{
		ShotCount = 0,
			dcount = 10, cooltime = 30,way = 1;
		TekkiPtr = Manager->FindTag(L"LeftPlayer");
		Muteki = false;
		FastMove = false;
		Info.X = 300;
		Info.Y = 159;
	}

	void DoEvent(const SpriteEvent e,const int val) override
	{
		switch (e)
		{
		case SpriteEvent::Damage:
			if (!Muteki)
			{
				HP--;
			}
			break;
		}
	}

	void Update() override
	{
		//移動中フラグ
		bool IsMoving = false;
		//移動量
		double MoveX = 0, MoveY = 0;

		//移動速度
		double SpdBuff = Input::KeyShift.pressed ? Speed / 2 : Speed;

		//スキル回復
		SP_count = (SP_count + 1) % 10;
		if (SP_count == 0)
		{
			SP += 1;

			if (SP >= 200)
			{
				SP = 200;
			}
		}

		#pragma region 移動処理(通常)
		//移動処理
		if (Input::KeyUp.pressed)
		{
			MoveY = SpdBuff;
			IsMoving = true;
		}
		if (Input::KeyDown.pressed)
		{
			MoveY = -SpdBuff;
			IsMoving = true;
		}
		if (Input::KeyLeft.pressed)
		{
			MoveX = SpdBuff;
			IsMoving = true;
		}
		if (Input::KeyRight.pressed)
		{
			MoveX = -SpdBuff;
			IsMoving = true;
		}
		#pragma endregion

		#pragma region 回避機能
		//高速移動判定
		if (FastMove)
		{
			//高速移動中
			if (IsMoving && Input::KeyJ.pressed && dcount > 0)
			{
				//高速移動継続
			}
			else
			{
				//高速移動終了
				Info.Color = Color(197, 78, 160);
				Muteki = false;
				FastMove = false;
				cooltime = 0;
			}
			dcount--;
		}
		else
		{
			//高速移動してない
			if (IsMoving && Input::KeyJ.pressed && cooltime == 30)
			{
				//高速移動開始
				dcount = 10;
				Info.Color = Palette::Aqua;
				Muteki = true;
				FastMove = true;
			}
			else
			{
				//通常
				if (cooltime < 30 && !Input::KeyJ.pressed)
				{
					cooltime++;
				}
			}
		}
		//回避機能有効の時
		if (FastMove)
		{
			//移動速度3倍
			MoveX = MoveX * 3;
			MoveY = MoveY * 3;
		}
		#pragma endregion

		Info.X += MoveX;
		Info.Y += MoveY;
		Info.X = Max<double>(Min<double>(Info.X, 639), 0);
		Info.Y = Max<double>(Min<double>(Info.Y, 460), 0);

		#pragma region 弾発射
		//弾発射		
		if (Input::KeyRControl.pressed &&Input::KeyPeriod.pressed&&Input::KeyComma.pressed)
		{

		}
		else if (Input::KeyRControl.pressed && Input::KeyPeriod.pressed)
		{
			if (ShotCount == 0 && SP <= 0)
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
		else if (Input::KeyRControl.pressed)
		{
			if (ShotCount == 0)
			{
				Shot* b = new Shot(Info.X, Info.Y, Info.Angle);

				b->Speed = 10;
				b->Tag = L"Shot";
				b->Target = TekkiPtr;

				Manager->Add(b);

			}
			//折り返し↓

			while (Input::KeyM.pressed)
			{

				if (Info.Angle > 110)
				{
					//Info.Angle = 240;
					way = 1;
				}
				if (Info.Angle < 70)
				{
					//Info.Angle = 320;
					way = -1;
				}
				Info.Angle += way * -3;
				break;
			}

			while (!Input::KeyM.pressed)
			{
				if (Info.Angle > 130)
				{
					way = -1;
				}
				if (Info.Angle < 50)
				{
					way = 1;
				}
				Info.Angle += way * 3;
				break;
			}



			//折り返し↑
			ShotCount = (ShotCount + 1) % 5;
			//スキル発動
			if (Input::KeyComma.pressed)
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

		#pragma endregion

		//強力攻撃
		if (Input::KeySlash.pressed)
		{
			if (SP == 200)
			{
				if (RandomBool())
				{
					gEvent.Launch(L"CounterLeft");
				}
				else
				{
					gEvent.Launch(L"BlockLeft");
				}
				SP = 0;
			}
		}

		//当たり判定
		//ブロック
		if (GetHitSp(L"Shot_Counter_Left") != nullptr)
		{
			DoEvent(SpriteEvent::Damage,1);
		}
		//ﾄﾞﾊﾞｧ
		if (GetHitSp(L"Bullets_Counter_Right") != nullptr)
		{
			DoEvent(SpriteEvent::Damage,3);
		}

		//死亡判定
		if (HP <= 0)
		{
			Manager->DestroyMe();
			Winner = LEFT;
			CurrentScene = Scene::Result;
		}
	}
};