#pragma once
#include<Siv3D.hpp>

/// <summary>
/// プログレスバー
/// </summary>
class ProgressBar
{
public:
	Color BackColor = Color(L"#dddddd");
	Color BarColor = Color(L"#4b85e5");
	int Width = 200;
	int Height = 20;
	int Value;
	int Max;
	/// <summary>
	/// プログレスバーのコンストラクター
	/// </summary>
	/// <param name="val">0~Maxの値</param>
	/// <param name="max">最大値</param>
	ProgressBar(int val, int max)
	{
		Value = val; Max = max;
	}
	/// <summary>
	/// プログレスバーのコンストラクター
	/// </summary>
	/// <param name="val">0~Maxの値</param>
	/// <param name="max">最大値</param>
	/// <param name="width">横幅</param>
	/// <param name="height">縦幅</param>
	ProgressBar(int val, int max, int width, int height)
	{
		Value = val; Max = max; Width = width; Height = height;
	}
	/// <summary>
	/// プログレスバーのコンストラクター
	/// </summary>
	/// <param name="val">0~Maxの値</param>
	/// <param name="max">最大値</param>
	/// <param name="width">横幅</param>
	/// <param name="height">縦幅</param>
	/// <param name="backcol">背景色</param>
	/// <param name="barcol">バーの色</param>
	ProgressBar(int val, int max, int width, int height,Color& backcol,Color& barcol)
	{
		Value = val; Max = max; Width = width; Height = height; BackColor = backcol; BarColor = barcol;
	}
	/// <summary>
	/// プログレスバーの描画
	/// </summary>
	/// <param name="x">左上のX座標</param>
	/// <param name="y">左上のY座標</param>
	void Draw(int x, int y)
	{
		//背景
		Rect(x,y,Width, Height).draw(BackColor);
		//バー
		Rect(x,y,Width*Value/Max, Height).draw(BarColor);
	}
};