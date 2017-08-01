#pragma once
#include "hero.h"

class c_map_door
{
public:
	void init(int);//��ʼ��
	void show(int, int);//��Ⱦ
	bool open();//��ĳ����ͨ��
	bool isOpened() { return opened; }//�ж�һ�����Ƿ񱻴�
	void setOpen() { opened = true; }
	int getType() { return type; } //�ŵ�����
private:
	int type;
	bool opened;
	int state;
	hgeSprite *door[4];
};

class c_map_point
{
public:
	void init(int, int, int, int, int);//��ʼ��
	void show(GfxFont*, int, int);//��Ⱦ
	void animation() { monster.changeState(); npc.changeState(); }//npc״̬�ı�
	void printMonsterInfo() { monster.printInfo(); } //���������Ϣ
	bool canMove(int);//�жϸõ��Ƿ���ƶ�
	bool canOpen() { return door.isOpened(); }//�ж�һ�����ܷ��
	bool openSpecial();
	int getItem() { return item; }
	void distroy() { item = 0; npc.init(0); door.init(0); monster.init(0); }
	void save(FILE*);//�浵
	void load(FILE*);//����
private:
	int type;//�������ͣ��� OR ǽ��
	int item;//��������
	c_monster monster;//��������
	c_map_door door;//������
	c_map_npc npc;// npc����
};

class c_map_floor
{
public:
	void init();
	void init(const int[30][30]);//��ʼ��
	void show();//��Ⱦ
	void animation();//״̬�ı�
	void printMonsterInfo(int, int);//���������Ϣ
	bool canMove(int, int, int);//�жϸõ�ͼ��ĳ���Ƿ���ƶ�
	int getItem(int, int);//��ȡ��ͼĳ�����Ʒ
	void save(FILE*);//�浵
	void load(FILE*);//����
	c_map_point* getinfo(int x, int y) { return &info[x][y]; }
private:
	c_map_point info[30][30];//ÿ����Ϣ
};