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
	Vec2 P_pos; //é©ã@ÇÃç¿ïW
	Texture P_tex;
	double speed; //é©ã@ÇÃë¨Ç≥
};

