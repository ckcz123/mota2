#include "stdafx.h"

extern c_hero hero;
extern constants consts;

void c_monster::init(int t)
{
	id=t;
	state=0;
	switch (t-50)
	{
	// monsters
	case 1:wcscpy_s(name, L"绿色史莱姆"); position = 0; hp = 100; atk = 14; def = 3; money = 3; special = 0; break;
	case 2:wcscpy_s(name, L"红色史莱姆"); position = 1; hp = 100; atk = 18; def = 7; money = 5; special = 0; break;
	case 3:wcscpy_s(name, L"小蝙蝠"); position = 4; hp = 100; atk = 20; def = 4; money = 6; special = 0; break;
	case 4:wcscpy_s(name, L"青头怪"); position = 2; hp = 124; atk = 24; def = 8; money = 9; special = 0; break;
	case 5:wcscpy_s(name, L"骷髅人"); position = 12; hp = 137; atk = 27; def = 11; money = 11; special = 0; break;
	case 6:wcscpy_s(name, L"初级法师"); position = 8; hp = 144; atk = 35; def = 5; money = 15; special = 1; break;
	case 7:wcscpy_s(name, L"骷髅士兵"); position = 13; hp = 156; atk = 48; def = 13; money = 17; special = 0; break;
	case 8:wcscpy_s(name, L"石头人"); position = 18; hp = 90; atk = 19; def = 19; money = 19; special = 2; break;
	case 9:wcscpy_s(name, L"史莱姆王"); position = 3; hp = 171; atk = 60; def = 5; money = 19; special = 0; break;
	case 10:wcscpy_s(name, L"初级卫兵"); position = 20; hp = 187; atk = 25; def = 60; money = 23; special = 0; break;
	case 11:wcscpy_s(name, L"大蝙蝠"); position = 5; hp = 195; atk = 80; def = 5; money = 27; special = 0; break;
	case 12:wcscpy_s(name, L"魔法警卫"); position = 29; hp = 200; atk = 130; def = 0; money = 30; special = 0; break;
	case 13:wcscpy_s(name, L"骷髅队长"); position = 14; hp = 212; atk = 40; def = 40; money = 34; special = 0; break;
	case 14:wcscpy_s(name, L"兽面人"); position = 16; hp = 286; atk = 80; def = 16; money = 37; special = 0; break;
	case 15:wcscpy_s(name, L"铁面人"); position = 34; hp = 180; atk = 38; def = 38; money = 38; special = 2; break;
	case 16:wcscpy_s(name, L"影子战士"); position = 19; hp = 317; atk = 89; def = 28; money = 40; special = 0; break;
	case 17:wcscpy_s(name, L"红蝙蝠"); position = 6; hp = 344; atk = 86; def = 38; money = 43; special = 0; break;
	case 18:wcscpy_s(name, L"中级卫兵"); position = 21; hp = 374; atk = 50; def = 120; money = 46; special = 0; break;
	case 19:wcscpy_s(name, L"高级法师"); position = 9; hp = 400; atk = 85; def = 55; money = 47; special = 1; break;
	case 20:wcscpy_s(name, L"初级巫师"); position = 10; hp = 433; atk = 94; def = 49; money = 49; special = 0; break;
	case 21:wcscpy_s(name, L"兽面武士"); position = 17; hp = 451; atk = 110; def = 30; money = 52; special = 0; break;
	case 22:wcscpy_s(name, L"初级骑士"); position = 25; hp = 477; atk = 68; def = 68; money = 55; special = 0; break;
	case 23:wcscpy_s(name, L"青衣警卫"); position = 38; hp = 489; atk = 126; def = 29; money = 58; special = 0; break;
	case 24:wcscpy_s(name, L"双手剑士"); position = 23; hp = 500; atk = 300; def = 0; money = 60; special = 0; break;
	case 25:wcscpy_s(name, L"冥队长"); position = 15; hp = 544; atk = 105; def = 50; money = 64; special = 0; break;
	case 26:wcscpy_s(name, L"绿兽人"); position = 35; hp = 578; atk = 121; def = 43; money = 69; special = 0; break;
	case 27:wcscpy_s(name, L"紫骷髅"); position = 32; hp = 614; atk = 134; def = 66; money = 75; special = 0; break;
	case 28:wcscpy_s(name, L"近卫骑士"); position = 39; hp = 666; atk = 157; def = 70; money = 79; special = 0; break;
	case 29:wcscpy_s(name, L"高级骑士"); position = 26; hp = 689; atk = 188; def = 81; money = 81; special = 0; break;
	case 30:wcscpy_s(name, L"冥战士"); position = 24; hp = 722; atk = 193; def = 88; money = 87; special = 0; break;
	case 31:wcscpy_s(name, L"高级卫兵"); position = 22; hp = 748; atk = 100; def = 240; money = 92; special = 0; break;
	case 32:wcscpy_s(name, L"紫蝙蝠"); position = 33; hp = 811; atk = 224; def = 100; money = 97; special = 0; break;
	case 33:wcscpy_s(name, L"高级巫师"); position = 11; hp = 836; atk = 150; def = 150; money = 102; special = 0; break;
	case 34:wcscpy_s(name, L"红衣警卫"); position = 28; hp = 875; atk = 268; def = 133; money = 106; special = 0; break;
	case 35:wcscpy_s(name, L"灵武士"); position = 27; hp = 948; atk = 299; def = 127; money = 114; special = 0; break;
	case 36:wcscpy_s(name, L"灵法师"); position = 30; hp = 1000; atk = 600; def = 0; money = 120; special = 0; break;
	// boss
	case 49:wcscpy_s(name, L"冥灵魔王"); position = 7; hp = 4000; atk = 400; def = 400; money = 0; special = 0; break;
	default:position=-1;
	}
	if (position!=-1)
		for (int i=0; i<4; i++)
			monster[i]=new hgeSprite(consts.ht_monster, 32*i, 32*position, 32, 32);
}
void c_monster::show(GfxFont* f, int i, int j)
{
	if (id!=0)
	{
		monster[state]->Render(j*32+consts.ScreenLeft, i*32);
		if (consts.book && f!=NULL) {
			int damage=hero.getDamage(*this);
			int hp=hero.getHP();
			if (damage>=hp)
				f->SetColor(4294901760ul);
			else if (damage<=hp/16)
				f->SetColor(4278255360ul);
			else if (damage<=hp/8)
				f->SetColor(4290047668ul);
			else if (damage<=hp/4)
				f->SetColor(4291677440ul);
			else if (damage<=hp/2)
				f->SetColor(4293844098ul);
			else if (damage<=hp*2/3)
				f->SetColor(4294951361ul);
			else f->SetColor(4294942842ul);
			if (damage>=c_hero::MAX_DAMAGE)
				f->Print(j*32+consts.ScreenLeft, i*32+20, L"???");
			else if (damage<100000)
				f->Print(j*32+consts.ScreenLeft, i*32+20, L"%d", damage);
			else
				f->Print(j*32+consts.ScreenLeft, i*32+20, L"%.1fW", damage/10000.0);
		}
	}
}
int c_monster::getAtk() {
	int a = atk + consts.total_point;
	if (a < 0) a = 0;
	return a;
}
int c_monster::getDef() {
	int d = def + consts.total_point;
	if (d < 0) d = 0;
	if (special == 2 && d < hero.getAtk() - 1)
		d = hero.getAtk() - 1;
	return d;
}
void c_monster::printInfo()
{
	if (id!=0)
	{
		int py=16;
		GfxFont *f=new GfxFont(L"楷体", 24);
		wchar_t s0[100]=L"";
		if (special==1) wcscpy_s(s0, L"（魔攻）");
		else if (special==2) wcscpy_s(s0, L"（坚固）");
		f->Print(consts.ScreenLeft+consts.map_width*32+16, py, L"%s%s", name, s0);
		delete f;

		char s1[100] = "";

		if (consts.total_point >= 0)
			sprintf_s(s1, "+%d", consts.total_point);
		else
			sprintf_s(s1, "%d", consts.total_point);

		py+=32;
		consts.s_heart->Render(consts.ScreenLeft+consts.map_width*32+16, py);
		consts.hgef->printf(consts.ScreenLeft+consts.map_width*32+60, py, HGETEXT_LEFT, "%d", hp);
		py+=32;
		consts.s_sword1->Render(consts.ScreenLeft+consts.map_width*32+16, py);
		consts.hgef->printf(consts.ScreenLeft+consts.map_width*32+60, py, HGETEXT_LEFT, "%d (%d%s)", getAtk(), atk, s1);
		py+=32;
		consts.s_shield1->Render(consts.ScreenLeft+consts.map_width*32+16, py);
		consts.hgef->printf(consts.ScreenLeft+consts.map_width*32+60, py, HGETEXT_LEFT, "%d (%d%s)", getDef(), def, s1);
		py+=32;
		consts.s_coin->Render(consts.ScreenLeft+consts.map_width*32+16, py);
		consts.hgef->printf(consts.ScreenLeft+consts.map_width*32+60, py, HGETEXT_LEFT, "%d (/3=%d)", money, money/3);
		py+=32;
		consts.s_damage->Render(consts.ScreenLeft+consts.map_width*32+16, py);
		int damage=hero.getDamage(*this);
		if (damage==c_hero::MAX_DAMAGE)
			consts.hgef->printf(consts.ScreenLeft+consts.map_width*32+60, py, HGETEXT_LEFT, "???");
		else
			consts.hgef->printf(consts.ScreenLeft+consts.map_width*32+60, py, HGETEXT_LEFT, "%d", damage);
	}
}
void c_monster::changeState()
{
	state++;
	state%=4;
}