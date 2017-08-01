#pragma once
#include "map.h"
#include <string>
#include <vector>

struct savedata
{
	int hp, atk, def;
	void init(int _hp, int _atk, int _def, int _nowf) { hp=_hp; atk=_atk; def=_def; }
};

class constants
{
public:
	static const int MESSAGE_NONE=0;
	static const int MESSAGE_QUIT=1;
	static const int MESSAGE_RESTART=2;
	static const int MESSAGE_SAVE=3;
	static const int MESSAGE_LOAD=4;
	static const int MESSAGE_WIN=5;
	static const int MESSAGE_NPC=6;
	static const int MESSAGE_ITEM=7;
	static const int MESSAGE_RANK=8;
	static const int MESSAGE_HINT=9;

	constants();
	void init();
	void loadResources();
	void destroy();
	void setMsg(const wchar_t* [50]);
	void setMsg(const wchar_t*);
	bool isFree() { return !moving && msg==MESSAGE_NONE; }
	void goOn(c_hero*, c_map_floor*, float);
	void save(FILE*);
	void load(FILE*);
	void printInfo();

	int msg;
	vector<wstring> hint;
	int nowcnt;
	long lasttime;

	float playtime;
	int step;

	bool book, item, moving, music;
	int map_height, map_width, volume, bgmvolume, ScreenLeft;

	savedata sd[100];
	int wanttosave;

	// ����ս���Ĺ���
	c_monster *monster_battling;
	// ����ս�������ԭʼ����ֵ
	int monster_life;

	// HGE
	HGE *hge;

	//��������
	HTEXTURE ht_map, ht_icon, ht_hero, ht_monster, ht_skin, ht_npc, ht_special;

	//������Ч
	HEFFECT he_GetItem, he_OpenDoor, he_Attack, he_Music;
	HCHANNEL hc_Music;

	//����ͼ��
	hgeSprite *s_ground, *s_wall;
	hgeSprite *s_coin, *s_floor;
	hgeSprite *s_sword1, *s_shield1;
	hgeSprite *s_enemyinfo, *s_heart, *s_expr, *s_damage, *s_time, *s_step;
	hgeSprite *s_specialdoor;

	// ����
	hgeFont *hgef;

	// ��������
	float time_move, time_open, time_animation, time_battle, time_floor;
	// �������Ƿ�ʼ
	bool isMyTurn, beatStarted;

};