#pragma once

#include"CommonData.hpp"

struct Title : public MyApp::Scene
{
private:
	
public:
	//�N���X���������Ɉ�x�����Ă΂��
	void init() override
	{
		SoundAsset(L"Title").setLoop(true);
		SoundAsset(L"Title").play();
	}

	//���t���[�� updateAndDraw() �ŌĂ΂��
	void update() override
	{
		if (Input::KeyEnter.clicked)
		{
			changeScene(L"SelectStage");
		}
	}

	// ���t���[�� update() �̎��ɌĂ΂��
	void draw() const override
	{
		TextureAsset(L"Title").resize(1280, 720).drawAt(Window::Center());
	}

};
