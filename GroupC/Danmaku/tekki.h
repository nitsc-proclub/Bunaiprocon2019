#pragma once

#include"SpriteCore.h"

#include"SpriteViews.h"



class tekki : public ISprite

{
public:
	double Speed = 3, dodge = 0, count = 0,
		dcount = 10, avoid = 0, cooltime = 60;
	//���ύX�_
	tekki()

	{

		View = vRect;

		Info.Width = 10;

		Info.Height = 10;

		Info.Angle = 0;

		Info.X = Random(640);

		Info.Y = Random(480);

		Info.Color = Color(197, 78, 160);
		Tag = L"";

	}



	void Start() override

	{

		Info.X = 100;
		Info.Y = 240;

	}



	void Update() override

	{
		double SpdBuff = Input::KeyShift.pressed ? Speed / 2 : Speed;
		if (Input::KeyUp.pressed)
		{
			Info.Y -= SpdBuff;
			//�ύX�_��
			dodge = 1;
		}
		if (Input::KeyDown.pressed)
		{
			Info.Y += SpdBuff;
			//�ύX�_��
			dodge = 1;
		}
		if (Input::KeyLeft.pressed)
		{
			Info.X -= SpdBuff;
			//�ύX�_��
			dodge = 1;
		}
		if (Input::KeyRight.pressed)
		{
			Info.X += SpdBuff;
			//�ύX�_��
			dodge = 1;
		}
		if (Input::KeySpace.pressed)
		{
			Shot*b = new Shot(Info.X, Info.Y, Info.Angle);

			b->Speed = 10;
			b->Tag = L"Shot";

			Manager->Add(b);
			Info.Angle += 5;

		}
		//����X�v���C�g�@�ړ��L�[��C�L�[�ŉ��
		if (dodge == 1 && Input::KeyC.pressed&&dcount == 10 && cooltime == 60)//�ړ��L�[��L�L�[����������Ԃ��N�[���^�C�����^����������ԃ}�b�N�X�̎�
		{
			cooltime = 0;
			--dcount;
			Speed = 8;
			Info.Color = Palette::Aqua;
			avoid = 1;

		}
		else if (dodge == 1 && Input::KeyC.pressed&&dcount != 0 && cooltime == 0)//������ړ��L�[��L�L�[����������Ԃŉ�𒆁@�����ŃN�[���^�C���[��
		{
			--dcount;
			avoid = 1;
			Info.Color = Palette::Aqua;
			Speed = 8;
		}
		else if (dodge == 1 && Input::KeyC.pressed&&dcount == 0 && cooltime == 0)//������ړ��L�[��L�L�[����������ԃN�[���^�C���[����������ԃ[���̎�
		{

			Speed = 3;
			Info.Color = Color(197, 78, 160);
			avoid = 0;
		}

		else if (dcount != 10 && cooltime != 60)//�ړ��L�[��L�L�[�𗣂�����
		{

			cooltime++;
			Speed = 3;
			Info.Color = Color(197, 78, 160);
			avoid = 0;

		}
		else//�ړ��L�[��L�L�[�𗣂�����ԃN�[���^�C�����^����������ԃ}�b�N�X�̎��@�����̏��
		{
			dcount = 10;
			Speed = 3;
			Info.Color = Color(197, 78, 160);
			avoid = 0;
		}

	}

};