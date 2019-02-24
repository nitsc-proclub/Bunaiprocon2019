#include <Siv3D.hpp>
#include <math.h>
#include "Player.h"
#include "Bullet.hpp"
#include "Bullet_sin.hpp"
#include "Bullet_1.hpp"


#define WID 1280 //画面横幅
#define LEN 720 //画面縦幅


void Main()
{
	Window::Resize(WID, LEN);
	Graphics::SetBackground(Palette::Gray);


	int hp = 10; //プレイヤーのHP
	int bullet_num = 0; //弾の数
	int wave = 0; //ウェーブ（ターン、面、ラウンド）数
	bool start_flag = false; 
	bool intersects_flag = false; 
	bool waveend_flag = true; 
	bool onetime = true; 
	const Texture buckground(L"Texture/function.png"); //背景
	const Texture buckgroundDM(L"Texture/functionDM.png"); //背景(ダメージ)
	const Texture UFOmeno(L"Texture/UFOmeno.png"); //プレイヤーテクスチャ
	const Texture UFOr(L"Texture/UFOr.png"); //弾のテクスチャ
	const Texture UFOb(L"Texture/UFOb.png"); //弾のテクスチャ
	const Texture ARE(L"Texture/gameover.jpg");
	const Sound damage_sound(L"Sound/dededon.wav"); 
	const Sound gameover(L"Sound/tin.wav");
	const Font font1(35);
	const Font font2(15);
	const Font font3(100, Typeface::Black, FontStyle::Italic); 
	Stopwatch stopwatch(true);

	Player player(UFOmeno); //自機
	Array<std::shared_ptr<Bullet>> bullets; //弾丸

	while (System::Update())
	{

		if (start_flag == false) { //スタート画面
			font3(L"関数避けゲー").drawCenter(LEN / 2 - 100 - font3.ascent);
			font2(L"(仮)").draw(1080, LEN / 2 - 100 - font2.ascent);
			font2(L"スペースキーでスタート").drawCenter(LEN / 2 + 100);
			if (Input::KeySpace.clicked) {
				start_flag = true;
			}
		}
		else {
			if (hp > 0) { //プレイ画面
				//ポーズ関係なく常時行う処理
				font1(L"WAVE ", wave).draw(LEN + 30, 5, Palette::Red);
				font2(L"プレイヤー座標 : (", player.getx(), L", ", player.gety(), L")").draw(LEN + 30, 80);
				font2(L"HP :", hp, L" / 10").draw(LEN + 30, 120);
				if(intersects_flag) {
					buckgroundDM.resize(LEN, LEN).draw();
					intersects_flag = false;
				}
				else buckground.resize(LEN, LEN).draw();
				player.draw();

				//弾の式を表示
				for (int i = 0; i < bullets.size(); ++i) {
					bullets[i]->formula(i);
				}



				//ポーズ時の処理
				if (stopwatch.isPaused()) {
					if (bullets.size() == 0)
						for (int i = 0; i < bullet_num; ++i) { // 弾を生成
							switch (Random(0, 1)) {
							case 0: bullets.push_back(std::shared_ptr<Bullet>(new Bullet_sin({ Random(0, 8), Random(0, LEN), UFOr }))); break; //int A, int B
							case 1: bullets.push_back(std::shared_ptr<Bullet>(new Bullet_1({ Random(-2, 2), Random(0, LEN), UFOb }))); break;
							default: break;
							}
						}

					player.update(9);
					//スペースキーでポーズ解除
					if (Input::KeySpace.clicked) {
						stopwatch.resume();
					}
				}


				//ポーズしてない時の処理
				else {
					player.update(0.5);

					//waveend_flagが立って、ポーズさせるときの処理
					if (waveend_flag) {
						waveend_flag = false;
						if (bullet_num < 25) ++bullet_num;
						++wave;
						stopwatch.pause();
					}
					else { //弾飛来中の処理

						//弾たちの処理1
						for (int i = 0; i < bullets.size(); ++i) {
							bullets[i]->update();
							bullets[i]->draw();
							//衝突判定
							if (player.body.intersects(bullets[i]->body) == true) {
								intersects_flag = true;
							}
						}

						//弾たちの処理2
						for (int i = 0; i < bullets.size(); ++i) {
							if (bullets[i]->getx() >= LEN) { //弾丸が画面外に出たら
								bullets.erase(bullets.begin() + i); //弾を消す
								if (bullets.size() == 0) waveend_flag = true;
							}
						}

						// 衝突処理
						if (intersects_flag) {
							if (Random(0, 100) == 0) {
								ARE.resize(WID, LEN).draw();
							}
							--hp;
							damage_sound.play();
						}

					}
				}
			}
			//ゲームオーバー時
			else {
				if (onetime) { //ち～ん(笑)再生
					gameover.play();
					onetime = false;
				}
				font3(L"GAME OVER").drawCenter(LEN / 2 - 200);
				font1(L"スコア : ", wave).drawCenter(LEN / 2 + 100);
				font2(L"スペースキーでリスタート").drawCenter(LEN / 2 + 200);
				if (Input::KeySpace.clicked) { //リスタート処理
					bullets.clear(); //弾を全消去
					bullets.shrink_to_fit(); //弾のメモリ開放
					//各変数を再初期化
					hp = 10; 
					bullet_num = 0;
					wave = 0;
					intersects_flag = false;
					waveend_flag = true;
					onetime = true;
					player.set_pos({ LEN / 2, LEN / 2 });
				}
			}
		}
	}
}