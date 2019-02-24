#pragma once

#include"CommonData.hpp"


struct SelectStage : public MyApp::Scene
{
public:

	void init() override
	{

	}

	void update() override
	{
		frame1 = rect1.mouseOver;
		frame2 = rect2.mouseOver;
		frame3 = rect3.mouseOver;
		frame4_1 = rect4.mouseOver;
		frame5_1 = rect5.mouseOver;

		switch (state)
		{
		case 0:
			if (frame1 && Input::MouseL.clicked)
			{
				state = 1;
				frame1_1 = true;
			}

			if (frame2 && Input::MouseL.clicked)
			{
				state = 1;
				frame2_1 = true;
			}

			if (frame3 && Input::MouseL.clicked)
			{
				state = 1;
				frame3_1 = true;
			}
			break;

		case 1:
			if (frame4_1 && Input::MouseL.clicked)
			{
				SoundAsset(L"Title").stop();
				changeScene(L"Game");
			}

			if (frame5_1 && Input::MouseL.clicked)
			{
				state = 0;
				frame1_1 = false;
				frame2_1 = false;
				frame3_1 = false;

			}

		default:
			break;


		}

	}

	void draw() const override
	{
		rect1.draw();
		if (frame1 && state == 0) rect1.drawFrame(10, 0, Palette::Red);
		if (frame1_1 && state == 1) rect1.drawFrame(10, 0, Palette::Blue);

		rect2.draw();
		if (frame2 && state == 0) rect2.drawFrame(10, 0, Palette::Red);
		if (frame2_1 && state == 1) rect2.drawFrame(10, 0, Palette::Blue);

		rect3.draw();
		if (frame3 && state == 0) rect3.drawFrame(10, 0, Palette::Red);
		if (frame3_1 && state == 1) rect3.drawFrame(10, 0, Palette::Blue);

		if (state == 1)
		{
			darkEffect.draw(Color(10, 10, 10, 90));
			rect4.draw();
			rect5.draw();
			rect6.draw(Palette::Gray);

			FontAsset(L"SystemFont")(L"Are you ready?").draw(350, 240, Color(Palette::Orange));
			FontAsset(L"SystemFont")(L"Cancel").drawCenter(280, 600, Color(0,0,0));
			FontAsset(L"SystemFont")(L"Start").drawCenter(1000, 600, Color(0,0,0));

			if(frame4_1) rect4.drawFrame(7, 0, Palette::Red);
			if(frame5_1) rect5.drawFrame(7, 0, Palette::Red);
		}


	}

private:
	const Rect rect1 = Rect(20, 20, 400, 400);
	const Rect rect2 = Rect(440, 20, 400, 400);
	const Rect rect3 = Rect(860, 20, 400, 400);
	const Rect rect4 = Rect(800, 500, 400, 200); //start
	const Rect rect5 = Rect(80, 500, 400, 200); //cancel
	const Rect rect6 = Rect(0, 200, 1280, 200);
	const Rect darkEffect = Rect(0, 0, 1280, 720);

	bool frame1 = false;
	bool frame2 = false;
	bool frame3 = false;
	bool frame1_1 = false;
	bool frame2_1 = false;
	bool frame3_1 = false;
	bool frame4_1 = false;
	bool frame5_1 = false;

	int state = 0;

};