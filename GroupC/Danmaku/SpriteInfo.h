#pragma once

/// <summary>
/// スプライト固有の情報を保管する構造体です。
/// </summary>
struct SpriteInfo
{
public:
	double Width = 10;
	double Height = 10;
	double X = 0;
	double Y = 0;
	double Angle = 0;
	Color Color = Palette::Red;
	/*SpriteInfo& operator=(const SpriteInfo& other)
	{
		this->Width = other.Width;
		this->Height = other.Height;
		this->X = other.X;
		this->Y = other.Y;
		this->Angle = other.Angle;
		this->Color = s3d::Color(other.Color);

		return *this;
	}*/
};