#pragma once
#include "Scene/CommonData.hpp"

class Enemy2
{
public:
	bool enemy2_alive;
	bool can_avoid;
	int avoid_grace;
	int alive_time;
	int enemy2_base_pos;
	int enemy2_width_max;
	int enemy2_width_min;
	Rect enemy2;

	void enemy2_spawn()
	{
		enemy2_base_pos = Random(100, 800);
		enemy2_width_min = 0;
		enemy2_width_max = Random(50, 200);
		enemy2 = Rect(enemy2_base_pos - enemy2_width_max, 0, enemy2_width_max * 2 , 1000);
		can_avoid = true;
		enemy2_alive = true;
		avoid_grace = 90;
	}

	void init()
	{
		enemy2_alive = false;
		can_avoid = true;
	}

	void update()
	{
		if (avoid_grace > 0 && enemy2_alive == true && can_avoid == true)
		{
			avoid_grace--;
			if (avoid_grace < 1) avoid_grace = 0, can_avoid = false;
		}

		if (avoid_grace < 1 && enemy2_alive == true && can_avoid == false)
		{
			enemy2 = Rect((enemy2_base_pos -= 3), 0, (enemy2_width_min += 3) * 2, 1000);
			if (enemy2_width_min >= enemy2_width_max)
			{
				can_avoid = true;
				enemy2_alive = false;
			}
		}
	}

	void draw() const
	{
		if (enemy2_alive == true && can_avoid == true)
		{
			enemy2.drawFrame(2, 0, Color(255, 0, 0));
			enemy2.draw(Color(255, 150, 150, 125));
		}
		if (enemy2_alive == true && can_avoid == false)
		{
			enemy2.draw(Color(0, 0, 255));
		}
			
	}
};