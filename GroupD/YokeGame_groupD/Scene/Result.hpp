#pragma once

#include"CommonData.hpp"

struct Result : public MyApp::Scene
{
public:
	//�N���X���������Ɉ�x�����Ă΂��
	void init() override
	{

	}

	//���t���[�� updateAndDraw() �ŌĂ΂��
	void update() override
	{
		if (Input::KeyEnter.clicked)
		{
			changeScene(L"Title");
		}
	}

	// ���t���[�� update() �̎��ɌĂ΂��
	void draw() const override
	{
		FontAsset(L"Result")(L"Score").drawAt({ 640, 250 });
		FontAsset(L"Result")(L"", m_data->Score).drawAt({ 640, 450 });
	}

private:

};
