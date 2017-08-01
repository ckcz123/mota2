#pragma once
#include "monster.h"

class c_map_npc
{
public:
	void init(int);//初始化
	void show(int, int);//渲染
	int getId();//返回npc的id
	void changeState();//改变状态
private:
	int id;
	int state;
	hgeSprite *npc[4];
};