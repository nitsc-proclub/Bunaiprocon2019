#pragma once
#define RIGHT true
#define LEFT false
#include"GameEvent.h"

enum Scene
{
	Title, Game, Result
};

Scene CurrentScene;

//���҃t���O�A�V�[����Result�ɂȂ����Ƃ��Ɋm��B(false:�� true:�E)
bool Winner;

GameEvent gEvent;