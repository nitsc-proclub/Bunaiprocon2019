#pragma once
#include"CircleView.h"
#include"RectView.h"
#include"ImageView.h"

RectView* vRect = new RectView();
CircleView* vCircle = new CircleView();
ImageView* vImage_Rocket;
ImageView* vImage_Bullets_Counter;
ImageView* vImage_Dobaa;

void SpriteViewsLoad()
{
	vImage_Rocket = new ImageView(L"Assets/rocket-red.png", true, -1);
	vImage_Rocket->HomeX = (double)25 / 2;
	vImage_Rocket->HomeY = 36;
	vImage_Rocket->HomeRot = 90;

	vImage_Bullets_Counter = new ImageView(L"Assets/kometsubu.png", true, -1);
	vImage_Bullets_Counter->HomeX = (double)7 / 2;
	vImage_Bullets_Counter->HomeY = 12;
	vImage_Bullets_Counter->HomeRot = 90;

	vImage_Dobaa = new ImageView(L"Assets/Dobaa_min.png", true, 10);
	vImage_Bullets_Counter->HomeX = 110 / 2;
	vImage_Bullets_Counter->HomeY = 110 / 2;
}