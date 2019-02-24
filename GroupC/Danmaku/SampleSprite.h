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
		Info.X = 10;//X���W
		Info.Y = 10;//Y���W
		Info.Width = 20;//����
		Info.Height = 20;//�c��
		Info.Color = Palette::Yellow;//�F(�uPalette::�v����n�߂ĉ����F������)
		Info.Angle = 0;//�p�x
	}
};
