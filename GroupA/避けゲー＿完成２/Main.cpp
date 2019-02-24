# include <Siv3D.hpp>
# include <HamFramework.hpp>


struct GameData
{
public:
	int s = 0;
	int i = 0;
	int32 count = 0;
};

using MyApp = SceneManager<String, GameData>;

class Title : public MyApp::Scene
{
public:
	const Circle circle1 = { { 250,240 }, 70 };
	const Circle circle2 = { { 320,240 }, 70 };
	const Circle circle3 = { { 390,240 }, 70 };

	void update() override
	{
		
		circle1.draw(HSV(0, 1, 1));
		circle2.draw(HSV(120, 1, 1));
		circle3.draw(HSV(240, 1, 1));
		if (Input::KeyEnter.pressed)
		{
			changeScene(L"Game");
		}
	}
	void draw() const override
	{

	}
};
using MyApp = SceneManager<String, GameData>;
class Game : public MyApp::Scene

{
public:
	int t = 0;
	int h = 0;
	int speed = 5;
	int shotspeed = 15;
	Circle player = { { 320,240 },10 };
	const Circle circle = { { 80,410 }, 70 };
	double b = 360.0;//色相
	double c = 1.0;//彩度
	double d = 1.0;//明度
	Array<Vec2> shots, bullets, enemies, enemies2, enemies3, item;


	void init() override
	{
		Stopwatch stopwatch(true);
	}

	void update() override
	{
		if (d <= 0.1)//明度が0になったとき
		{
			changeScene(L"Result");
		}
		
		Vec2 direction(Input::KeyRight.pressed - Input::KeyLeft.pressed, Input::KeyDown.pressed - Input::KeyUp.pressed);
		if (!direction.isZero()) //キーが入力されていれば
		{
			player.moveBy(direction.setLength(speed)); //速さ5でプレイヤーを動かす
			if (player.x < 0)player.x = 0;
			if (player.y < 0)player.y = 0;
			if (player.x > 640)player.x = 640;
			if (player.y > 480)player.y = 480;
		}

		if (m_data->count % (100 - Min(m_data->count / 600, 18)) == 0)
			enemies.emplace_back(Random(50, 550), -40);//敵を生成する範囲と座標

		for (auto& bullet : bullets)//敵の攻撃
			bullet.y += 4.0;

		for (auto& enemy : enemies)
		{
			//敵の移動
			if (enemy.y >= 100)
				enemy.y += 1.0;
			else
				enemy.y += 2.0;//敵の速度

			if (m_data->count % 40 == 0)
				bullets.push_back(enemy);//敵の弾の生成
		}

		if (m_data->count % (40 - Min(m_data->count / 600, 18)) == 0)
			enemies2.emplace_back(Random(40, 600), -40);//敵を生成する範囲と座標

		for (auto& bullet : bullets)
			bullet.y += 7.0;//敵の攻撃

		for (auto& enemy2 : enemies2)
		{
			//敵の速度
			enemy2.y += 5.0;

			if (m_data->count % 60 == 0)
				bullets.push_back(enemy2);//敵の弾の生成
		}

		if (m_data->count % (100 - Min(m_data->count / 600, 18)) == 0)
			enemies3.emplace_back(Random(100, 500), -40);//敵を生成する範囲と座標

		for (auto& enemy3 : enemies3)
		{
			//敵の移動
			if (enemy3.y >= 80)
				enemy3.y += 0;
			else
				enemy3.y += 1.0;//敵の速度

			if (m_data->count % 40 == 0)
				bullets.push_back(enemy3);//敵の弾の生成
		}

		if (Input::Key1.clicked)//１が押されたとき赤←ここを当たり判定に
		{
			b = 0;

			speed = 5;
		}

		if (Input::Key2.clicked)//２が押されたとき緑←ここを当たり判定に
		{
			b = 120;

			speed = 3;
			if (d >= 8)
				d = d + 0.2;//明度を下げる（だんだん白になる）
		}

		if (Input::Key3.clicked)//３が押されたとき青←ここを当たり判定に
		{
			
			b = 240;

			speed = 10;

			shotspeed = 5;

			d = d - 0.4;

			if (d <= 0.4)
			{
				b == 1;
			}
			
		}

		if (AnyOf(bullets, [=](const Vec2& b) { return player.intersects(b); }))
		{
			if (d <= 0.1)
				d;

			else
				d = d - 0.1;
            
		}

		if (Input::KeyF.pressed)//Fが押されたとき
		{
			h++;

			if (0 == h % shotspeed)
			{
				shots.push_back(player.center);
			}
		}
		for (auto& shot : shots)
		{
			shot.y -= 8.0;//弾の速さ
		}

		player.draw(HSV(b, c, d));
	}
	void draw() const override
	{
		++m_data->count;

		const int32 skyOffset = System::FrameCount() % 960 * 8;

		//敵の弾の形
		for (const auto& bullet : bullets)
			RectF(bullet, 2, 10).draw(Palette::Gray);

		for (const auto& enemy : enemies)
			RectF(20, 20).setCenter(enemy).rotated(enemy.y / 1.9).drawFrame(2, 0, HSV(1, 1, 1));//敵の形

		for (const auto& enemy2 : enemies2)
			RectF(20, 20).setCenter(enemy2).rotated(enemy2.y / 1.9).drawFrame(2, 0, HSV(120, 1, 1));//敵の形

		for (const auto& enemy3 : enemies3)
			RectF(20, 20).setCenter(enemy3).rotated(enemy3.y / 1.9).drawFrame(2, 0, HSV(240, 1, 1));//敵の形

		for (const auto& shot : shots)
		{
			Circle(shot, 7).draw(HSV(b, c, d));//弾の色など
		}

		Erase_if(shots, [&](const Vec2& e2) {//shotに当たったenemiesを消す
			if (AnyOf(enemies, [=](const Vec2& s) { return e2.intersects(s); }))
			{
				return true;
			}

		});

		Erase_if(shots, [&](const Vec2& e3) {//shotに当たったenemies2を消す
			if (AnyOf(enemies2, [=](const Vec2& s2) { return e3.intersects(s2); }))
			{
				return true;
			}

		});

		Erase_if(shots, [&](const Vec2& e4) {//shotに当たったenemies3を消す
			if (AnyOf(enemies3, [=](const Vec2& s3) { return e4.intersects(s3); }))
			{
				return true;
			}

		});
	}
}; class Result : public MyApp::Scene

{
public:
	void update() override
	{
		if (Input::KeyEnter.clicked)
		{
			changeScene(L"Title", 2000);
		}
	}
	void draw() const override
	{

	}
};

void Main()
{
	MyApp manager;
	// フェードイン・アウト時の色
	manager.setFadeColor(Palette::White);
	manager.add<Title>(L"Title");
	manager.add<Game>(L"Game");
	manager.add<Result>(L"Result");

	while (System::Update())
	{
		if (!manager.updateAndDraw())
		{
			break;
		}
	}
}
