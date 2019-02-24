#pragma once
#include"SpriteCore.h"
#include"SpriteViews.h"

class Shot : public ISprite
{
public:
	double Speed;
	std::shared_ptr<ISprite> Target;

	Shot()
	{
		View = vCircle;
	}

	Shot(double X,double Y,double Angle)
	{
		View = vCircle;
		Info.X = X;
		Info.Y = Y;
		Info.Angle = Angle;
		Info.Color = Palette::Yellow;
		Info.Width = 10;
		Info.Height = 10;
	}

	void Start() override
	{
		
	}

	void Update() override
	{
		Info.X += Cos(Info.Angle*Pi / 180)*Speed;
		Info.Y += Sin(Info.Angle*Pi / 180)*Speed;
		if (!IsInWindow())
		{
			Manager->DestroyMe();
		}
		if (Target!=nullptr&&IsHit(Target))
		{
			Target->DoEvent(SpriteEvent::Damage,1);
			Manager->DestroyMe();
		}
	}
};