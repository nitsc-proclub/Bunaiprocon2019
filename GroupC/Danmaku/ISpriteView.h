#pragma once

/// <summary>
///スプライトの描画と当たり判定を行うインターフェースです。
/// </summary>
class ISpriteView
{
public:
	Polygon basePolygon;
	Polygon genePolygon;
	
	///<summary>
	///描画を行います
	///</summary>
	virtual void Draw(SpriteInfo&) {}
};