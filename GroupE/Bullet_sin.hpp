#include <Siv3D.hpp>

#define PI 3.14159265
#define WID 1280
#define LEN 720

class Bullet_sin : public Bullet {


public:

	using Bullet::Bullet;

	void update() override
	{
		B_pos.x += speed;
		B_pos.y = -200 * sin((PI * B_pos.x / LEN) * a) + b; //弾丸をサインカーブに
	}


	void formula(int n) override
	{
		font(n + 1, L" : Y = sin(", a, L"πX) + (",LEN/2 - b, L")").draw(LEN + 30, 170 + 20 * n);
	}

};