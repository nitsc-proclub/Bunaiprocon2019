#pragma once

#include "Scene/CommonData.hpp"


class RecoveryItem
{
public :
	bool item_alive;//��ʓ��Ɉ������������������

	int event_lock;//���t���[���̊ԓ������Ă��邱�ƂɂȂ��Ă��܂������߁A�΍�

	Rect item_collider;//�����蔻��Ɏg��

	void item_spawn()
	{
		pos_x = Random(100, 780);//�A�C�e���������Ă�����W�������_���ɐݒ�
		pos_y = 10;//�o�����鏉���ʒu
		item_alive = true;
		event_lock = 0;
	}

	void init()
	{
		item_alive = false;
		fall_speed = 3;
		item_image = Texture(L"Texture/RecoveryItem.png");//��ɂ���ă��\�[�X�t�@�C���ɔz�u�����ɑ��΃p�X�ł��肢���܂��B
	}


	void update()
	{
		//�A�C�e������ʓ��ɂ��鎞�Ɏ��s
		if (item_alive)
		{
			pos_y += fall_speed;
			item_collider = Rect(pos_x, pos_y, 20, 20);
		}

		//�g�͈͓̔��ɏo���Ƃ��ɏ������߂̃t���O
		if (713 < pos_y)
		{
			item_alive = false;
		}
	}


	void draw() const
	{
		if (item_alive)
		{
			item_collider.draw(Color(0,0,0,0));//��ɂ���ē���
			item_image.draw(pos_x, pos_y);//�����蔻��ɏd�Ȃ�悤�Ƀe�N�X�`����`��
		}
	}
	

private :
	int pos_x, pos_y, fall_speed;

	Texture item_image;
};