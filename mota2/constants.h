#pragma once
#include "map.h"
#include <string>
#include <vector>

struct savedata
{
	int hp, atk, def;
	void init(int _hp, int _atk, int _def) { hp=_hp; atk=_atk; def=_def; }
};

class constants
{
public:
	static const int MESSAGE_NONE=0;
	static const int MESSAGE_RESTART=1;
	static const int MESSAGE_SAVE=2;
	static const int MESSAGE_LOAD=3;
	static const int MESSAGE_WIN=4;
	static const int MESSAGE_ITEM=5;
	static const int MESSAGE_RANK=6;
	static const int MESSAGE_HINT=7;
	static const int MESSAGE_POINT=8;

	constants();
	void init();
	void loadResources();
	void destroy();
	void setMsg(const wchar_t* [50]);
	void setMsg(const wchar_t*);
	bool isFree() { return !moving && !opening && msg==MESSAGE_NONE; }
	void goOn(c_hero*, c_map_floor*, float);
	void save(FILE*);
	void load(FILE*);
	void load(constants* another);
	void printInfo();

	int msg;
	vector<wstring> hint;
	int nowcnt;
	long lasttime;

	float playtime;
	int step;

	bool book, item, moving, music, opening;
	int map_height, map_width, volume, bgmvolume, ScreenLeft;

	// ʹ�õ���
	int item_choose, item_point;

	// ��ǰ����
	int curr_point, total_point;

	savedata sd[100];
	int wanttosave;

	// ���ڿ�����
	c_map_door *map_openingdoor;

	// ���ڶԻ���npc
	c_map_npc *map_npc;

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