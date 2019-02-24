#pragma once

#include"CommonData.hpp"

struct Made : public MyApp::Scene
{
public:
	//�N���X���������Ɉ�x�����Ă΂��
	void init() override
	{
		timer.start();
	}

	//���t���[�� updateAndDraw() �ŌĂ΂��
	void update() override
	{
		if (timer.s() == 5 || Input::KeyEnter.clicked)
		{
			timer.reset();
			changeScene(L"Title");
		}
	}

	// ���t���[�� update() �̎��ɌĂ΂��
	void draw() const override
	{
		TextureAsset(L"Siv3D").resize(1280, 720).drawAt(Window::Center());
	}

private:
	Stopwatch timer;
};
