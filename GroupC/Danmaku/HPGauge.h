#pragma once
#include"ProgressBar.h"

class HPGauge : public ProgressBar
{
public:
	HPGauge(int val, int max) : ProgressBar(val,max)
	{
		
	}

	Color Warn = Palette::Red;//0~20%
	Color Attention = Palette::Yellow;//20~50%
	Color Nomal = Palette::Green;//50~100%

	void Draw(int x, int y)
	{
		double per = (double)Value / Max;
		if (per <= 0.2)
		{
			BarColor = Warn;
		}
		else if (per <= 0.5)
		{
			BarColor = Attention;
		}
		else
		{
			BarColor = Nomal;
		}
		//”wŒi
		Rect(x, y, Width, Height).draw(BackColor);
		//ƒo[
		Rect(x, y, Width*Value / Max, Height).draw(BarColor);
	}
};