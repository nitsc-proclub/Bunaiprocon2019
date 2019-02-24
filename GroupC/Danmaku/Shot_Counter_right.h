#pragma once
#include"SpriteCore.h"
#include"SpriteViews.h"
#include"Sprites.h"

class Shot_Counter_Right : public ISprite
{
public:
	double Speed = 3;

	Shot_Counter_Right()
	{
		View = vRect;
	}

	Shot_Counter_Right(double X, double Y, double Angle)
	{
		View = vRect;
		Info.Width = 10;
		Info.Height = 50;
		Info.Angle = Angle;
		Info.X = X;
		Info.Y = Y;
		Info.Color = Palette::Cornflowerblue;
		Tag = L"Shot_Counter_Right";
	}

	void Start() override
	{

	}

	void Update() override
	{
		Info.Y += 8;
	}
};

