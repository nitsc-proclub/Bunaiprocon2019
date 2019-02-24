#pragma once

#include"CommonData.hpp"

struct Made : public MyApp::Scene
{
public:
	//クラス初期化時に一度だけ呼ばれる
	void init() override
	{
		timer.start();
	}

	//毎フレーム updateAndDraw() で呼ばれる
	void update() override
	{
		if (timer.s() == 5 || Input::KeyEnter.clicked)
		{
			timer.reset();
			changeScene(L"Title");
		}
	}

	// 毎フレーム update() の次に呼ばれる
	void draw() const override
	{
		TextureAsset(L"Siv3D").resize(1280, 720).drawAt(Window::Center());
	}

private:
	Stopwatch timer;
};
