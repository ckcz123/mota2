#pragma once
#include "monster.h"

class c_map_npc
{
public:
	void init(int);//��ʼ��
	void show(int, int);//��Ⱦ
	int getId();//����npc��id
	void changeState();//�ı�״̬
private:
	int id;
	int state;
	hgeSprite *npc[4];
};