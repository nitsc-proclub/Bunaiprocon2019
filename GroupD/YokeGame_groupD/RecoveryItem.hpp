#pragma once

#include "Scene/CommonData.hpp"


class RecoveryItem
{
public :
	bool item_alive;//画面内に一個だけ生成したいため

	int event_lock;//数フレームの間当たっていることになってしまったため、対策

	Rect item_collider;//当たり判定に使う

	void item_spawn()
	{
		pos_x = Random(100, 780);//アイテムが落ちてくる座標をランダムに設定
		pos_y = 10;//出現する初期位置
		item_alive = true;
		event_lock = 0;
	}

	void init()
	{
		item_alive = false;
		fall_speed = 3;
		item_image = Texture(L"Texture/RecoveryItem.png");//例によってリソースファイルに配置せずに相対パスでお願いします。
	}


	void update()
	{
		//アイテムが画面内にある時に実行
		if (item_alive)
		{
			pos_y += fall_speed;
			item_collider = Rect(pos_x, pos_y, 20, 20);
		}

		//枠の範囲内に出たときに消すためのフラグ
		if (713 < pos_y)
		{
			item_alive = false;
		}
	}


	void draw() const
	{
		if (item_alive)
		{
			item_collider.draw(Color(0,0,0,0));//例によって透明
			item_image.draw(pos_x, pos_y);//当たり判定に重なるようにテクスチャを描画
		}
	}
	

private :
	int pos_x, pos_y, fall_speed;

	Texture item_image;
};