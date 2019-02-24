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
		B_pos.y = -200 * sin((PI * B_pos.x / LEN) * a) + b; //�e�ۂ��T�C���J�[�u��
	}


	void formula(int n) override
	{
		font(n + 1, L" : Y = sin(", a, L"��X) + (",LEN/2 - b, L")").draw(LEN + 30, 170 + 20 * n);
	}

};