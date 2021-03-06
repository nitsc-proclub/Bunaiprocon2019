#pragma once
#include <Siv3D.hpp>

class Player
{
public:	
	Player(Texture texture);
	void update(double Speed);
	void draw();
	int getx();
	int gety();
	void set_pos(Vec2 pos);
	~Player();

	Circle body;

private:
	Vec2 P_pos; //自機の座標
	Texture P_tex;
	double speed; //自機の速さ
};

