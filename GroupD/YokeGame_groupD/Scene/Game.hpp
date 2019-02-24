#pragma once

#include"CommonData.hpp"
#include"Player.hpp"
#include"RecoveryItem.hpp"
#include"Enemy2.hpp"

#define Enemy_amount 20

struct Game : public MyApp::Scene
{
private:
	Player m_player;
	RecoveryItem item;
	Enemy2 enemy2;
	Line Wall[4];
	Stopwatch time;


	Circle enemy1[Enemy_amount];
	int enemy1_pos_x[Enemy_amount];
	int enemy1_pos_y[Enemy_amount];
	int enemy1_speed_x[Enemy_amount];
	int enemy1_speed_y[Enemy_amount];
	bool enemy1_alive[Enemy_amount];
	

public:

	//クラス初期化時に一度だけ呼ばれる
	void init() override
	{
		m_data->Score = 0;

		for (int i = 0; i < Enemy_amount; i++)
		{
			enemy1_pos_x[i] = 0;
			enemy1_pos_y[i] = 0;
			enemy1_speed_x[i] = 0;
			enemy1_speed_y[i] = 0;
			enemy1_alive[i] = false;
		}

		Wall[0] = {100, 10, 800, 10};
		Wall[1] = {100, 10, 100, 710};
		Wall[2] = {800, 10, 800, 710};
		Wall[3] = {100, 710, 800, 710};
		
		m_player = Player();
		m_player.init();
		m_player.create_HP_bar(900, 600, 250, 60);


		item = RecoveryItem();
		item.init();

		enemy2 = Enemy2();
		enemy2.init();
	

		SoundAsset(L"Game").setLoop(true);
		SoundAsset(L"Game").play();

		time.restart();
	}

	//毎フレーム updateAndDraw() で呼ばれる
	void update() override
	{
		if (m_player.player_hp == 0)
		{
			time.pause();
			SoundAsset(L"Game").stop();
			changeScene(L"Result", 1000, true);
		}
		
		m_player.update();

		if (item.item_alive == false && RandomBool(0.00125))//RandomBoolは1.00で100%trueになります。
		{
			item.item_spawn();//アイテムの生成
		}

		if (item.item_alive)
		{
			item.update();
		}

		//当たり判定に使っているintersectsの処理がここにないと動かなかったのでここに置きました。
		if (item.event_lock == 0 && m_player.player_collider.intersects(item.item_collider))
		{
			item.event_lock = 1;
			m_player.damage_hp(-20);
			item.item_alive = false;//このタイミングでアイテムが消えます。
			m_data->Score += 100000;
		}


		if (enemy2.enemy2_alive == false && RandomBool(0.005)) enemy2.enemy2_spawn();

		enemy2.update();
		if (enemy2.can_avoid == false && m_player.muteki == false)
		{
			if (m_player.player_collider.intersects(enemy2.enemy2))
			{
				m_player.damage_hp(30);
			}
		}
		
		//ごめんなさい。普通のenemyをクラスで実装するのができませんでした。
		for (int n = 0; n < Enemy_amount; n++)
		{
			if (enemy1_alive[n])
			{
				enemy1_pos_x[n] += enemy1_speed_x[n];
				enemy1_pos_y[n] += enemy1_speed_y[n];

				if (enemy1_pos_x[n] > 820 || enemy1_pos_x[n] < 80 || enemy1_pos_y[n] > 730)
				{
					enemy1_alive[n] = false;
					continue;
				}
				enemy1[n] = Circle(enemy1_pos_x[n], enemy1_pos_y[n], 15);

				if (m_player.player_collider.intersects(enemy1[n]) && m_player.muteki == false)
				{
					m_player.damage_hp(10);
				}
				
			}
			else
			{
				enemy1_alive[n] = true;
				enemy1_pos_x[n] = Random(120, 780);
				enemy1_pos_y[n] = 0;
				enemy1_speed_x[n] = Random(-3, 3);
				enemy1_speed_y[n] = Random(4, 8);
			}
		}

		

	}

	// 毎フレーム update() の次に呼ばれる
	void draw() const override
	{
		item.draw();
		enemy2.draw();
		
		m_data->Score = time.s() * 1000;

		for (int m = 0; m < Enemy_amount; m++)
		{
			if (enemy1_alive[m]) enemy1[m].draw(Color(255, 255, 200));
		}

		Rect(100, 10, 700, 700).drawFrame(0, 500, Color(0, 0, 0));

		m_player.draw();

		Rect(100, 10, 700, 700).drawFrame(0, 20, Color(0, 0, 0));
		for (int i = 0; i < 4; i++)
		{
			Wall[i].draw(Palette::White);
		}
		FontAsset(L"SystemFont")(L"Score").draw({900, 100});
		FontAsset(L"SystemFont")(L"", m_data->Score).drawCenter({ 1000, 200 });
		if(time.s() < 5)	FontAsset(L"SystemFont")(L"Stage1").draw();
	}

};
