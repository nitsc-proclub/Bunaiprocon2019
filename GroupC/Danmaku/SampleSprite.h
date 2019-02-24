#pragma once
#include"SpriteCore.h"
#include"SpriteViews.h"

class SampleSprite : public ISprite
{
public:
	SampleSprite()
	{
		View = vCircle;
		Info.Width = 10;
		Info.Height = 10;
		Info.Angle = 0;
		Info.X = Random(640);
		Info.Y = Random(480);
		Info.Color = RandomColor();
	}

	void Start() override
	{

	}

	void Update() override
	{
		Info.X = 10;//X座標
		Info.Y = 10;//Y座標
		Info.Width = 20;//横幅
		Info.Height = 20;//縦幅
		Info.Color = Palette::Yellow;//色(「Palette::」から始めて何か色を入れる)
		Info.Angle = 0;//角度
	}
};
