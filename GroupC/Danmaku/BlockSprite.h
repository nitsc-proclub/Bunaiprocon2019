#pragma once
#include"SpriteCore.h"
#include"SpriteViews.h"

class BlockSprite : public ISprite
{
private:
	int num;
public:
	std::shared_ptr<ISprite> Target;

	BlockSprite(std::shared_ptr<ISprite> target,int sx,int sy,int ex,int ey)
	{
		View = vCircle;
		Info.Width = 0;
		Info.Height = 0;
		Info.Angle = 0;
		Info.X = Random(sx,ex);
		Info.Y = Random(sy,ey);
		Info.Color = RandomColor();
		num = 1;
		Tag = L"Enemy";
		Target = target;
	}

	void Start() override
	{

	}

	void Update() override
	{
		double Size = Abs(Sin(num*Pi / 360)) * 20;
		Info.Width = Size;
		Info.Height = Size;
		num = (num + 1) % 360;
		if (IsHit(Target))
		{
			Target->DoEvent(SpriteEvent::Damage,1);
		}
		if (num == 0) {
			Manager->DestroyMe();
		}
	}
};
