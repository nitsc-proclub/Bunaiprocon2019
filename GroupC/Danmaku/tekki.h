#pragma once

#include"SpriteCore.h"

#include"SpriteViews.h"



class tekki : public ISprite

{
public:
	double Speed = 3, dodge = 0, count = 0,
		dcount = 10, avoid = 0, cooltime = 60;
	//←変更点
	tekki()

	{

		View = vRect;

		Info.Width = 10;

		Info.Height = 10;

		Info.Angle = 0;

		Info.X = Random(640);

		Info.Y = Random(480);

		Info.Color = Color(197, 78, 160);
		Tag = L"";

	}



	void Start() override

	{

		Info.X = 100;
		Info.Y = 240;

	}



	void Update() override

	{
		double SpdBuff = Input::KeyShift.pressed ? Speed / 2 : Speed;
		if (Input::KeyUp.pressed)
		{
			Info.Y -= SpdBuff;
			//変更点↓
			dodge = 1;
		}
		if (Input::KeyDown.pressed)
		{
			Info.Y += SpdBuff;
			//変更点↓
			dodge = 1;
		}
		if (Input::KeyLeft.pressed)
		{
			Info.X -= SpdBuff;
			//変更点↓
			dodge = 1;
		}
		if (Input::KeyRight.pressed)
		{
			Info.X += SpdBuff;
			//変更点↓
			dodge = 1;
		}
		if (Input::KeySpace.pressed)
		{
			Shot*b = new Shot(Info.X, Info.Y, Info.Angle);

			b->Speed = 10;
			b->Tag = L"Shot";

			Manager->Add(b);
			Info.Angle += 5;

		}
		//回避スプライト　移動キー＆Cキーで回避
		if (dodge == 1 && Input::KeyC.pressed&&dcount == 10 && cooltime == 60)//移動キー＆Lキーを押した状態かつクールタイム満タンかつ回避時間マックスの時
		{
			cooltime = 0;
			--dcount;
			Speed = 8;
			Info.Color = Palette::Aqua;
			avoid = 1;

		}
		else if (dodge == 1 && Input::KeyC.pressed&&dcount != 0 && cooltime == 0)//↑から移動キー＆Lキーを押した状態で回避中　ここでクールタイムゼロ
		{
			--dcount;
			avoid = 1;
			Info.Color = Palette::Aqua;
			Speed = 8;
		}
		else if (dodge == 1 && Input::KeyC.pressed&&dcount == 0 && cooltime == 0)//↑から移動キー＆Lキーを押した状態クールタイムゼロかつ回避時間ゼロの時
		{

			Speed = 3;
			Info.Color = Color(197, 78, 160);
			avoid = 0;
		}

		else if (dcount != 10 && cooltime != 60)//移動キー＆Lキーを離した時
		{

			cooltime++;
			Speed = 3;
			Info.Color = Color(197, 78, 160);
			avoid = 0;

		}
		else//移動キー＆Lキーを離した状態クールタイム満タンかつ回避時間マックスの時　いつもの状態
		{
			dcount = 10;
			Speed = 3;
			Info.Color = Color(197, 78, 160);
			avoid = 0;
		}

	}

};