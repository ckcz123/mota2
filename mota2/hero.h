#pragma once

#include "npc.h"
class c_hero
{
public:
	const static int MAX_DAMAGE=99999999;

	c_hero();//���캯��
	void init();
	float nextX();//��һ���ĺ�����
	float nextY();//��һ����������
	bool canMove(int);//�Ƿ���Գ�ĳ�������ƶ�
	bool moveComplete();//�ƶ��Ƿ����
	void show();
	void printInfo();//�����ʿ��Ϣ
	bool canBeat(c_monster);//�ܷ��ܹ���
	int getDamage(c_monster);//��ܹ�����ͨ�˺�
	void save(FILE*);//�浵
	void load(FILE*);//����
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
