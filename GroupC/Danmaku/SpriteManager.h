#pragma once
#include<Siv3D.hpp>
#include"ISprite.h"

class ISprite;

/// <summary>
///スプライトを管理するクラスです。
/// </summary>
class SpriteManager
{
public:
	SpriteManager(int width, int height)
	{
		Width = width;
		Height = height;
	}
	/// <summary>
	/// 管理しているスプライトすべてのDraw()を実行します
	/// </summary>
	/// <param name="X">X座標</param>
	/// <param name="Y">Y座標</param>
	/// <param name="Rot180">180度回転</param>
	virtual void DrawAll(double X, double Y, bool Rot180);
	/// <summary>
	/// 管理しているスプライトすべてのUpdate()を実行します
	/// </summary>
	virtual void UpdateAll();
	/// <summary>
	/// 自分自身のスプライトを管理から外します(スプライトのDraw(),Update()からの呼び出しに対して有効)
	/// </summary>
	virtual void DestroyMe();
	/// <summary>
	/// 管理するスプライトを追加します
	/// </summary>
	/// <param name="sp">スプライトの参照</param>
	virtual void Add(ISprite*);
	/// <summary>
	/// すべてのスプライトを管理から外します
	/// </summary>
	virtual void Clear();
	/// <summary>
	/// 指定した番号のスプライトを管理から外します
	/// </summary>
	/// <param name="index">スプライトの番号</param>
	void RemoveAt(unsigned int index);
	/// <summary>
	/// 指定したタグを持つスプライトを取得します
	/// </summary>
	/// <param name="tag">検索するタグ</param>
	/// <returns>スプライトの参照(見つからないときはnullptr)</returns>
	std::shared_ptr<ISprite> FindTag(const String Tag);

	Array<std::shared_ptr<ISprite>> Sprites;
	unsigned int Call_i;
	bool Calling = false;
	double Width, Height;
	double OffsetX, OffsetY;
	bool Rot180;
};