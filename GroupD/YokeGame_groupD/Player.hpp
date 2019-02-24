
#pragma once

#include"Scene/CommonData.hpp"

class Player
{
public:
	int game_difficulty_num;//�}���̓�Փx�ݒ�

	int play_area[4] = { 107, 790, 17, 700 }; //�ړ��\�͈͂̍��W�@0,1 == ���[,�E�[�@2,3 == ��[,���[
	Rect player_collider;//�v���C���[�̓����蔻��
	double player_speed = 1; //�O�I�v���ɂ���Ď��@�̑��x��ς������Ƃ��͂�����������Ă�������

	int player_hp = 100;
	double player_hp_max = 100;

	int muteki_time = 60;
	bool muteki = false;
	

	//�Q�[���̃V�[���̃N���X��init�̎��Ɏ��s���Ăق����֐�
	void create_HP_bar(int pos_x, int pos_y, int width, int height)
	{
		//�n�_�̍��W
		hp_pos_x = (double)pos_x;
		hp_pos_y = (double)pos_y;

		//���A����
		hp_bar_width = (double)width;
		hp_bar_height = (double)height;

		hp_base = Rect(pos_x, pos_y, width, height);
		green_hp = Rect(pos_x, pos_y, width, height);
	}


	//�_���[�W���󂯂�Ƃ��Ɏ��s
	void damage_hp(int damage)
	{
		player_hp -= damage;//hp�����炷
		if (damage > 0) muteki = true, muteki_time = 60;
		if (player_hp < 0) player_hp = 0;
		if (player_hp > 100) player_hp = 100;

		//������HP�ɍ��킹�ėΐF�̎l�p���Đݒ�
		damage_temp = hp_bar_width * (player_hp / player_hp_max);

		green_hp = Rect(hp_pos_x, hp_pos_y, damage_temp, hp_bar_height);
	}


	void init()
	{
		//���@�̏����ʒu
		pos_x = (play_area[0] + play_area[1]) / 2;
		pos_y = (play_area[2] + play_area[3]) / 2;
		player_collider = Rect(pos_x, pos_y, 14,13);


	}


	void update()
	{
		move_dist = base_dist * player_speed;//�W���̑��x * �O�I�v���ɂ��{���ϓ�

		//���͎󂯎��
		if (Input::KeyUp.pressed) pos_y -= move_dist;
		if (Input::KeyDown.pressed) pos_y += move_dist;
		if (Input::KeyLeft.pressed) pos_x -= move_dist;
		if (Input::KeyRight.pressed) pos_x += move_dist;

		//�͈͊O�ɏo�����ɂȂ������̏���
		if (pos_x < play_area[0]) pos_x = play_area[0];
		if (pos_x > play_area[1]) pos_x = play_area[1];
		if (pos_y < play_area[2]) pos_y = play_area[2];
		if (pos_y > play_area[3]) pos_y = play_area[3];

		player_collider = Rect(pos_x - 6, pos_y - 7, 14, 13);//��14,����13�̓e�N�X�`���̑傫��

		if (muteki) muteki_time--;
		if (muteki_time < 1) muteki = false, muteki_time = 0;
	}


	void draw() const
	{
		player_collider.draw(Color(0, 0, 0, 0));//�����܂œ����蔻��Ȃ̂œ����ɂ�����
		player_image.draw(pos_x - 6, pos_y - 7);

		if (muteki_time < 50 && muteki_time > 42) player_collider.draw(Color(255, 255, 255, 255));
		if (muteki_time < 30 && muteki_time > 22) player_collider.draw(Color(255, 255, 255, 255));
		if (muteki_time < 10 && muteki_time > 2) player_collider.draw(Color(255, 255, 255, 255));

		if(player_hp >= 0) green_hp.draw(Color(60, 255, 60));//hp��0�ɂȂ��Ă��ΐF�̐����`�悳��Ă��܂����߁A�����t��

		hp_base.drawFrame(0,5,Color(255,255,255));
		hp_base.drawFrame(1,0, Color(60,60,60));
		

		hp_text(L"HP: ", player_hp).draw(hp_pos_x, hp_pos_y - 40);//40�́Afont�̑傫�� * 2
	}


private:
	double pos_x, pos_y, move_dist;
	double base_dist = 5;
	double hp_pos_x, hp_pos_y, hp_bar_width, hp_bar_height, damage_temp;//damage_temp�̓_���[�W�����̎��Ɏg���܂��B

	Rect hp_base;//HP�o�[�̘g
	Rect green_hp;//�ΐF�̕���

	Font hp_text = Font(20);

	Texture player_image = Texture(L"Texture/player1.png");//���\�[�X�t�@�C���ɔz�u����Ƃ��܂������Ȃ������̂ő��΃p�X����

};


