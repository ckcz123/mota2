#include "stdafx.h"

// ��ͼ��Ϣ
c_map_floor map_floor[50];

// ��ʿ��Ϣ
c_hero hero;

// ������Ϣ
constants consts;

void loadsave()
{
	FILE *savefile;
	constants tmpcon;
	c_hero tmphero;
	for (int i=0; i<10; i++) {
		char s[100]="";
		sprintf_s(s, "Save/save%d.dat", i);
		int err=fopen_s(&savefile, s, "r");
		if (err!=0)
			consts.sd[i].hp=-1;
		else {
			tmpcon.load(savefile);
			tmphero.load(savefile);
			consts.sd[i].init(tmphero.getHP(), tmphero.getAtk(), tmphero.getDef(), tmphero.getNowFloor());
			fclose(savefile);
		}
	}
	consts.lasttime=clock();
}

void save(int id)
{
	FILE *savefile;
	char s[100]="";
	sprintf_s(s, "Save/save%d.dat", id);
	fopen_s(&savefile, s, "w");
	consts.save(savefile);
	hero.save(savefile);
	for (int i=0; i<consts.map_floornum; i++)map_floor[i].save(savefile);
	for (int i=31; i<=consts.special_floornum; i++)map_floor[i].save(savefile);
	fclose(savefile);
	consts.setMsg("�浵�ɹ���");
}
void load(int id)
{
	FILE *loadfile;
	char s[100]="";
	sprintf_s(s, "Save/save%d.dat", id);
	fopen_s(&loadfile, s, "r");
	consts.load(loadfile);
	hero.load(loadfile);
	for (int i=0; i<consts.map_floornum; i++)map_floor[i].load(loadfile);
	for (int i=31; i<=consts.special_floornum; i++)map_floor[i].load(loadfile);
	fclose(loadfile);
	consts.setMsg("�����ɹ���");
}
void showMessage(const char *s) // ��ʾ��ʾ
{
	hgeSprite *s_temp;
	s_temp=new hgeSprite(consts.ht_skin, 0, 0, 128, 128);
	s_temp->SetColor(0x88FFFFFF);
	s_temp->RenderStretch(16+consts.ScreenLeft, consts.map_height*32-160, consts.map_width*32+consts.ScreenLeft-16, consts.map_height*32-8);
	GfxFont *f=new GfxFont(L"����", 23);
	f->Print(16+consts.ScreenLeft+8, consts.map_height*32-160+8, "%s", s);
	delete f;
	delete s_temp;
}
void init(bool restart=false)
{
	// ��ʼ��
	consts.init();
	hero.init();
	// �����ͼ
	FILE *map_infile;
	fopen_s(&map_infile, "Res/map.dat", "r");
	for (int i=0; i<consts.map_floornum; i++)
	{
		int ch[30][30];
		for (int j=0; j<consts.map_height; j++)for (int k=0; k<consts.map_width; k++)fscanf_s(map_infile, "%d", &ch[j][k]);
		map_floor[i].init(i, ch);
	}
	for (int i=31; i<=consts.special_floornum; i++)
	{
		int ch[30][30];
		for (int j=0; j<consts.map_height; j++)for (int k=0; k<consts.map_width; k++)fscanf_s(map_infile, "%d", &ch[j][k]);
		map_floor[i].init(i, ch);
	}
	fclose(map_infile);
	if (restart)
		consts.setMsg("��Ϸ�����¿�ʼ��");
}
bool frameFunc()
{
	float dt=consts.hge->Timer_GetDelta();

	if (consts.isFree()&&consts.hge->Input_GetKeyState(HGEK_DOWN)&&hero.canMove(0))consts.moving=true;
	if (consts.isFree()&&consts.hge->Input_GetKeyState(HGEK_LEFT)&&hero.canMove(1))consts.moving=true;
	if (consts.isFree()&&consts.hge->Input_GetKeyState(HGEK_RIGHT)&&hero.canMove(2))consts.moving=true;
	if (consts.isFree()&&consts.hge->Input_GetKeyState(HGEK_UP)&&hero.canMove(3))consts.moving=true;
	if (consts.isFree()&&consts.hge->Input_GetKeyState(HGEK_H)) {
		const char* help_hint[50]={
			"����һ��̶���ֵ��RPG��С��\nϷ�����Ŀ���ǳ��϶�¥����\n��ץס������С�㡣\n\n[���س�������]",
			"��ͼ�зֲ���һ���������š�\n���ߡ������NPC�ȡ�\n\n��ͬ��ɫ������Ҫ��Ӧ��ɫ��\nԿ�ײ��ܿ�������������Ҫ��\n�ⷽʽ���ܿ�����",
			"������ս����ʽ�ǻغ��ƣ�\nÿ������Ĺ���������ķ���\n�۳�������ֵ��Ȼ�����乥��\n����ķ����۳��������ֵ��\nֱ�����������ֵΪ0����\n�ܹ����ɻ�ȡ��Һ;��顣",
			"��Һ;���ֵ�����������̵�\n�����Լ���������ͬʱ��Ҳ��\n��ͨ��ʰȡ��ͼ�ϵĵ��߽���\n���������籦ʯ�ͽ��ܿ�����\n����Ĺ���������Ѫƿ����\n�����������ֵ���ȵȡ�",
			"S/L: �浵/����\nF: ¥����У����������\nR: ���¿�ʼ\nM: ���ֿ���\nH: �鿴����\nQ: �˳���Ϸ"
		};
		consts.setMsg(help_hint);
	}
	if (consts.isFree()&&consts.hge->Input_GetKeyState(HGEK_Q)) consts.msg=consts.MESSAGE_QUIT;
	if (consts.isFree()&&consts.hge->Input_GetKeyState(HGEK_R)) consts.msg=consts.MESSAGE_RESTART;
	if (consts.isFree()&&consts.hge->Input_GetKeyState(HGEK_S)) {
		if (hero.getNowFloor()>=30&&!hero.nearStair()) {
			consts.setMsg("ֻ����¥�ݱ߲��ܴ浵��");
		}
		else {
			loadsave();
			consts.msg=consts.MESSAGE_SAVE;
		}
	}
	if (consts.isFree()&&consts.hge->Input_GetKeyState(HGEK_L)) {
		loadsave();
		consts.msg=consts.MESSAGE_LOAD;
	}
	if (consts.isFree()&&consts.hge->Input_GetKeyState(HGEK_F)) {
		if (hero.getNowFloor()>=30) consts.setMsg("���ﲻ��ʹ�÷�������");
		else if (consts.canfly) {
			if (hero.getNowFloor()==21) consts.setMsg("���������������¥ʧЧ�ˣ�");
			else consts.msg=consts.MESSAGE_FLYING;
		}
		else if (consts.lefttime<80) consts.setMsg("������������ʧ�ˣ�");
		else consts.setMsg("����Ҫ�Ȼ�÷�������");
	}
	if (consts.isFree()&&consts.hge->Input_GetKeyState(HGEK_M)) {
		consts.music=!consts.music;
		consts.setMsg(consts.music?"�����ѿ���":"�����ѹر�");
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
		if (consts.nowcnt>=consts.hint.size())
			consts.msg=consts.MESSAGE_NONE;
	}

	// �浵
	if (consts.msg==consts.MESSAGE_SAVE)
	{
		if (consts.hge->Input_GetKeyState(HGEK_DOWN)&&clock()-consts.lasttime>200) {
			consts.wanttosave++;
			if (consts.wanttosave>=10) consts.wanttosave=9;
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
			if (consts.wanttosave>=10) consts.wanttosave=9;
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
				consts.setMsg("��Ч�Ĵ浵��");
			else load(consts.wanttosave);
		}
	}

	// ʤ��orʧ��
	if ((consts.msg==consts.MESSAGE_WIN||consts.msg==consts.MESSAGE_LOSE)&&consts.hge->Input_GetKeyState(HGEK_ENTER)) return true;
	// �˳�
	if (consts.msg==consts.MESSAGE_QUIT && consts.hge->Input_GetKeyState(HGEK_SPACE)) return true;
	// ���¿�ʼ
	if (consts.msg==consts.MESSAGE_RESTART && consts.hge->Input_GetKeyState(HGEK_SPACE)) init(true);

	// ���ڷ���
	if (consts.msg==consts.MESSAGE_FLYING)
	{
		if (consts.hge->Input_GetKeyState(HGEK_UP)&&clock()-consts.lasttime>100)
		{
			hero.setFlyFloor(1);
			consts.lasttime=clock();
		}
		if (consts.hge->Input_GetKeyState(HGEK_DOWN)&&clock()-consts.lasttime>100)
		{
			hero.setFlyFloor(-1);
			consts.lasttime=clock();
		}
		if (consts.hge->Input_GetKeyState(HGEK_ESCAPE))
		{
			consts.msg=consts.MESSAGE_NONE;
		}
		if (consts.hge->Input_GetKeyState(HGEK_ENTER))
		{
			hero.fly();
			consts.msg=consts.MESSAGE_NONE;
		}
	}

	if (consts.msg==consts.MESSAGE_NPC)
	{
		int npcid=map_floor[hero.getNowFloor()].getinfo(hero.nextY(), hero.nextX())->getNpcID();
		if (consts.hge->Input_GetKeyState(HGEK_1)&&clock()-consts.lasttime>200) {
			hero.npc(1); consts.lasttime=clock();
		}
		else if (consts.hge->Input_GetKeyState(HGEK_2)&&clock()-consts.lasttime>200) {
			hero.npc(2); consts.lasttime=clock();
		}
		else if (consts.hge->Input_GetKeyState(HGEK_3)&&clock()-consts.lasttime>200) {
			hero.npc(3); consts.lasttime=clock();
		}
		else hero.npc();
	}

	if ((consts.msg==consts.MESSAGE_FLYING||consts.msg==consts.MESSAGE_NPC
		||consts.msg==consts.MESSAGE_QUIT||consts.msg==consts.MESSAGE_RESTART)&&consts.hge->Input_GetKeyState(HGEK_ENTER))
		consts.msg=consts.MESSAGE_NONE;

	consts.goOn(&hero, &map_floor[hero.getNowFloor()], dt);
	return false;
}
bool renderFunc()
{
	consts.hge->Gfx_BeginScene();
	consts.hge->Gfx_Clear(0);
	map_floor[hero.getNowFloor()].show();
	hero.setMaxFloor();
	hero.show();
	hero.printInfo();
	consts.printInfo();

	float mx, my; // ���λ��
	consts.hge->Input_GetMousePos(&mx, &my);
	int x=(mx-consts.ScreenLeft)/32, y=my/32;
	if (consts.battling)consts.monster_battling->printInfo();
	else if (consts.book && x>=0&&x<consts.map_width)map_floor[hero.getNowFloor()].printMonsterInfo(x, y);


	switch (consts.msg)
	{
	case consts.MESSAGE_QUIT:
		showMessage("�����˳���Ϸ��\n\n[ENTER] ������Ϸ\n[SPACE] �˳���Ϸ");
		break;
	case consts.MESSAGE_RESTART:
		showMessage("�������¿�ʼ��\n\n[ENTER] ������Ϸ\n[SPACE] ���¿�ʼ");
		break;;
	case consts.MESSAGE_WIN:
		if (consts.trueend)
			showMessage("�����ӵ�ף���£����º�����\nͬѧ˳���ش������������Ӵ�\n�����������మ���ȹ����Ҹ�\n��һ����\n\nTRUE END.");
		else
			showMessage("���º�����ͬѧ˳���ش�����\n�������Ӵ˹����˿����Ҹ���\n���\n\nHAPPY END.");
		break;
	case consts.MESSAGE_LOSE:
		showMessage("�����ˣ����º�����ͬѧ����\n����û�г����������ֱ����\n�����ǵ��ֻ�������һ��ģ�\n����Ҳû�ֿ���\n\nNORMAL END.");
		break;
	case consts.MESSAGE_HINT:
		showMessage(consts.hint.at(consts.nowcnt).c_str());
		break;
	case consts.MESSAGE_SAVE:
	{
		char ss[200];
		if (consts.sd[consts.wanttosave].hp<0)
			sprintf_s(ss, "�浵���ļ� %d\n(�հ�)\n\n[��] [��] ���Ĵ浵λ��\n[ENTER] ȷ�ϴ浵\n[ESC] ȡ��", consts.wanttosave+1);
		else
			if (consts.sd[consts.wanttosave].now_floor<30)
				sprintf_s(ss, "�浵���ļ� %d\n(F%d/HP%d/A%d/D%d)\n\n[��] [��] ���Ĵ浵λ��\n[ENTER] ȷ�ϴ浵\n[ESC] ȡ��",
					consts.wanttosave+1, consts.sd[consts.wanttosave].now_floor, consts.sd[consts.wanttosave].hp,
					consts.sd[consts.wanttosave].atk, consts.sd[consts.wanttosave].def);
			else
				sprintf_s(ss, "�浵���ļ� %d\n(F???/HP%d/A%d/D%d)\n\n[��] [��] ���Ĵ浵λ��\n[ENTER] ȷ�ϴ浵\n[ESC] ȡ��",
					consts.wanttosave+1, consts.sd[consts.wanttosave].hp,
					consts.sd[consts.wanttosave].atk, consts.sd[consts.wanttosave].def);
		showMessage(ss);
		break;
	}
	case consts.MESSAGE_LOAD:
	{
		char ss[200];
		if (consts.sd[consts.wanttosave].hp<0)
			sprintf_s(ss, "��ȡ�浵 %d\n(��Ч�Ĵ浵)\n\n[��] [��] ���Ķ���λ��\n[ENTER] ȷ�϶���\n[ESC] ȡ��", consts.wanttosave+1);
		else
			if (consts.sd[consts.wanttosave].now_floor<30)
				sprintf_s(ss, "��ȡ�浵 %d\n(F%d/HP%d/A%d/D%d)\n\n[��] [��] ���Ķ���λ��\n[ENTER] ȷ�϶���\n[ESC] ȡ��",
					consts.wanttosave+1, consts.sd[consts.wanttosave].now_floor, consts.sd[consts.wanttosave].hp,
					consts.sd[consts.wanttosave].atk, consts.sd[consts.wanttosave].def);
			else
				sprintf_s(ss, "��ȡ�浵 %d\n(F???/HP%d/A%d/D%d)\n\n[��] [��] ���Ķ���λ��\n[ENTER] ȷ�϶���\n[ESC] ȡ��",
					consts.wanttosave+1, consts.sd[consts.wanttosave].hp,
					consts.sd[consts.wanttosave].atk, consts.sd[consts.wanttosave].def);
		showMessage(ss);
		break;
	}
	case consts.MESSAGE_FLYING:
	{
		char ss[100];
		sprintf_s(ss, "��Ҫ���� %d ¥\n[��] [��] ����¥��\n[ENTER] ȷ�Ϸ���\n[ESC] ȡ��", hero.getFlyFloor());
		showMessage(ss);
		break;
	}
	default:
		break;
	}
	if (consts.msg==consts.MESSAGE_NPC) {
		int npcid=map_floor[hero.getNowFloor()].getinfo(hero.nextY(), hero.nextX())->getNpcID();
		int npctime=map_floor[hero.getNowFloor()].getinfo(hero.nextY(), hero.nextX())->getNpcVisit();
		if (npcid==45)
			showMessage("�����þ����������������\n[1] ����һ�� ��100���飩\n[2] ����+5 ��30���飩\n[3] ����+5 ��30���飩\n[ENTER] �˳�");
		if (npcid==46)
			showMessage("���빺��Կ����\n[1] ��Կ�� ��10��ң�\n[2] ��Կ�� ��50��ң�\n[3] ��Կ�� ��100��ң�\n[ENTER] �˳�");
		if (npcid==47)
			showMessage("�������25��ң�\n[1] ����+400\n[2] ����+4\n[3] ����+4\n[ENTER] �˳�");
		if (npcid==48)
			showMessage("�������100��ң�\n[1] ����+2000\n[2] ����+20\n[3] ����+20\n[ENTER] �˳�");
		if (npcid==49)
			showMessage("�����þ����������������\n[1] �������� ��270���飩\n[2] ����+17 ��95���飩\n[3] ����+17 ��95���飩\n[ENTER] �˳�");
		if (npcid==50)
			showMessage("���ж����Կ��Ҫ������\n[1] ��Կ�� ��7��ң�\n[2] ��Կ�� ��35��ң�\n[3] ��Կ�� ��70��ң�\n[ENTER] �˳�");
		if (npcid==53&&npctime==0)
			showMessage("500�㾭�黻ȡ120�㹥������\n����\n[1] ��\n[ENTER] ��Ҫ");
		if (npcid==54&&npctime==0)
			showMessage("500���һ�ȡ120���������\n����\n[1] ��\n[ENTER] ��Ҫ");
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
	consts.hge->System_SetState(HGE_TITLE, "����֮·");
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
