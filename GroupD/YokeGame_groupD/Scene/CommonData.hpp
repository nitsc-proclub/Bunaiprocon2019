#pragma once

#include<Siv3D.hpp>
#include<HamFramework.hpp>


struct GameData
{
	int Score;
};

using MyApp = SceneManager<String, GameData>;


