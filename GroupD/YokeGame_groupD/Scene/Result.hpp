#pragma once

#include"CommonData.hpp"

struct Result : public MyApp::Scene
{
public:
	//クラス初期化時に一度だけ呼ばれる
	void init() override
	{

	}

	//毎フレーム updateAndDraw() で呼ばれる
	void update() override
	{
		if (Input::KeyEnter.clicked)
		{
			changeScene(L"Title");
		}
	}

	// 毎フレーム update() の次に呼ばれる
	void draw() const override
	{
		FontAsset(L"Result")(L"Score").drawAt({ 640, 250 });
		FontAsset(L"Result")(L"", m_data->Score).drawAt({ 640, 450 });
	}

private:

};
