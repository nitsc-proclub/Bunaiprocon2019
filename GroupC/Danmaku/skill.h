#pragma once
#include"SpriteCore.h"
#include"SpriteViews.h"

class skill : public ISprite
{
public:
	double Speed;
	
	skill()
	{
		View = vCircle;
	}

	skill(double X, double Y, double Angle)
	{
		View = vCircle;
		Info.X = X;
		Info.Y = Y;
		Info.Angle = Angle;
		Info.Color = Palette::Green;
		Info.Width = 10;
		Info.Height = 10;
		Tag = L"skill";
	}

	void Start() override
	{

	}

	void Update() override
	{
		Info.Y += Sin(Info.Angle*Pi / 180)*Speed;
		Info.X += Cos(Info.Angle*Pi / 180)*Speed;
		if (!IsInWindow())
		{
			Manager->DestroyMe();
		}
	}
};