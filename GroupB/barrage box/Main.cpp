# include <Siv3D.hpp>
# include <HamFramework.hpp>

struct GameData
{
	int counter = 0;
	Font font{ 30 };
	int32 t;
};

// シーンのキーの型と、共有データの型を指定
using MyApp = SceneManager<String, GameData>;

struct Title : MyApp::Scene
{
	// 毎フレーム updateAndDraw() で呼ばれる
	void update() override
	{
		if (Input::KeyS.clicked)
		{
			// 次のシーケンスと、フェードイン・アウトの時間（ミリ秒）
			changeScene(L"Setsumei", 2000);
		}

		// 共有データにアクセスできる
		m_data->t;
	}

	// 毎フレーム update() の次に呼ばれる
	void draw() const override
	{
		Window::ClientRect().draw(Palette::Black);
		m_data->font(L"Barrage Box").drawCenter(Window::Center());
		m_data->font(L"Sキーを押してね").draw(150, 350);
	}
};

struct Setsumei : MyApp::Scene
{
	// 毎フレーム updateAndDraw() で呼ばれる
	void update() override
	{
		if (Input::KeyS.clicked)
		{
			// 次のシーケンスと、フェードイン・アウトの時間（ミリ秒）
			changeScene(L"Game", 2000);
		}

		// 共有データにアクセスできる
		m_data->t;
	}

	// 毎フレーム update() の次に呼ばれる
	void draw() const override
	{
		Window::ClientRect().draw(Palette::Black);
		m_data->font(L"攻撃側").draw(10, 10);
		m_data->font(L"移動：矢印キー").draw(10, 60);
		m_data->font(L"攻撃：スペースキー").draw(10, 110);
		m_data->font(L"逃げる側").draw(10, 210);
		m_data->font(L"移動：A 左　D 右　W 上　S 下").draw(10, 260);
		m_data->font(L"Sキーを押してね").draw(150, 400);
	}
};

struct Game : MyApp::Scene
{


	//初期値定義・最小値
	int x_shokichi = 125;
	int y_shokichi = 100;

	//長方形の横の長さ
	int yoko = 400;

	//長方形の高さ
	int takasa = 300;

	//x最大値
	int x_saidaichi = yoko + x_shokichi;

	//y最大値
	int y_saidaichi = takasa + y_shokichi;

	//プレイヤー移動速度
	int idousokudo = 5;

	//弾の速度
	double X_s = 5.0;

	double Y_s = 5.0;

	//斜めからの攻撃時弾の方向調整
	double Xshoki_tyousei = 3.8;

	double Yshoki_tyousei = 0.2;

	double Xsaidai_tyousei = -3.7;

	double Ysaidai_tyousei = -0.1;

	//座標の定義
	int x = x_shokichi;
	int y = y_shokichi;

	int x2 = 330;
	int y2 = 250;

	//プレイヤーの攻撃(定義)
	Array<Vec2> shots;

	int32 count = 0;

	//攻撃する弾の感覚
	int speed = 12;

	//定義
	int hp = 10;

	bool x_lr_flag = false, x_rl_flag = false, y_ud_flag = false, y_du_flag = false;
	bool ss_udrl_flag = false, Ss_udlr_flag = false, sS_durl_flag = false, SS_dulr_flag = false;
	//タイマー用
	int time = 30;
	int a = 1;

	void update() override
	{
		count++;

		// 長方形の内側に太さ 16 の白い枠を描く
		const Rect rect(x_shokichi, y_shokichi, 400, 300);
		rect.drawFrame(8, 8, Palette::White);

		//プレイヤー(●)
		const Circle player(x, y, 16);


		//攻撃するプレイヤーの色
		player.draw(Palette::Blue);

		//ゲーム内タイマー
		if (time - count / 60 == 0)//タイムが０になったら止まる
		{
			a = 0;
			changeScene(L"nipiwin", 2000);
		}


		//もし[→]が押されたらX座標+1
		if (Input::KeyRight.pressed)
		{
			if (((x - x_shokichi) % idousokudo) == 0 && x < x_saidaichi && (y == y_shokichi) | (y == yoko))
			{
				x = x + idousokudo;
			}
		}

		//もし[←]が押されたらX座標-1
		if (Input::KeyLeft.pressed)
		{
			if (((x - x_shokichi) % idousokudo) == 0 && x > x_shokichi && (y == y_shokichi) | (y == yoko))
			{
				x = x - idousokudo;
			}
		}

		//もし[↑]が押されたらY座標-1
		if (Input::KeyUp.pressed)
		{
			if (((y - y_shokichi) % idousokudo) == 0 && y > y_shokichi && (x == x_shokichi) | (x == x_saidaichi))
			{
				y = y - idousokudo;
			}
		}

		//もし[↓]が押されたらY座標+1
		if (Input::KeyDown.pressed)
		{
			if (((y - y_shokichi) % idousokudo) == 0 && y < y_saidaichi && (x == x_shokichi) | (x == x_saidaichi))
			{
				y = y + idousokudo;
			}
		}

		//プレイヤー2



		//プレイヤー(●)
		const Circle player2(x2, y2, 16);

		//プレイヤーの色
		player2.draw(Palette::Red);

		//右
		if (x2 >= x_saidaichi - 16)
		{
			if (Input::KeyD.pressed)
			{
				x2 = x2;
			}
		}
		else
		{
			if (Input::KeyD.pressed)
			{
				x2 = x2 + idousokudo;
			}
		}
		//下
		if (y2 >= y_saidaichi - 16)
		{
			if (Input::KeyS.pressed)
			{
				y2 = y2;
			}
		}
		else
		{
			if (Input::KeyS.pressed)
			{
				y2 = y2 + idousokudo;
			}
		}
		//左
		if (x2 <= x_shokichi + 16)
		{
			if (Input::KeyA.pressed)
			{
				x2 = x2;
			}
		}
		else
		{
			if (Input::KeyA.pressed)
			{
				x2 = x2 - idousokudo;
			}
		}
		//上
		if (y2 <= y_shokichi + 16)
		{
			if (Input::KeyW.pressed)
			{
				y2 = y2;
			}
		}
		else
		{
			if (Input::KeyW.pressed)
			{
				y2 = y2 - idousokudo;
			}
		}



		//プレイヤーの攻撃　攻撃する弾のスピード

		if (Input::KeySpace.pressed && count % speed == 0)
		{
			//発射する場所
			shots.push_back(player.center);
		}

		//場所によって打つ弾の方向を変える
		for (const auto& shot : shots)
		{
			RectF(shot, 7).drawFrame(4, 0, Palette::Red);

			if (x == x_shokichi && y == y_shokichi)
			{
				ss_udrl_flag = true;
				sS_durl_flag = false;
				Ss_udlr_flag = false;
				SS_dulr_flag = false;
				x_rl_flag = false;
				x_lr_flag = false;
				y_ud_flag = false;
				y_du_flag = false;
			}
			if (x == x_shokichi && y == y_saidaichi)
			{
				sS_durl_flag = true;
				ss_udrl_flag = false;
				Ss_udlr_flag = false;
				SS_dulr_flag = false;
				x_rl_flag = false;
				x_lr_flag = false;
				y_ud_flag = false;
				y_du_flag = false;
			}
			if (x == x_saidaichi && y == y_shokichi)
			{
				Ss_udlr_flag = true;
				ss_udrl_flag = false;
				sS_durl_flag = false;
				SS_dulr_flag = false;
				x_rl_flag = false;
				x_lr_flag = false;
				y_ud_flag = false;
				y_du_flag = false;
			}
			if (x == x_saidaichi && y == y_saidaichi)
			{
				SS_dulr_flag = true;
				ss_udrl_flag = false;
				sS_durl_flag = false;
				Ss_udlr_flag = false;
				x_rl_flag = false;
				x_lr_flag = false;
				y_ud_flag = false;
				y_du_flag = false;
			}
			if (x == x_saidaichi)
			{
				x_rl_flag = true;
				x_lr_flag = false;
				y_ud_flag = false;
				y_du_flag = false;
			}
			if (x == x_shokichi)
			{
				x_lr_flag = true;
				x_rl_flag = false;
				y_ud_flag = false;
				y_du_flag = false;
			}
			if (y == y_shokichi)
			{
				y_ud_flag = true;
				y_du_flag = false;
				x_lr_flag = false;
				x_rl_flag = false;
			}
			if (y == y_saidaichi)
			{
				y_du_flag = true;
				y_ud_flag = false;
				x_lr_flag = false;
				x_rl_flag = false;
			}
		}
		//弾の方向制御
		for (auto& shot : shots)
		{
			if (x == x_shokichi && y == y_shokichi)
			{
				shot.x += Xshoki_tyousei;
				shot.y += Yshoki_tyousei;
			}
			if (x == x_shokichi && y == y_saidaichi)
			{
				shot.x += Xshoki_tyousei;
				shot.y += Ysaidai_tyousei;
			}
			if (x == x_saidaichi && y == y_shokichi)
			{
				shot.x += Xsaidai_tyousei;
				shot.y += Yshoki_tyousei;

			}
			if (x == x_saidaichi && y == y_saidaichi)
			{
				shot.x += Xsaidai_tyousei;
				shot.y += Ysaidai_tyousei;
			}
			if (x_rl_flag)
			{
				shot.x -= X_s;
			}
			if (x_lr_flag)
			{
				shot.x += X_s;
			}
			if (y_ud_flag)
			{
				shot.y += Y_s;
			}
			if (y_du_flag)
			{
				shot.y -= Y_s;
			}
		}

		if (AnyOf(shots, [=](const Vec2& s) { return player2.intersects(s); }))
		{
			if (hp <= 1)
			{
				hp;
				changeScene(L"itipiwin", 2000);
			}
			else
			{
				hp--;
			}
		}
		m_data->font(hp).draw(180, 20, Palette::Orange);
		m_data->font(L"残りHP").draw(20, 20, Palette::Orange);
		m_data->font(L"秒").draw(460, 20, Palette::Blue);

		//弾の処理(playerに当たった時・壁に当たった時)

		Erase_if(shots, [player2](const Vec2& s)
		{

			bool retval = false;
			if (player2.intersects(s))
			{
				retval = true;
			}
			if ((s.y <= 100) || (s.y >= 400))
			{
				retval = true;
			}
			if ((s.x <= 125) || (s.x >= 525))
			{
				retval = true;
			}
			return retval;
		});
	}
	void draw() const override
	{
		m_data->font((time - count / 60)*a).draw(400, 20, Palette::Blue);
	}
};
struct itipiwin : MyApp::Scene
{
	void update() override
	{
		if (Input::KeyT.clicked)
		{
			// 次のシーケンスと、フェードイン・アウトの時間（ミリ秒）
			changeScene(L"Title", 2000);
		}
	}
	void draw() const override
	{
		Window::ClientRect().draw(Palette::Black);
		m_data->font(L"Tキーを押してね").draw(150, 350);
		m_data->font(L"攻撃側の勝利！").drawCenter(Window::Center());
	}

};

struct nipiwin : MyApp::Scene
{
	void update() override
	{
		if (Input::KeyT.clicked)
		{
			// 次のシーケンスと、フェードイン・アウトの時間（ミリ秒）
			changeScene(L"Title", 2000);
		}
	}
	void draw() const override
	{
		Window::ClientRect().draw(Palette::Black);
		m_data->font(L"Tキーを押してね").draw(150, 350);
		m_data->font(L"逃げる側の勝利！").drawCenter(Window::Center());
	}

};

void Main()
{
	MyApp manager;

	manager.add<Title>(L"Title");
	manager.add<Setsumei>(L"Setsumei");
	manager.add<Game>(L"Game");
	manager.add<nipiwin>(L"nipiwin");
	manager.add<itipiwin>(L"itipiwin");


	while (System::Update())
	{
		if (!manager.updateAndDraw())
			break;
	}
}