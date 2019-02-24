#pragma once
#include"SpriteCore.h"
#include"SpriteViews.h"
#include"Sprites.h"

class Jiki : public ISprite 
{
public :
	double Speed = 3, dodge = 0, count = 0,
		dcount = 10, avoid = 0, cooltime = 60;//←変更点
	
	
	Jiki()
	{
		View = vRect;
		Info.Width = 10;
		Info.Height = 10;
		Info.Angle = 0;
		Info.X = Random(640);
		Info.Y = Random(480);
		Info.Color = Palette::Forestgreen;
	}
	//変更点↓


	 
	
	void Start() override
	{
		Info.X = 540;
		Info.Y = 240;
		
	}

	void Update() override
	{
		// const Font font(30); font(L"dcount", dcount = dcount).draw({ 100,300 });
		
		++count;

		double SpdBuff = Input::KeyShift.pressed ? Speed / 2 : Speed;
		if (Input::KeyW.pressed)
		{
			Info.Y -= SpdBuff; 
			//変更点↓
			dodge = 1;
		}
		if (Input::KeyS.pressed)
		{
			Info.Y += SpdBuff; 
			//変更点↓
			dodge = 1;
		}
		if (Input::KeyA.pressed)
		{
			Info.X -= SpdBuff; 
			//変更点↓
			dodge = 1;
		}
		if (Input::KeyD.pressed)
		{
			Info.X += SpdBuff; 
			//変更点↓
			dodge = 1;
		}
		if (Input::KeyEnter.pressed)
		{
			Shot*b = new Shot(Info.X,Info.Y,Info.Angle);

			b->Speed = 10;
			b->Tag = L"Shot";

			Manager->Add(b);

			Info.Angle += 5;
		}
		//if (Input::KeyK.pressed) 新しい弾を追加したかった
		//{
			//skill*b = new skill(Info.X, Info.Y, Info.Angle);
		
			//b->Speed = 10;
			
			
			//Manager->Add(b);

			
		//}

		//{
			//auto result = GetHitSp(L"Enemy");
			//Info.Color = result == nullptr ? Palette::Red : Palette::Orange;
		//}
		//回避スプライト　移動キー＆Lキーで回避
		if ( dodge == 1 &&Input::KeyL.pressed&&dcount == 10&&cooltime==60)//移動キー＆Lキーを押した状態かつクールタイム満タンかつ回避時間マックスの時
		{
			cooltime = 0;
			--dcount;
			Speed = 8;
			Info.Color = Palette::Aqua;
			avoid = 1;

		}
		else if (dodge == 1 && Input::KeyL.pressed&&dcount !=0&&cooltime==0 )//↑から移動キー＆Lキーを押した状態で回避中　ここでクールタイムゼロ
		{
			--dcount;
			avoid = 1;
			Info.Color = Palette::Aqua;
			Speed = 8;
		}
		else if (dodge == 1 && Input::KeyL.pressed&&dcount == 0 && cooltime == 0)//↑から移動キー＆Lキーを押した状態クールタイムゼロかつ回避時間ゼロの時
		{
			
			Speed = 3;
			Info.Color = Palette::Forestgreen;
			avoid = 0;
		}

		else if (dcount != 10&&cooltime!=60)//移動キー＆Lキーを離した時
		{
		
			cooltime++;
			Speed = 3;
			Info.Color = Palette::Forestgreen;
			avoid = 0;

		}
		else//移動キー＆Lキーを離した状態クールタイム満タンかつ回避時間マックスの時　いつもの状態
		{
			dcount=10;
			Speed = 3;
			Info.Color = Palette::Forestgreen;
			avoid = 0;
		}

		dodge = 0;
		//変更点↑

		//const Font font(20); font(L"dcount").draw({ 100,100 });UI	を追加したかった
	}


};