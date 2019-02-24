
#pragma once

#include"Scene/CommonData.hpp"

class Player
{
public:
	int game_difficulty_num;//急造の難易度設定

	int play_area[4] = { 107, 790, 17, 700 }; //移動可能範囲の座標　0,1 == 左端,右端　2,3 == 上端,下端
	Rect player_collider;//プレイヤーの当たり判定
	double player_speed = 1; //外的要因によって自機の速度を変えたいときはこれをいじってください

	int player_hp = 100;
	double player_hp_max = 100;

	int muteki_time = 60;
	bool muteki = false;
	

	//ゲームのシーンのクラスでinitの時に実行してほしい関数
	void create_HP_bar(int pos_x, int pos_y, int width, int height)
	{
		//始点の座標
		hp_pos_x = (double)pos_x;
		hp_pos_y = (double)pos_y;

		//幅、高さ
		hp_bar_width = (double)width;
		hp_bar_height = (double)height;

		hp_base = Rect(pos_x, pos_y, width, height);
		green_hp = Rect(pos_x, pos_y, width, height);
	}


	//ダメージを受けるときに実行
	void damage_hp(int damage)
	{
		player_hp -= damage;//hpを減らす
		if (damage > 0) muteki = true, muteki_time = 60;
		if (player_hp < 0) player_hp = 0;
		if (player_hp > 100) player_hp = 100;

		//減ったHPに合わせて緑色の四角を再設定
		damage_temp = hp_bar_width * (player_hp / player_hp_max);

		green_hp = Rect(hp_pos_x, hp_pos_y, damage_temp, hp_bar_height);
	}


	void init()
	{
		//自機の初期位置
		pos_x = (play_area[0] + play_area[1]) / 2;
		pos_y = (play_area[2] + play_area[3]) / 2;
		player_collider = Rect(pos_x, pos_y, 14,13);


	}


	void update()
	{
		move_dist = base_dist * player_speed;//標準の速度 * 外的要因による倍率変動

		//入力受け取り
		if (Input::KeyUp.pressed) pos_y -= move_dist;
		if (Input::KeyDown.pressed) pos_y += move_dist;
		if (Input::KeyLeft.pressed) pos_x -= move_dist;
		if (Input::KeyRight.pressed) pos_x += move_dist;

		//範囲外に出そうになった時の処理
		if (pos_x < play_area[0]) pos_x = play_area[0];
		if (pos_x > play_area[1]) pos_x = play_area[1];
		if (pos_y < play_area[2]) pos_y = play_area[2];
		if (pos_y > play_area[3]) pos_y = play_area[3];

		player_collider = Rect(pos_x - 6, pos_y - 7, 14, 13);//幅14,高さ13はテクスチャの大きさ

		if (muteki) muteki_time--;
		if (muteki_time < 1) muteki = false, muteki_time = 0;
	}


	void draw() const
	{
		player_collider.draw(Color(0, 0, 0, 0));//あくまで当たり判定なので透明にしたい
		player_image.draw(pos_x - 6, pos_y - 7);

		if (muteki_time < 50 && muteki_time > 42) player_collider.draw(Color(255, 255, 255, 255));
		if (muteki_time < 30 && muteki_time > 22) player_collider.draw(Color(255, 255, 255, 255));
		if (muteki_time < 10 && muteki_time > 2) player_collider.draw(Color(255, 255, 255, 255));

		if(player_hp >= 0) green_hp.draw(Color(60, 255, 60));//hpが0になっても緑色の線が描画されてしまうため、条件付き

		hp_base.drawFrame(0,5,Color(255,255,255));
		hp_base.drawFrame(1,0, Color(60,60,60));
		

		hp_text(L"HP: ", player_hp).draw(hp_pos_x, hp_pos_y - 40);//40は、fontの大きさ * 2
	}


private:
	double pos_x, pos_y, move_dist;
	double base_dist = 5;
	double hp_pos_x, hp_pos_y, hp_bar_width, hp_bar_height, damage_temp;//damage_tempはダメージ処理の時に使います。

	Rect hp_base;//HPバーの枠
	Rect green_hp;//緑色の部分

	Font hp_text = Font(20);

	Texture player_image = Texture(L"Texture/player1.png");//リソースファイルに配置するとうまくいかなかったので相対パス推奨

};


