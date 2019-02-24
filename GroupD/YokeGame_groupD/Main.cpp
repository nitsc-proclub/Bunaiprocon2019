
#include<Siv3D.hpp>
#include<HamFramework.hpp>

#include"Scene/Made.hpp"
#include"Scene/Title.hpp"
#include"Scene/SelectStage.hpp"
#include"Scene/Game.hpp"
#include"Scene/Result.hpp"
#include"Player.hpp"
#include"RecoveryItem.hpp"
#include"Enemy2.hpp"

void Main()
{
	Window::Resize(1280, 720);

	MyApp manager;
	manager.add<Made>(L"Made");
	manager.add<Title>(L"Title");
	manager.add<SelectStage>(L"SelectStage");
	manager.add<Game>(L"Game");
	manager.add<Result>(L"Result");

	TextureAsset::Register(L"Siv3D", L"Texture/Made_with_Siv3D.jpg" );
	TextureAsset::Register(L"Title", L"Texture/Title.jpg");
	FontAsset::Register(L"SystemFont", 40);
	FontAsset::Register(L"Result", 60);
	SoundAsset::Register(L"Game", L"Music/gamebgm.mp3");
	SoundAsset::Register(L"Title", L"Music/風の丘.mp3");

	while (System::Update())
	{
		if (!manager.updateAndDraw())
		{
			break;
		}
	}
}
