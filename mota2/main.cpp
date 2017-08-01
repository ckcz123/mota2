#include "stdafx.h"

// 地图信息
c_map_floor map_floor[50];

// 勇士信息
c_hero hero;

// 常量信息
constants consts;

// encode & decode file
bool fileConvert(char* from, char* to, bool encode=true) {
	char* pwd = "g-=f3j0o+";

	// 如果文件存在，先删除
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

	/*加密/解密算法开始*/
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
		consts.setMsg(L"存档失败！请检查Save文件夹是否存在，是否存在读写权限。");
		return;
	}

	consts.save(savefile);
	hero.save(savefile);
	map_floor[0].save(savefile);
	fclose(savefile);

	char s[100] = "";
	sprintf_s(s, "Save/save%d.dat", id);
	
	if (fileConvert(tmp, s))
		consts.setMsg(L"存档成功！");
	else
		consts.setMsg(L"存档失败！请检查Save文件夹是否存在，是否存在读写权限。");
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

			consts.setMsg(L"读档成功！");
			remove(tmp);
			return;
		}
		catch (exception&) {}
	}
	consts.setMsg(L"读档失败！请检查Save文件夹是否存在，存档是否有效");
	remove(tmp);

}
void showMessage(const wchar_t *s) // 显示提示
{
	hgeSprite *s_temp;
	s_temp=new hgeSprite(consts.ht_skin, 0, 0, 128, 128);
	s_temp->SetColor(0x88FFFFFF);
	s_temp->RenderStretch(16+consts.ScreenLeft, consts.map_height*32-160, consts.map_width*32+consts.ScreenLeft-16, consts.map_height*32-8);
	GfxFont *f=new GfxFont(L"楷体", 23);
	f->Print(16+consts.ScreenLeft+8, consts.map_height*32-160+8, L"%s", s);
	delete f;
	delete s_temp;
}
void init(bool restart=false)
{
	// 初始化
	consts.init();
	hero.init();
	map_floor[0].init();
	if (restart)
		consts.setMsg(L"游戏已重新开始！");
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
		consts.setMsg(consts.music?L"音乐已开启":L"音乐已关闭");
		if (consts.music) consts.hge->Channel_SetVolume(consts.hc_Music, consts.bgmvolume);
		else consts.hge->Channel_SetVolume(consts.hc_Music, 0);
	}

	// 提示消息
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

	// 存档
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

	// 读档
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
				consts.setMsg(L"无效的存档。");
			else load(consts.wanttosave);
		}
	}

	// 胜利or失败
	if (consts.msg==consts.MESSAGE_WIN&&consts.hge->Input_GetKeyState(HGEK_ENTER)) return true;

	// 重新开始
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

	float mx, my; // 鼠标位置
	consts.hge->Input_GetMousePos(&mx, &my);
	int x=(mx-consts.ScreenLeft)/32, y=my/32;
	if (consts.book && x>=0&&x<consts.map_width)map_floor[0].printMonsterInfo(x, y);

	switch (consts.msg)
	{
	case consts.MESSAGE_RESTART:
		showMessage(L"你想重新开始吗？\n\n[ENTER] 继续游戏\n[SPACE] 重新开始");
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
			wsprintf(ss, L"存档到文件 %d\n(空白)\n\n[↑] [↓] 更改存档位置\n[ENTER] 确认存档\n[ESC] 取消", consts.wanttosave+1);
		else
			wsprintf(ss, L"存档到文件 %d\n(HP%d/A%d/D%d)\n\n[↑] [↓] 更改存档位置\n[ENTER] 确认存档\n[ESC] 取消",
					consts.wanttosave+1, consts.sd[consts.wanttosave].hp,
					consts.sd[consts.wanttosave].atk, consts.sd[consts.wanttosave].def);
		showMessage(ss);
		break;
	}
	case consts.MESSAGE_LOAD:
	{
		wchar_t ss[200];
		if (consts.sd[consts.wanttosave].hp<0)
			wsprintf(ss, L"读取存档 %d\n(无效的存档)\n\n[↑] [↓] 更改读档位置\n[ENTER] 确认读档\n[ESC] 取消", consts.wanttosave+1);
		else
			wsprintf(ss, L"读取存档 %d\n(HP%d/A%d/D%d)\n\n[↑] [↓] 更改读档位置\n[ENTER] 确认读档\n[ESC] 取消",
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

	//hge初始化
	consts.hge=hgeCreate(HGE_VERSION);
	consts.hge->System_SetState(HGE_FRAMEFUNC, frameFunc);
	consts.hge->System_SetState(HGE_RENDERFUNC, renderFunc);
	consts.hge->System_SetState(HGE_USESOUND, true);
	consts.hge->System_SetState(HGE_TITLE, "可变加点单层 - By Sky_天空的梦");
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
