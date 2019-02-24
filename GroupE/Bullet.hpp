#include <Siv3D.hpp>

#define PI 3.14159265
#define WID 1280
#define LEN 720
#define B_SIZE 10

class Bullet {

protected:
	Vec2 B_pos; //弾丸の座標
	Texture B_tex; //弾のテクスチャ
	int a; //傾き的なやつ
	int speed = Random(5,8); //弾丸の速さ
	int b; //yの初期位置 切片的なやつ
	const Font font = Font(10);

public:
	Circle body;

	Bullet(int A, int B, Texture texture) {
		a = A;
		b = B;
		B_pos = { 0, b };
		B_tex = texture;
	}


	virtual void update() = 0;

	virtual void formula(int n) = 0;

	void draw() {
		body = Circle(B_pos, B_SIZE);
		B_tex.resize(20, 20).draw(B_pos.x - B_SIZE, B_pos.y - B_SIZE);
	}


	double geta(void) {
		return a;
	}

	int getspeed(void) {
		return speed;
	}

	int getb() {
		return b;
	}

	int getx() {
		return B_pos.x;
	}


	int gety() {
		return B_pos.y;
	}


	~Bullet()
	{
	}
};