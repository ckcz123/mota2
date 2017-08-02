#include "stdafx.h"

extern Http http;
extern c_hero hero;

constants::constants()
{
	hge=NULL;
	volume=30;
	bgmvolume=100;
	ScreenLeft=240;
	music=true;
	map_width=13; map_height=13;
}

void constants::init()
{
	book=moving=false;
	item_time=-1;
	playtime=0.0;
	step=0;
	time_move=time_open=time_animation=time_battle=time_floor=0;
	item_choose = item_point = 0;
	curr_point = total_point = 0;
	isMyTurn=true;
	beatStarted=false;
	max=0;
	for (int i=0; i<100; i++) sd[i].hp=0;
}
void constants::loadResources()
{
	ht_map=hge->Texture_Load("Res/map.png");
	ht_icon=hge->Texture_Load("Res/icon.png");
	ht_hero=hge->Texture_Load("Res/hero.png");
	ht_monster=hge->Texture_Load("Res/monster.png");
	ht_skin=hge->Texture_Load("Res/skin.png");
	ht_npc=hge->Texture_Load("Res/npc.png");
	ht_special=hge->Texture_Load("Res/special.png");
	he_GetItem=hge->Effect_Load("Res/item.ogg");
	he_OpenDoor=hge->Effect_Load("Res/door.ogg");
	he_Attack=hge->Effect_Load("Res/attack.ogg");
	he_Music=hge->Effect_Load("Res/bgm.mp3");
	hgef=new hgeFont("Res/font.fnt");
	//ht_map
	s_ground=new hgeSprite(ht_map, 0, 0, 32, 32);
	s_wall=new hgeSprite(ht_map, 32, 0, 32, 32);
	//ht_door
	s_specialdoor=new hgeSprite(ht_map, 96, 64, 32, 32);
	//ht_item
	s_coin=new hgeSprite(ht_icon, 0, 64, 32, 32);
	s_floor=new hgeSprite(ht_icon, 32, 160, 32, 32);
	s_heart=new hgeSprite(ht_icon, 64, 192, 32, 32);
	s_expr=new hgeSprite(ht_icon, 96, 192, 32, 32);
	s_time=new hgeSprite(ht_icon, 32, 96, 32, 32);
	s_step=new hgeSprite(ht_icon, 32, 128, 32, 32);
	s_damage=new hgeSprite(ht_icon, 64, 160, 32, 32);
	s_enemyinfo=new hgeSprite(ht_icon, 32, 64, 32, 32);
	s_sword1=new hgeSprite(ht_icon, 0, 32, 32, 32);
	s_shield1=new hgeSprite(ht_icon, 32, 32, 32, 32);
	s_score=new hgeSprite(ht_icon, 64, 128, 32, 32);
	hc_Music=hge->Effect_PlayEx(he_Music, bgmvolume, 0, 1, true);
}

void constants::destroy()
{
	hge->Texture_Free(ht_map);
	hge->Texture_Free(ht_icon);
	hge->Texture_Free(ht_hero);
	hge->Texture_Free(ht_skin);
	hge->Texture_Free(ht_monster);
	hge->Texture_Free(ht_npc);
	hge->Effect_Free(he_GetItem);
	hge->Effect_Free(he_Music);
	hge->Effect_Free(he_OpenDoor);
	hge->Effect_Free(he_Attack);
	delete hgef;
}

void constants::setMsg(const wchar_t* s[50])
{
	hint.clear();
	for (int i=0; i<50; i++) {
		if (s[i]==NULL) break;
		hint.push_back(wstring(s[i]));
	}
	lasttime=clock();
	nowcnt=0;
	msg=MESSAGE_HINT;
}

void constants::setMsg(const wchar_t* s)
{
	hint.clear();
	hint.push_back(wstring(s));
	lasttime=clock();
	nowcnt=0;
	msg=MESSAGE_HINT;
}

void constants::goOn(c_hero* hero, c_map_floor* currFloor, float dt)
{
	playtime+=dt;
	if (moving) // 移动
	{
		time_move+=dt;
		if (time_move>=0.03f)
		{
			time_move-=0.03f;
			if (hero->moveComplete())
				moving=false;
		}
	}
	if (opening)
	{
		time_open+=dt;
		if (time_open>=0.03f)
		{
			time_open-=0.03f;
			if (map_openingdoor->open()) {
				hge->Effect_PlayEx(he_OpenDoor);
				opening=false;
			}
		}
	}
	
	time_animation+=dt;
	if (time_animation>=0.1f) // 四次后又回到自身状态
	{
		time_animation-=0.1f;
		currFloor->animation();
	}
}

void constants::printInfo()
{
	s_step->Render(ScreenLeft+map_width*32+24, 340);
	hgef->printf(ScreenLeft+map_width*32+68, 340, HGETEXT_LEFT, "%d", step);
	int ptm=playtime;
	s_time->Render(ScreenLeft+map_width*32+24, 298);
	if (ptm>=3600)
		hgef->printf(ScreenLeft+map_width*32+68, 298, HGETEXT_LEFT, "%02d : %02d : %02d", ptm/3600, (ptm/60)%60, ptm%60);
	else hgef->printf(ScreenLeft+map_width*32+68, 298, HGETEXT_LEFT, "%02d : %02d", ptm/60, ptm%60);

	// print book & item
	if (book)
		s_enemyinfo->Render(24, 288);

	if (item_time>=0) {
		s_floor->Render(80, 288);
		GfxFont *f=new GfxFont(L"楷体", 14, true);
		f->Print(108, 308, L"%d", item_time);
		delete f;
	}

}

void constants::upload()
{
	thread t1(&constants::doUpload, this);
	t1.detach();
}

void constants::doUpload()
{
	char url[200];
	int time=item_time; if (time<0) time=0;
	sprintf_s(url, "/upload?score=%d&hp=%d&atk=%d&def=%d&times=%d", hero.getScore(), hero.getHP(), hero.getAtk(),
		hero.getDef(), time);

	char* output=http.get(http.server, http.port, url, NULL);
	if (output!=NULL) {

		string text(output);
		stringstream stream;
		stream << text;

		string s1;
		stream >> s1 >> max;
		if (max<=0) max=-1;
		else {
			size_t outsize;
			mbstowcs_s(&outsize, rank, 20, s1.c_str(), 20);
		}
		delete output;
	}
	else
		max=-1;
}

void constants::getRank()
{
	msg=MESSAGE_RANK;
	max=0;
	for (int i=0; i<10; i++)
		rd[i].init();
	thread t2(&constants::doGetRank, this);
	t2.detach();
}

void constants::doGetRank()
{
	char* output=http.get(http.server, http.port, "/top", NULL);
	if (output!=NULL) {
		string text(output);
		stringstream stream;
		stream << text;
		stream >> max;
		for (int i=0; i<max; i++) {
			stream >> rd[i].score >> rd[i].hp >> rd[i].atk >> rd[i].def >> rd[i].item;
			string s1, s2;
			stream >> s1 >> s2;
			size_t outsize;
			mbstowcs_s(&outsize, rd[i].t1, 20, s1.c_str(), 20);
			mbstowcs_s(&outsize, rd[i].t2, 20, s2.c_str(), 20);
		}
		delete output;
		if (max==0) max=1;
	}
	else
		max=-1;
}

void constants::save(FILE* f)
{
	fprintf_s(f, "%d %d %d %d %d %d %.2f\n", map_width, map_height, total_point, book?1:0, item_time, step, playtime);
}

void constants::load(FILE* f)
{
	int _book;
	fscanf_s(f, "%d %d %d %d %d %d %f", &map_width, &map_height, &total_point, &_book, &item_time, &step, &playtime);
	book=_book==1;
	moving=false;
}

void constants::load(constants* another) {
	map_width = another->map_width;
	map_height = another->map_height;
	total_point = another->total_point;
	book = another->book;
	item_time= another->item_time;
	step = another->step;
	playtime = another->playtime;
}