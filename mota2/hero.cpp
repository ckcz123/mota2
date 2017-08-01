#include "stdafx.h"

extern c_map_floor map_floor[50];
extern constants consts;

c_hero::c_hero()
{
	dir[0][0]=dir[0][3]=dir[1][1]=dir[1][2]=0;
	dir[0][1]=dir[1][3]=-1;
	dir[0][2]=dir[1][0]=1;
};
void c_hero::init()
{
	hp=1000;
	atk=10;
	def=10;
	x=6;
	y=12;
	face=3;
	move=0;
	for (int i=0; i<4; i++)
		for (int j=0; j<4; j++)
			sprites[i][j]=new hgeSprite(consts.ht_hero, 32*i, 33*j, 32, 33);
}
float c_hero::nextX()
{
	return x+dir[0][face];
}
float c_hero::nextY()
{
	return y+dir[1][face];
}
bool c_hero::canMove(int f)
{
	face=f;
	return map_floor[0].canMove(nextX(), nextY(), f);
}
void c_hero::show()
{
	sprites[move][face]->Render(x*32+8*move*dir[0][face]+consts.ScreenLeft, y*32+8*move*dir[1][face]);
}
bool c_hero::moveComplete()
{
	bool c=false;
	if (move==3)
	{
		c=true;
		x+=dir[0][face];
		y+=dir[1][face];
	}
	if (c)
	{
		char item=map_floor[0].getItem(x, y);
		if (item!=0&&consts.music)
			consts.hge->Effect_PlayEx(consts.he_GetItem, consts.volume);
		switch (item)
		{
		case 31: consts.setMsg(L"获得神秘六芒星！\n你可以支付任意点攻击或防御值，使\n全场怪兽攻防下降支付点数的一半。\n\n[X]键使用。"); break;
		default: break;
		}
		consts.step++;
	}
	move++;
	move%=4;
	return c;
}
void c_hero::printInfo()
{
	int py=16;
	consts.s_heart->Render(16, py);
	consts.hgef->printf(60, py, HGETEXT_LEFT, "%d", hp);
	py+=32;
	consts.s_sword1->Render(16, py);
	consts.hgef->printf(60, py, HGETEXT_LEFT, "%d", atk);
	py+=32;
	consts.s_shield1->Render(16, py);
	consts.hgef->printf(60, py, HGETEXT_LEFT, "%d", def);
}
bool c_hero::canBeat(c_monster monster) // 判断能否打败
{
	return hp>getDamage(monster);
}
int c_hero::getDamage(c_monster monster) // 打败怪物，返回hp
{
	int mon_def = monster.getDef(), mon_atk=monster.getAtk();
	if (atk <= mon_def) return MAX_DAMAGE;
	int hero_def = monster.getSpecial() == 1 ? 0 : def;
	if (hero_def >= mon_atk) return 0;
	return (monster.getHp() - 1) / (atk - mon_def) * (mon_atk - hero_def);
}
void c_hero::save(FILE* f)
{
	fprintf_s(f, "%d %d %d %d %d %d\n", hp, atk, def, x, y, face);
}
void c_hero::load(FILE* f)
{
	fscanf_s(f, "%d %d %d %d %d %d", &hp, &atk, &def, &x, &y, &face);
}
void c_hero::load(c_hero* another)
{
	hp = another->hp;
	atk = another->atk;
	def = another->def;
	x = another->x;
	y = another->y;
}