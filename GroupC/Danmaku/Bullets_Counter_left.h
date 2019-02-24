#pragma once
#include"SpriteCore.h"
#include"SpriteViews.h"
#include"Sprites.h"
#include"ISprite.h"

class Bullets_Counter_Left : public ISprite
{
public:
	double Speed = 3;
	double Speed_X = Random(-3,3);
	double Speed_Y = Random(1,5);

	Bullets_Counter_Left()
	{
		View = vImage_Bullets_Counter;
		Info.Width = 10;
		Info.Height = 10;
		Info.Angle = Atan2(Speed_Y, Speed_X) * 180 / Pi;
		Info.X = Random(640);
		Info.Y = 481;
		Info.Color = Palette::Aquamarine;
		Tag = L"Bullets_Counter_Left";
	}

	void Update() override
	{
		Info.X += Speed_X;
		Info.Y += Speed_Y;

		
		if (!IsInWindow())
		{
			Manager->DestroyMe();
		}

		if (GetHitSp(L"LeftPlayer") != nullptr)
		{
			if (Input::KeyT.pressed)//Tキーが押されていたら、カウンター攻撃をして、ﾄﾊﾞｧは消す
			{
				Manager->DestroyMe();

				Manager->Add(new Shot_Counter_Left(Info.X,Info.Y,Info.Angle));
			}
		}		
	}
};