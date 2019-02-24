#pragma once
#include"SpriteManager.h"
#include"SpriteInfo.h"
#include"ISpriteView.h"

class SpriteManager;

/// <summary>
///スプライト本体のインターフェースです。
/// </summary>
class ISprite
{
public:
	enum SpriteEvent
	{
		Damage
	};

	ISprite() {}

	ISprite& operator=(const ISprite& other)
	{
		this->View = other.View;
		this->Info = other.Info;
		this->IsInit = other.IsInit;

		return *this;
	}

	/// <summary>
	/// <para>スプライトの描画を行います</para>
	/// <para>(デフォルトはViewのDraw()を呼び出します)</para>
	/// </summary>
	virtual void Draw();
	
	/// <summary>
	/// 初めてUpdateを呼ぶ直前に呼ばれる関数
	/// </summary>
	virtual void Start();

	/// <summary>
	/// 毎フレームに呼ばれる関数
	/// </summary>
	virtual void Update();

	/// <summary>
	/// スプライトのイベントハンドラ
	/// </summary>
	/// <param name="e">イベントの内容</param>
	/// <param name="e">イベントの内容(数値)</param>
	virtual void DoEvent(const SpriteEvent e,const int value);

	/// <summary>
	/// スプライトとの当たり判定を行います
	/// </summary>
	/// <param name="sp">判定するスプライト</param>
	/// <returns>当たっていればtrue、当たっていなければfalse</returns>
	virtual bool IsHit(const std::shared_ptr<ISprite>);

	/// <summary>
	/// スプライトとの当たり判定を行います
	/// </summary>
	/// <param name="sp">スプライトの管理番号</param>
	/// <returns>当たっていればtrue、当たっていなければfalse</returns>
	virtual bool IsHit(unsigned int);

	/// <summary>
	/// 当たっているスプライトを1つ返します
	/// </summary>
	/// <returns>スプライトの管理番号</returns>
	virtual std::shared_ptr<ISprite> GetHitSp();
	/// <summary>
	/// 条件に該当し、当たっているスプライトを1つ返します
	/// </summary>
	/// <param name="tag">絞り込む条件</param>
	/// <returns>スプライトの管理番号</returns>
	virtual std::shared_ptr<ISprite> GetHitSp(const String tag);
	
	bool IsInWindow();
	bool IsInWindow(int x, int y);

	int HitArea;
	ISpriteView* View = nullptr;
	SpriteInfo Info = SpriteInfo();
	SpriteManager* Manager = nullptr;
	String Tag;
	bool IsInit = false;
};