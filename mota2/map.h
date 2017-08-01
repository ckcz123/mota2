#pragma once
#include "hero.h"

class c_map_door
{
public:
	void init(int);//初始化
	void show(int, int);//渲染
	bool open();//开某个普通门
	bool isOpened() { return opened; }//判断一个门是否被打开
	void setOpen() { opened = true; }
	int getType() { return type; } //门的类型
private:
	int type;
	bool opened;
	int state;
	hgeSprite *door[4];
};

class c_map_point
{
public:
	void init(int, int, int, int, int);//初始化
	void show(GfxFont*, int, int);//渲染
	void animation() { monster.changeState(); npc.changeState(); }//npc状态改变
	void printMonsterInfo() { monster.printInfo(); } //输出怪物信息
	bool canMove(int);//判断该点是否可移动
	bool canOpen() { return door.isOpened(); }//判断一个门能否打开
	bool openSpecial();
	int getItem() { return item; }
	void distroy() { item = 0; npc.init(0); door.init(0); monster.init(0); }
	void save(FILE*);//存档
	void load(FILE*);//读档
private:
	int type;//地面类型（地 OR 墙）
	int item;//道具类型
	c_monster monster;//敌人类型
	c_map_door door;//门类型
	c_map_npc npc;// npc类型
};

class c_map_floor
{
public:
	void init();
	void init(const int[30][30]);//初始化
	void show();//渲染
	void animation();//状态改变
	void printMonsterInfo(int, int);//输出怪物信息
	bool canMove(int, int, int);//判断该地图的某点是否可移动
	int getItem(int, int);//获取地图某点的物品
	void save(FILE*);//存档
	void load(FILE*);//读档
	c_map_point* getinfo(int x, int y) { return &info[x][y]; }
private:
	c_map_point info[30][30];//每点信息
};