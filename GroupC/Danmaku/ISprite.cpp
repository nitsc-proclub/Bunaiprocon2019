#include"ISprite.h"
void ISprite::Draw()
{
	SpriteInfo buffinfo;
	buffinfo = Info;
	if (Manager->Rot180)
	{
		buffinfo.Angle = -buffinfo.Angle;
		buffinfo.X = -buffinfo.X + Manager->Width;
		buffinfo.Y = -buffinfo.Y + Manager->Height;
	}
	buffinfo.X += Manager->OffsetX;
	buffinfo.Y += Manager->OffsetY;
	View->Draw(buffinfo);
}
void ISprite::Start()
{
}
void ISprite::Update()
{
}
void ISprite::DoEvent(const SpriteEvent Mess,const int val)
{
}
bool ISprite::IsHit(const std::shared_ptr<ISprite> sp)
{
	if (sp->View == nullptr || View == nullptr)
	{
		Println(L"エラー(IsHit):当たり判定対象がnullptrです。");
		return false;
	}
	Polygon TargetMov = sp->View->genePolygon.movedBy(sp->Info.X, sp->Info.Y);
	Polygon MineMov = this->View->genePolygon.movedBy(this->Info.X, this->Info.Y);
	return TargetMov.intersects(MineMov);
}
bool ISprite::IsHit(unsigned int num)
{
	return IsHit(Manager->Sprites[num]);
}
std::shared_ptr<ISprite> ISprite::GetHitSp()
{
	for (unsigned int n=0;n<Manager->Sprites.size();n++)
	{
		if (Manager->Call_i != n)
		{
			auto sp = Manager->Sprites[n];
			if (IsHit(sp))
			{
				return sp;
			}
		}
	}
	return nullptr;
}
std::shared_ptr<ISprite> ISprite::GetHitSp(const String tag)
{
	for (unsigned int n = 0; n < Manager->Sprites.size(); n++)
	{
		if (Manager->Call_i != n)
		{
			auto sp = Manager->Sprites[n];
			if (sp->Tag == tag && IsHit(sp))
			{
				return sp;
			}
		}
	}
	return nullptr;
}
bool ISprite::IsInWindow()
{
	return IsInWindow(Info.X, Info.Y);
}
bool ISprite::IsInWindow(int x, int y)
{
	//Siv3Dオリジナルのint32は聞いてないぞ!
	return (0 <= x && x < Manager->Width) && (0 <= y && y < Manager->Height);
}