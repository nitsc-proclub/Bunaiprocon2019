#include<Siv3D.hpp>
#include"Sprites.h"
#include"ProgressBar.h"
#include"GameEvent.h"

SpriteManager danmaku(640, 480 * 2);

int WindowWidth = 640 * 2 + 2;
int WindowHeight = 480;

const String GameTitle = L"Taisengata-Danmaku-Ge-Mu";

//デバッグ用
class Debug
{
public:
	GUI gui;
	Debug()
	{
		gui = GUI(GUIStyle::Default);
		gui.setTitle(L"Debug");
		gui.addln(L"fps", GUIText::Create(L"FPS:"));
		gui.add(L"hr", GUIHorizontalLine::Create(1));
		gui.horizontalLine(L"hr").style.color = Color(127);
		gui.addln(L"spcnt", GUIText::Create(L"スプライトの数:"));

		gui.addln(L"LR", GUIRadioButton::Create({ L"Left", L"Right" },0));
		gui.add(L"doba", GUIButton::Create(L"ﾄﾞﾊﾞｧ"));
		gui.add(L"block", GUIButton::Create(L"ブロック"));
	}
	void Update()
	{
		gui.text(L"fps").text = Format(L"FPS: ",Profiler::FPS());
		gui.text(L"spcnt").text = Format(L"スプライトの数: ", danmaku.Sprites.size());
		if (gui.button(L"doba").pushed)
		{
			if (gui.radioButton(L"LR").checked(0))
			{
				gEvent.Launch(L"CounterLeft");
			}
			if (gui.radioButton(L"LR").checked(1))
			{
				gEvent.Launch(L"CounterRight");
			}
		}
		if (gui.button(L"block").pushed)
		{
			if (gui.radioButton(L"LR").checked(0))
			{
				gEvent.Launch(L"BlockLeft");
			}
			if (gui.radioButton(L"LR").checked(1))
			{
				gEvent.Launch(L"BlockRight");
			}
		}
	}
};

void Main()
{
	SpriteViewsLoad();

	Window::Resize(WindowWidth, WindowHeight);
	Window::SetTitle(GameTitle);

	Rect PartLine(640, 0, 2, 480);
	Font Font_Default;
	Font Font_Title(50, Typeface::Default, FontStyle::Italic);
	Font_Title.changeOutlineStyle(TextOutlineStyle(Palette::Gray, Palette::White, 1.0));
	Font Font_WinLose(50, Typeface::Heavy, FontStyle::Bold);

	CurrentScene = Scene::Title;

	Debug debug;

	RasterizerState rasterizer = RasterizerState::Default2D;
	rasterizer.scissorEnable = true;

	Graphics2D::SetRasterizerState(rasterizer);

	std::shared_ptr<ISprite> left = nullptr;
	std::shared_ptr<ISprite> right = nullptr;

	while (System::Update())
	{
		switch (CurrentScene)
		{
		case Scene::Title:
			Graphics2D::SetScissorRect(Rect(0, 0, WindowWidth, WindowHeight));
			Font_Title(GameTitle).drawCenter(WindowWidth / 2, WindowHeight / 2);
			Font_Default(L"Press [Enter] to start").drawCenter(WindowWidth/2,WindowHeight/2+50);
			if (Input::KeyEnter.released)
			{
				CurrentScene = Scene::Game;

				danmaku.Add(new LeftPlayer());
				danmaku.Add(new RightPlayer());
				left = danmaku.FindTag(L"LeftPlayer");
				right = danmaku.FindTag(L"RightPlayer");
			}
			break;
		case Scene::Game:
			//座標の更新、計算処理
			danmaku.UpdateAll();
			//イベント
			for (String EvName : gEvent.GetEvents())
			{
				if (EvName == L"CounterLeft")
				{
					for (int i = 0; i <= 20; i++)
					{
						danmaku.Add(new Bullets_Counter_Left());
					}
				}
				else if (EvName == L"CounterRight")
				{
					for (int i = 0; i <= 20; i++)
					{
						danmaku.Add(new Bullets_Counter_Right());
					}
				}
				else if (EvName == L"BlockLeft")
				{
					for (int i = 0; i <= 15; i++)
					{
						danmaku.Add(new BlockSprite(left,0, 480, 639, 959));
					}
				}
				else if (EvName == L"BlockRight")
				{
					for (int i = 0; i <= 15; i++)
					{
						danmaku.Add(new BlockSprite(right,0, 0, 639, 479));
					}
				}
				else
				{
					Println(Format(L"不明なイベント名:", EvName));
				}
			}
		case Scene::Result:
			//描画(左)
			Graphics2D::SetScissorRect(Rect(0, 0, 640, 480));
			danmaku.DrawAll(0, -480, false);
			//描画(右)
			Graphics2D::SetScissorRect(Rect(642, 0, 640, 480));
			danmaku.DrawAll(642, -480, true);
			//描画(その他)
			Graphics2D::SetScissorRect(Rect(0, 0, WindowWidth, WindowHeight));
			PartLine.draw();//分割線
			if (CurrentScene == Scene::Result)
			{
				if (Winner == LEFT)
				{
					Font_WinLose(L"WIN").drawCenter(320, 240, Palette::Red);
					Font_WinLose(L"LOSE").drawCenter(642 + 320, 240, Palette::Blue);
				}
				else
				{
					Font_WinLose(L"LOSE").drawCenter(320, 240, Palette::Blue);
					Font_WinLose(L"WIN").drawCenter(642 + 320, 240, Palette::Red);
				}
				Font_Default(L"[Enterキー]で再戦").drawCenter(WindowWidth/2, WindowHeight/2+100);
				if (Input::KeyEnter.released)
				{
					CurrentScene = Scene::Game;
					danmaku.Clear();
					danmaku.Add(new LeftPlayer());
					danmaku.Add(new RightPlayer());
					left = danmaku.FindTag(L"LeftPlayer");
					right = danmaku.FindTag(L"RightPlayer");
				}
			}
			break;
		}
		debug.Update();
	}
}