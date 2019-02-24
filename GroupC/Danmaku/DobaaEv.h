#pragma once
#include"SpriteCore.h"
#include"SpriteViews.h"
#include"Share.h"

class DobaaEv : public ISprite
{
public:
	std::shared_ptr<ISprite> Right,Left;

	DobaaEv(double X, double Y)
	{
		View = vCircle;
		Info.X = X;
		Info.Y = Y;
		Info.Color = Palette::Yellow;
		Info.Width = 10;
		Info.Height = 10;
	}

	void Start() override
	{
		Right = Manager->FindTag(L"RightPlayer");
		Left = Manager->FindTag(L"LeftPlayer");
	}

	void Update() override
	{
		if (IsHit(Right))
		{
			gEvent.Launch(L"CounterLeft");
			Manager->DestroyMe();
		}
		else if (IsHit(Left))
		{
			gEvent.Launch(L"CounterRight");
			Manager->DestroyMe();
		}
	}
};