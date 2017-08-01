#pragma once
#include <hge.h>
#include <hgefont.h>
#include <hgesprite.h>
#include "gfxfont.h"
using namespace std;

class c_monster
{
public:
	void init(int);//��ʼ��
	void show(GfxFont*, int, int);//��Ⱦ
	void printInfo();//�����Ϣ
	void changeState();//���ﶯ��
	int getId() { return id; }
	int getHp() { return hp; }
	int getAtk();
	int getDef();
	int getMoney() { return money; }
	int getSpecial() { return special; }
private:
	wchar_t name[30];
	int id, hp, atk, def, money, special;
	int state, position;
	hgeSprite *monster[4];
};