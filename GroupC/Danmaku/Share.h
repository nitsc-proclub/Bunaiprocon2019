#pragma once
#define RIGHT true
#define LEFT false
#include"GameEvent.h"

enum Scene
{
	Title, Game, Result
};

Scene CurrentScene;

//勝者フラグ、シーンがResultになったときに確定。(false:左 true:右)
bool Winner;

GameEvent gEvent;