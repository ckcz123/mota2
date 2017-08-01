#pragma once
#include "hero.h"

class c_map_door
{
public:
	void init(int);//初始化
	void show(int, int);//渲染
	bool open();//开某个普通门
	void setOpened(bool on=true) { opened=on; } //打开一个特殊门
	bool isOpened() { return opened; }//判断一个门是否被打开
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
	void init(hgeSprite*, hgeSprite*, int, int);//初始化
	void show(GfxFont*, int, int);//渲染
	void animation() { monster.changeState(); npc.changeState(); }//npc状态改变
	void printMonsterInfo() { monster.printInfo(); } //输出怪物信息
	bool canMove(int);//判断该点是否可移动
	bool canOpen() { return door.isOpened(); }//判断一个门能否打开
	void setOpened() { door.setOpened(); }//打开一个门
	bool openSpecial();
	int getItemID();//获取该点的物品编号
	void distroy() { item=NULL; } //获取该点物品
	int getNpcID() { return npc.getId(); }//返回npc的id
	int getNpcVisit() { return npc.getVisit(); } //返回npc的访问次数
	void visitNpc() { npc.setVisit(npc.getVisit()+1); } //读入npc的访问次数
	void changeLight();
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
	void init(int, int[30][30]);//初始化
	void show();//渲染
	void animation();//状态改变
	void printMonsterInfo(int, int);//输出怪物信息
	bool canMove(int, int, int);//判断该地图的某点是否可移动
	int getItem(int, int);//获取地图某点的物品
	void save(FILE*);//存档
	void load(FILE*);//读档
	c_map_point* getinfo(int x, int y) { return &info[x][y]; }
private:
	int id;//楼层编号
	c_map_point info[30][30];//每点信息
};