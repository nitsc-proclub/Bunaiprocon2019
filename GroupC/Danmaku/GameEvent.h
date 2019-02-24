#pragma once
#include"SpriteCore.h"

class GameEvent
{
private:
	Array<String> EventQueue;
public:
	Array<String> GetEvents()
	{
		auto ret = EventQueue;
		EventQueue.clear();
		return ret;
	}
	void Launch(const String EventName)
	{
		EventQueue.push_back(EventName);
	}
};