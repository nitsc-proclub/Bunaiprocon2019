#pragma once

#include"CommonData.hpp"

struct Title : public MyApp::Scene
{
private:
	
public:
	//クラス初期化時に一度だけ呼ばれる
	void init() override
	{
		SoundAsset(L"Title").setLoop(true);
		SoundAsset(L"Title").play();
	}

	//毎フレーム updateAndDraw() で呼ばれる
	void update() override
	{
		if (Input::KeyEnter.clicked)
		{
			changeScene(L"SelectStage");
		}
	}

	// 毎フレーム update() の次に呼ばれる
	void draw() const override
	{
		TextureAsset(L"Title").resize(1280, 720).drawAt(Window::Center());
	}

};
