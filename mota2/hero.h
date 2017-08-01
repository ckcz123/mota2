#pragma once

#include "npc.h"
class c_hero
{
public:
	const static int MAX_DAMAGE=99999999;

	c_hero();//构造函数
	void init();
	float nextX();//下一步的横坐标
	float nextY();//下一步的纵坐标
	bool canMove(int);//是否可以朝某个方向移动
	bool moveComplete();//移动是否完成
	void show();
	void printInfo();//输出勇士信息
	bool canBeat(c_monster);//能否打败怪物
	int getDamage(c_monster);//打败怪物普通伤害
	void save(FILE*);//存档
	void load(FILE*);//读档
	void load(c_hero* another);
	int getHP() { return hp; }
	int getAtk() { return atk; }
	int getDef() { return def; }
	void addAtk(int point) { atk += point; }
	void addDef(int point) { def += point; }
	void addHP(int point) { hp += 150 * point; }
	int getScore() { return 150 * (atk + def) + hp; }
	int dir[2][4];
private:
	int hp, atk, def;
	int x, y, move, face;

	hgeSprite* sprites[4][4];
};
