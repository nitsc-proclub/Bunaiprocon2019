#pragma once
#include"SpriteCore.h"

class ImageView : public ISpriteView
{
private:
	Texture texture;
public:
	double HomeX = 0;
	double HomeY = 0;
	double HomeRot = 0;
	ImageView(String path,bool useAlpha,double polyLv)
	{
		if (FileSystem::Exists(path))
		{
			Image img(path);
			basePolygon = Imaging::FindExternalContour(img, useAlpha);
			if (polyLv > 0)
			{
				basePolygon = basePolygon.simplified(polyLv);
			}
			genePolygon = basePolygon.clone();
			texture = Texture(img);
		}
		else
		{
			Println(L"ImageView:‰æ‘œƒtƒ@ƒCƒ‹‚Ì“Ç‚İ‚İ‚É¸”s(" + path + L")");
		}
	}
	void Draw(SpriteInfo& info) override
	{
		genePolygon = basePolygon.clone();
		genePolygon = genePolygon.rotatedAt({HomeX,HomeY}, Radians(info.Angle + HomeRot));
		texture.rotateAt({ HomeX,HomeY },Radians(info.Angle + HomeRot)).draw(info.X, info.Y);
	}
};