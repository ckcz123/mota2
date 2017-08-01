#include "stdafx.h"

// ��ͼ��Ϣ
c_map_floor map_floor[50];

// ��ʿ��Ϣ
c_hero hero;

// ������Ϣ
constants consts;

// encode & decode file
bool fileConvert(char* from, char* to, bool encode=true) {
	char* pwd = "g-=f3j0o+";

	// ����ļ����ڣ���ɾ��
	remove(to);

	FILE *fp1, *fp2;
	register char ch;
	int j = 0;
	int j0 = 0;
	int err = fopen_s(&fp1, from, "r");
	if (fp1 == NULL || err!=0) return false;
	err = fopen_s(&fp2, to, "w");
	if (fp2 == NULL || err!=0) {
		fclose(fp1);
		return false;
	}

	while (pwd[++j0]);

	ch = fgetc(fp1);

	/*����/�����㷨��ʼ*/
	while (!feof(fp1)) {
		if (j0 > 7)
			j0 = 0;
		if (encode)
			ch += pwd[j0++];
		else
			ch -= pwd[j0++];
		fputc(ch, fp2);
		ch = fgetc(fp1);
	}
	fclose(fp1);
	fclose(fp2);
	return true;
}

void loadsave()
{
	FILE *savefile;
	constants tmpcon;
	c_hero tmphero;
	for (int i=0; i<100; i++) {
		char s[100]="";
		sprintf_s(s, "Save/save%d.dat", i);
		char* tmp = "Save/tmp";
		if (fileConvert(s, tmp, false)) {
			int err = fopen_s(&savefile, tmp, "r");
			if (err != 0)
				consts.sd[i].hp = -1;
			else {
				tmpcon.load(savefile);
				tmphero.load(savefile);
				consts.sd[i].init(tmphero.getHP(), tmphero.getAtk(), tmphero.getDef());
				fclose(savefile);
				remove(tmp);
			}
		}
		else consts.sd[i].hp = -1;
	}
	consts.lasttime=clock();
}

void save(int id)
{
	FILE *savefile;
	char* tmp = "Save/tmp";

	int err=fopen_s(&savefile, tmp, "w");
	if (err != 0) {
		consts.setMsg(L"�浵ʧ�ܣ�����Save�ļ����Ƿ���ڣ��Ƿ���ڶ�дȨ�ޡ�");
		return;
	}

	consts.save(savefile);
	hero.save(savefile);
	map_floor[0].save(savefile);
	fclose(savefile);

	char s[100] = "";
	sprintf_s(s, "Save/save%d.dat", id);
	
	if (fileConvert(tmp, s))
		consts.setMsg(L"�浵�ɹ���");
	else
		consts.setMsg(L"�浵ʧ�ܣ�����Save�ļ����Ƿ���ڣ��Ƿ���ڶ�дȨ�ޡ�");
	remove(tmp);
}
void load(int id)
{
	FILE *loadfile;
	char s[100]="";
	sprintf_s(s, "Save/save%d.dat", id);

	char* tmp = "Save/tmp";
	if (fileConvert(s, tmp, false)) {
		try {
			constants tmpcon;
			c_hero tmphero;
			fopen_s(&loadfile, tmp, "r");
			tmpcon.load(loadfile);
			tmphero.load(loadfile);
			map_floor[0].load(loadfile);
			fclose(loadfile);

			consts.load(&tmpcon);
			hero.load(&tmphero);

			consts.setMsg(L"�����ɹ���");
			remove(tmp);
			return;
		}
		catch (exception&) {}
	}
	consts.setMsg(L"����ʧ�ܣ�����Save�ļ����Ƿ���ڣ��浵�Ƿ���Ч");
	remove(tmp);

}
void showMessage(const wchar_t *s) // ��ʾ��ʾ
{
	hgeSprite *s_temp;
	s_temp=new hgeSprite(consts.ht_skin, 0, 0, 128, 128);
	s_temp->SetColor(0x88FFFFFF);
	s_temp->RenderStretch(16+consts.ScreenLeft, consts.map_height*32-160, consts.map_width*32+consts.ScreenLeft-16, consts.map_height*32-8);
	GfxFont *f=new GfxFont(L"����", 23);
	f->Print(16+consts.ScreenLeft+8, consts.map_height*32-160+8, L"%s", s);
	delete f;
	delete s_temp;
}
void init(bool restart=false)
{
	// ��ʼ��
	consts.init();
	hero.init();
	map_floor[0].init();
	if (restart)
		consts.setMsg(L"��Ϸ�����¿�ʼ��");
}
bool frameFunc()
{
	float dt=consts.hge->Timer_GetDelta();

	if (consts.isFree()&&consts.hge->Input_GetKeyState(HGEK_DOWN)&&hero.canMove(0))consts.moving=true;
	if (consts.isFree()&&consts.hge->Input_GetKeyState(HGEK_LEFT)&&hero.canMove(1))consts.moving=true;
	if (consts.isFree()&&consts.hge->Input_GetKeyState(HGEK_RIGHT)&&hero.canMove(2))consts.moving=true;
	if (consts.isFree()&&consts.hge->Input_GetKeyState(HGEK_UP)&&hero.canMove(3))consts.moving=true;

	if (consts.isFree()&&consts.hge->Input_GetKeyState(HGEK_R)) consts.msg=consts.MESSAGE_RESTART;
	if (consts.isFree()&&consts.hge->Input_GetKeyState(HGEK_S)) {
		loadsave();
		consts.msg=consts.MESSAGE_SAVE;
	}
	if (consts.isFree()&&consts.hge->Input_GetKeyState(HGEK_L)) {
		loadsave();
		consts.msg=consts.MESSAGE_LOAD;
	}
	if (consts.isFree()&&consts.hge->Input_GetKeyState(HGEK_M)) {
		consts.music=!consts.music;
		consts.setMsg(consts.music?L"�����ѿ���":L"�����ѹر�");
		if (consts.music) consts.hge->Channel_SetVolume(consts.hc_Music, consts.bgmvolume);
		else consts.hge->Channel_SetVolume(consts.hc_Music, 0);
	}

	// ��ʾ��Ϣ
	if (consts.msg==consts.MESSAGE_HINT)
	{
		if (consts.hge->Input_GetKeyState(HGEK_ENTER)&&clock()-consts.lasttime>200) {
			consts.nowcnt++;
			consts.lasttime=clock();
		}
		if (consts.nowcnt >= (int)consts.hint.size()) {
			consts.msg = consts.MESSAGE_NONE;
			if (consts.map_npc != NULL) {
				consts.map_npc->init(0);
				consts.map_npc = NULL;
			}

		}
	}

	// �浵
	if (consts.msg==consts.MESSAGE_SAVE)
	{
		if (consts.hge->Input_GetKeyState(HGEK_DOWN)&&clock()-consts.lasttime>200) {
			consts.wanttosave++;
			if (consts.wanttosave>=100) consts.wanttosave=99;
			consts.lasttime=clock();
		}
		else if (consts.hge->Input_GetKeyState(HGEK_UP)&&clock()-consts.lasttime>200) {
			consts.wanttosave--;
			if (consts.wanttosave<0) consts.wanttosave=0;
			consts.lasttime=clock();
		}
		else if (consts.hge->Input_GetKeyState(HGEK_ESCAPE))
			consts.msg=consts.MESSAGE_NONE;
		else if (consts.hge->Input_GetKeyState(HGEK_ENTER))
			save(consts.wanttosave);
	}

	// ����
	if (consts.msg==consts.MESSAGE_LOAD)
	{
		if (consts.hge->Input_GetKeyState(HGEK_DOWN)&&clock()-consts.lasttime>200) {
			consts.wanttosave++;
			if (consts.wanttosave>=100) consts.wanttosave=99;
			consts.lasttime=clock();
		}
		else if (consts.hge->Input_GetKeyState(HGEK_UP)&&clock()-consts.lasttime>200) {
			consts.wanttosave--;
			if (consts.wanttosave<0) consts.wanttosave=0;
			consts.lasttime=clock();
		}
		else if (consts.hge->Input_GetKeyState(HGEK_ESCAPE))
			consts.msg=consts.MESSAGE_NONE;
		else if (consts.hge->Input_GetKeyState(HGEK_ENTER)) {
			if (consts.sd[consts.wanttosave].hp<0)
				consts.setMsg(L"��Ч�Ĵ浵��");
			else load(consts.wanttosave);
		}
	}

	// ʤ��orʧ��
	if (consts.msg==consts.MESSAGE_WIN&&consts.hge->Input_GetKeyState(HGEK_ENTER)) return true;

	// ���¿�ʼ
	if (consts.msg==consts.MESSAGE_RESTART && consts.hge->Input_GetKeyState(HGEK_SPACE)) init(true);
	if (consts.msg==consts.MESSAGE_RESTART &&consts.hge->Input_GetKeyState(HGEK_ENTER)) consts.msg=consts.MESSAGE_NONE;

	consts.goOn(&hero, &map_floor[0], dt);
	return false;
}
bool renderFunc()
{
	consts.hge->Gfx_BeginScene();
	consts.hge->Gfx_Clear(0);
	map_floor[0].show();
	hero.show();
	hero.printInfo();
	consts.printInfo();

	float mx, my; // ���λ��
	consts.hge->Input_GetMousePos(&mx, &my);
	int x=(mx-consts.ScreenLeft)/32, y=my/32;
	if (consts.book && x>=0&&x<consts.map_width)map_floor[0].printMonsterInfo(x, y);

	switch (consts.msg)
	{
	case consts.MESSAGE_RESTART:
		showMessage(L"�������¿�ʼ��\n\n[ENTER] ������Ϸ\n[SPACE] ���¿�ʼ");
		break;;
	case consts.MESSAGE_WIN:
		
		/* win */



		break;
	case consts.MESSAGE_HINT:
		showMessage(consts.hint.at(consts.nowcnt).c_str());
		break;
	case consts.MESSAGE_SAVE:
	{
		wchar_t ss[200];
		if (consts.sd[consts.wanttosave].hp<0)
			wsprintf(ss, L"�浵���ļ� %d\n(�հ�)\n\n[��] [��] ���Ĵ浵λ��\n[ENTER] ȷ�ϴ浵\n[ESC] ȡ��", consts.wanttosave+1);
		else
			wsprintf(ss, L"�浵���ļ� %d\n(HP%d/A%d/D%d)\n\n[��] [��] ���Ĵ浵λ��\n[ENTER] ȷ�ϴ浵\n[ESC] ȡ��",
					consts.wanttosave+1, consts.sd[consts.wanttosave].hp,
					consts.sd[consts.wanttosave].atk, consts.sd[consts.wanttosave].def);
		showMessage(ss);
		break;
	}
	case consts.MESSAGE_LOAD:
	{
		wchar_t ss[200];
		if (consts.sd[consts.wanttosave].hp<0)
			wsprintf(ss, L"��ȡ�浵 %d\n(��Ч�Ĵ浵)\n\n[��] [��] ���Ķ���λ��\n[ENTER] ȷ�϶���\n[ESC] ȡ��", consts.wanttosave+1);
		else
			wsprintf(ss, L"��ȡ�浵 %d\n(HP%d/A%d/D%d)\n\n[��] [��] ���Ķ���λ��\n[ENTER] ȷ�϶���\n[ESC] ȡ��",
					consts.wanttosave+1, consts.sd[consts.wanttosave].hp,
					consts.sd[consts.wanttosave].atk, consts.sd[consts.wanttosave].def);
		showMessage(ss);
		break;
	}
	case consts.MESSAGE_ITEM:

		break;
	case consts.MESSAGE_POINT:

		break;
	case consts.MESSAGE_RANK:

		break;
	default:
		break;
	}
	
	consts.hge->Gfx_EndScene();
	return false;
}
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{

	//hge��ʼ��
	consts.hge=hgeCreate(HGE_VERSION);
	consts.hge->System_SetState(HGE_FRAMEFUNC, frameFunc);
	consts.hge->System_SetState(HGE_RENDERFUNC, renderFunc);
	consts.hge->System_SetState(HGE_USESOUND, true);
	consts.hge->System_SetState(HGE_TITLE, "�ɱ�ӵ㵥�� - By Sky_��յ���");
	consts.hge->System_SetState(HGE_WINDOWED, true);
	consts.hge->System_SetState(HGE_HIDEMOUSE, false);
	consts.hge->System_SetState(HGE_SCREENHEIGHT, 32*consts.map_height);
	consts.hge->System_SetState(HGE_SCREENWIDTH, 32*consts.map_width+2*consts.ScreenLeft);
	if (consts.hge->System_Initiate())
	{
		consts.loadResources();
		init();
		consts.hge->System_Start();
		consts.destroy();
	}
	consts.hge->System_Shutdown();
	consts.hge->Release();
	return 0;
}
