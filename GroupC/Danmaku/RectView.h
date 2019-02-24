#pragma once
#include"SpriteCore.h"

class RectView : public ISpriteView
{
public:
	RectView()
	{
		basePolygon = Rect(-1, -1, 2, 2).asPolygon();
		genePolygon = basePolygon.clone();
	}
	void Draw(SpriteInfo& info) override
	{
		genePolygon = basePolygon.clone();
		genePolygon = genePolygon.scaled(info.Width, info.Height);
		genePolygon = genePolygon.rotated(Radians(info.Angle));
		genePolygon.draw(info.X, info.Y, info.Color);
	}
};