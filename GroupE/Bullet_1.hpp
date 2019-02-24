#include <Siv3D.hpp>

#define PI 3.14159265
#define WID 1280
#define LEN 720

class Bullet_1 : public Bullet {


public:

	using Bullet::Bullet;

	virtual void update() {
		if (B_pos.y > LEN || B_pos.y < 0) B_pos.x = LEN + 20;
		B_pos.x += speed;
		B_pos.y = -1 * 0.5 * a * B_pos.x + b; //’eŠÛ‚ðˆêŽŸŠÖ”‚É
	}

	void formula(int n) override
	{
		font(n + 1, L" : Y = ", 0.5 * a, L"X + (", LEN/2 - b + (0.5 * a * LEN/2), L")").draw(LEN + 30, 170 + 20 * n);
	}
};