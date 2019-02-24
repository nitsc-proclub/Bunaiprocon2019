#include"SpriteManager.h"

void SpriteManager::DrawAll(double X, double Y, bool Rot180)
{
	OffsetX = X;
	OffsetY = Y;
	this->Rot180 = Rot180;
	for (Call_i = 0; Call_i < Sprites.size(); Call_i++)
	{
		std::shared_ptr<ISprite> sp = Sprites[Call_i];
		sp->Manager = this;
		sp->Draw();
	}
}

void SpriteManager::UpdateAll()
{
	Calling = true;
	for (Call_i = 0; Call_i < Sprites.size(); Call_i++)
	{
		std::shared_ptr<ISprite> sp = Sprites[Call_i];
		sp->Manager = this;
		if (!sp->IsInit)
		{
			sp->Start();
			sp->IsInit = true;
		}
		sp->Update();
		sp->Info.Angle = Fmod((360 + sp->Info.Angle), 360);
	}
	Calling = false;
}

void SpriteManager::DestroyMe()
{
	if (Calling)
	{
		RemoveAt(Call_i);
	}
}

void SpriteManager::Add(ISprite* sp)
{
	Sprites.push_back(std::shared_ptr<ISprite>(sp));
}

void SpriteManager::Clear()
{
	Sprites.clear();
}

void SpriteManager::RemoveAt(unsigned int index)
{
	Sprites.erase(Sprites.begin() + index);
	if (Calling)
	{
		Call_i--;
	}
}

std::shared_ptr<ISprite> SpriteManager::FindTag(const String Tag)
{
	for (int i = 0; i < Sprites.size(); i++)
	{
		std::shared_ptr<ISprite> sp = Sprites[i];
		if (sp->Tag == Tag)
		{
			return sp;
		}
	}
	Println(L"エラー(FindTag):指定したTagを持つスプライトが見つかりませんでした。");
	return nullptr;
}