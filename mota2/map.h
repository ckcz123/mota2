#pragma once
#include "hero.h"

class c_map_door
{
public:
	void init(int);//��ʼ��
	void show(int, int);//��Ⱦ
	bool open();//��ĳ����ͨ��
	void setOpened(bool on=true) { opened=on; } //��һ��������
	bool isOpened() { return opened; }//�ж�һ�����Ƿ񱻴�
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
	void init(hgeSprite*, hgeSprite*, int, int);//��ʼ��
	void show(GfxFont*, int, int);//��Ⱦ
	void animation() { monster.changeState(); npc.changeState(); }//npc״̬�ı�
	void printMonsterInfo() { monster.printInfo(); } //���������Ϣ
	bool canMove(int);//�жϸõ��Ƿ���ƶ�
	bool canOpen() { return door.isOpened(); }//�ж�һ�����ܷ��
	void setOpened() { door.setOpened(); }//��һ����
	bool openSpecial();
	int getItemID();//��ȡ�õ����Ʒ���
	void distroy() { item=NULL; } //��ȡ�õ���Ʒ
	int getNpcID() { return npc.getId(); }//����npc��id
	int getNpcVisit() { return npc.getVisit(); } //����npc�ķ��ʴ���
	void visitNpc() { npc.setVisit(npc.getVisit()+1); } //����npc�ķ��ʴ���
	void changeLight();
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
	void init(int, int[30][30]);//��ʼ��
	void show();//��Ⱦ
	void animation();//״̬�ı�
	void printMonsterInfo(int, int);//���������Ϣ
	bool canMove(int, int, int);//�жϸõ�ͼ��ĳ���Ƿ���ƶ�
	int getItem(int, int);//��ȡ��ͼĳ�����Ʒ
	void save(FILE*);//�浵
	void load(FILE*);//����
	c_map_point* getinfo(int x, int y) { return &info[x][y]; }
private:
	int id;//¥����
	c_map_point info[30][30];//ÿ����Ϣ
};