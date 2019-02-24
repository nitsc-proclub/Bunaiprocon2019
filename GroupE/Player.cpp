#include "Player.h"

#define WID 1280
#define LEN 720
#define P_SIZE 10

Player::Player(Texture texture)
{
	P_pos = { LEN/2, LEN/2 };
	P_tex = texture;

}

 //ˆÚ“®
void Player::update(double Speed) {
	speed = Speed;

	if (Input::KeyW.pressed && P_pos.y > P_SIZE) P_pos.y = P_pos.y - speed;
	if (Input::KeyS.pressed && P_pos.y < LEN - P_SIZE) P_pos.y = P_pos.y + speed;
	if (Input::KeyD.pressed && P_pos.x < LEN - P_SIZE) P_pos.x = P_pos.x + speed;
	if (Input::KeyA.pressed && P_pos.x > P_SIZE) P_pos.x = P_pos.x - speed;
}

void Player::draw() {
	body = Circle(P_pos, P_SIZE);
	P_tex.resize(20, 20).draw(P_pos.x - P_SIZE, P_pos.y - P_SIZE);
}

int Player::getx() {
	return P_pos.x;
}

int Player::gety() {
	return P_pos.y;
}

void Player::set_pos(Vec2 pos) {
	P_pos = pos;
}

Player::~Player()
{
}
