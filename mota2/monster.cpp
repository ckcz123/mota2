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
	case 2:wcscpy_s(name, L"红色史莱姆"); position = 1; hp = 100; atk = 18; def = 5; money = 5; special = 0; break;
	case 3:wcscpy_s(name, L"小蝙蝠"); position = 4; hp = 100; atk = 20; def = 7; money = 6; special = 0; break;
	case 4:wcscpy_s(name, L"青头怪"); position = 2; hp = 124; atk = 23; def = 8; money = 7; special = 0; break;
	case 5:wcscpy_s(name, L"骷髅人"); position = 12; hp = 137; atk = 26; def = 11; money = 9; special = 0; break;
	case 6:wcscpy_s(name, L"初级法师"); position = 8; hp = 144; atk = 35; def = 5; money = 11; special = 1; break;
	case 7:wcscpy_s(name, L"骷髅士兵"); position = 13; hp = 156; atk = 39; def = 10; money = 14; special = 0; break;
	case 8:wcscpy_s(name, L"史莱姆王"); position = 3; hp = 171; atk = 60; def = 5; money = 15; special = 0; break;
	case 9:wcscpy_s(name, L"石头人"); position = 18; hp = 187; atk = 35; def = 70; money = 20; special = 0; break;
	case 10:wcscpy_s(name, L"大蝙蝠"); position = 5; hp = 195; atk = 76; def = 38; money = 21; special = 0; break;
	case 11:wcscpy_s(name, L"魔法警卫"); position = 29; hp = 234; atk = 123; def = 0; money = 23; special = 0; break;
	case 12:wcscpy_s(name, L"初级卫兵"); position = 20; hp = 250; atk = 25; def = 25; money = 25; special = 2; break;

	case 13:wcscpy_s(name, L"骷髅队长"); position = 14; hp = 268; atk = 82; def = 31; money = 26; special = 0; break;
	case 14:wcscpy_s(name, L"兽面人"); position = 16; hp = 287; atk = 93; def = 35; money = 28; special = 0; break;
	case 15:wcscpy_s(name, L"影子战士"); position = 19; hp = 300; atk = 100; def = 30; money = 30; special = 0; break;
	case 16:wcscpy_s(name, L"红蝙蝠"); position = 6; hp = 343; atk = 113; def = 33; money = 34; special = 0; break;
	case 17:wcscpy_s(name, L"铁面人"); position = 34; hp = 374; atk = 70; def = 140; money = 37; special = 0; break;
	case 18:wcscpy_s(name, L"初级巫师"); position = 10; hp = 400; atk = 122; def = 40; money = 39; special = 1; break;
	case 19:wcscpy_s(name, L"兽面武士"); position = 17; hp = 438; atk = 135; def = 48; money = 42; special = 0; break;
	case 20:wcscpy_s(name, L"初级骑士"); position = 25; hp = 455; atk = 145; def = 45; money = 45; special = 0; break;
	case 21:wcscpy_s(name, L"青衣警卫"); position = 38; hp = 477; atk = 110; def = 80; money = 48; special = 0; break;
	case 22:wcscpy_s(name, L"中级卫兵"); position = 21; hp = 500; atk = 50; def = 50; money = 50; special = 2; break;
	case 23:wcscpy_s(name, L"冥队长"); position = 15; hp = 536; atk = 156; def = 50; money = 58; special = 0; break;
	case 24:wcscpy_s(name, L"双手剑士"); position = 23; hp = 600; atk = 300; def = 0; money = 60; special = 0; break;

	case 25:wcscpy_s(name, L"绿兽人"); position = 35; hp = 655; atk = 170; def = 55; money = 61; special = 0; break;
	case 26:wcscpy_s(name, L"近卫骑士"); position = 39; hp = 813; atk = 177; def = 57; money = 62; special = 0; break;
	case 27:wcscpy_s(name, L"高级法师"); position = 9; hp = 869; atk = 182; def = 61; money = 65; special = 1; break;
	case 28:wcscpy_s(name, L"紫骷髅"); position = 32; hp = 903; atk = 194; def = 63; money = 68; special = 0; break;
	case 29:wcscpy_s(name, L"高级骑士"); position = 26; hp = 924; atk = 206; def = 69; money = 71; special = 0; break;
	case 30:wcscpy_s(name, L"冥战士"); position = 24; hp = 967; atk = 222; def = 72; money = 73; special = 0; break;
	case 31:wcscpy_s(name, L"高级卫兵"); position = 22; hp = 750; atk = 75; def = 75; money = 75; special = 2; break;
	case 32:wcscpy_s(name, L"高级巫师"); position = 11; hp = 1000; atk = 240; def = 50; money = 76; special = 1; break;
	case 33:wcscpy_s(name, L"紫蝙蝠"); position = 33; hp = 1024; atk = 243; def = 81; money = 77; special = 0; break;
	case 34:wcscpy_s(name, L"灵武士"); position = 27; hp = 1333; atk = 122; def = 93; money = 80; special = 0; break;
	case 35:wcscpy_s(name, L"红衣警卫"); position = 28; hp = 1449; atk = 250; def = 100; money = 83; special = 0; break;
	case 36:wcscpy_s(name, L"灵法师"); position = 30; hp = 1500; atk = 500; def = 0; money = 90; special = 0; break;
	// boss
	case 49:wcscpy_s(name, L"冥灵魔王"); position = 7; hp = 5000; atk = 500; def = 100; money = 0; special = 0; break;
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
				f->SetColor(0xFFFF0000);
			else if (damage<=hp/10)
				f->SetColor(0xFF00FF00);
			else if (damage<=hp/5)
				f->SetColor(0xFF66CD00);
			else if (damage<=hp/2)
				f->SetColor(0xFF96CDCD);
			else if (damage<=hp*3/4)
				f->SetColor(0xFFEE7942);
			else f->SetColor(0xFFEE3B3B);
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
		int py=32;
		GfxFont *f=new GfxFont(L"楷体", 24);
		wchar_t s0[100]=L"";
		if (special==1) wcscpy_s(s0, L"（魔攻）");
		else if (special==2) wcscpy_s(s0, L"（坚固）");
		f->Print(consts.ScreenLeft+consts.map_width*32+24, py, L"%s%s", name, s0);
		delete f;

		py+=36;
		consts.s_heart->Render(consts.ScreenLeft+consts.map_width*32+24, py);
		consts.hgef->printf(consts.ScreenLeft+consts.map_width*32+68, py, HGETEXT_LEFT, "%d", hp);
		py+=36;
		consts.s_sword1->Render(consts.ScreenLeft+consts.map_width*32+24, py);
		consts.hgef->printf(consts.ScreenLeft+consts.map_width*32+68, py, HGETEXT_LEFT, "%-6d(%d%+d)", getAtk(), atk, consts.total_point);
		py+=36;
		consts.s_shield1->Render(consts.ScreenLeft+consts.map_width*32+24, py);
		consts.hgef->printf(consts.ScreenLeft+consts.map_width*32+68, py, HGETEXT_LEFT, "%-6d(%d%+d)", getDef(), def, consts.total_point);
		py+=36;
		consts.s_coin->Render(consts.ScreenLeft+consts.map_width*32+24, py);
		consts.hgef->printf(consts.ScreenLeft+consts.map_width*32+68, py, HGETEXT_LEFT, "%d", money);
		py+=36;
		consts.s_damage->Render(consts.ScreenLeft+consts.map_width*32+24, py);
		int damage=hero.getDamage(*this);
		if (damage==c_hero::MAX_DAMAGE)
			consts.hgef->printf(consts.ScreenLeft+consts.map_width*32+68, py, HGETEXT_LEFT, "???");
		else
			consts.hgef->printf(consts.ScreenLeft+consts.map_width*32+68, py, HGETEXT_LEFT, "%d", damage);
	}
}
void c_monster::changeState()
{
	state++;
	state%=4;
}