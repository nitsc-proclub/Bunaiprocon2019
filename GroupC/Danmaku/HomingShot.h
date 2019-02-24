#pragma once
#include"SpriteCore.h"
#include"SpriteViews.h"

class HomingShot : public ISprite
{
public:
	double Speed;
	double Precision;
	std::shared_ptr<ISprite> Target;

	HomingShot(const std::shared_ptr<ISprite> target)
	{
		View = vImage_Rocket;
		Target = target;
		Speed = 10;
		Precision = 0.7;
	}

	HomingShot(double X, double Y, double Angle, const std::shared_ptr<ISprite> target)
	{
		View = vImage_Rocket;
		Target = target;
		Speed = 10;
		Precision = 0.5;
		Info.X = X;
		Info.Y = Y;
		Info.Angle = Angle;
	}

	void Start() override
	{

	}

	void Update() override
	{
		double atanAng = Atan2(Target->Info.Y - Info.Y, Target->Info.X - Info.X) * 180 / Pi;

		atanAng = Fmod((360 + atanAng), 360);

		double diffLeft;
		double diffRight;
		if (Info.Angle < atanAng)
		{
			diffLeft = -((360 - atanAng) + Info.Angle);
			diffRight = atanAng - Info.Angle;
		}
		else
		{
			diffLeft = Info.Angle - atanAng;
			diffRight = ((360 - Info.Angle) + atanAng);
		}

		if (Abs(diffLeft) > Abs(diffRight))
		{
			Info.Angle += Precision;
		}
		else
		{
			Info.Angle -= Precision;
		}

		Info.X += Cos(Info.Angle*Pi / 180)*Speed;
		Info.Y += Sin(Info.Angle*Pi / 180)*Speed;

		if (!IsInWindow())
		{
			Manager->DestroyMe();
		}
		if (Target != nullptr&&IsHit(Target))
		{
			Target->DoEvent(SpriteEvent::Damage,1);
			Manager->DestroyMe();
		}
	}
};