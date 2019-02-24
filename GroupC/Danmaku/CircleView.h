#pragma once
#include"SpriteCore.h"

class CircleView : public ISpriteView
{
public:
	CircleView()
	{
		basePolygon = Geometry2D::CreateNgon(15,1);
		genePolygon = basePolygon.clone();
	}
	void Draw(SpriteInfo& info) override
	{
		genePolygon = basePolygon.clone();
		genePolygon = genePolygon.scaled(info.Width, info.Height);
		genePolygon.draw(info.X, info.Y, info.Color);
	}
};