#include "stdafx.h"

// 地图信息
c_map_floor map_floor[50];

// 勇士信息
c_hero hero;

// 常量信息
constants consts;

// HTTP
Http http;

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
				consts.sd[i].init(tmpcon.level, tmphero.getHP(), tmphero.getAtk(), tmphero.getDef());
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
	s_temp->SetColor(0xBBFFFFFF);
	s_temp->RenderStretch(16+consts.ScreenLeft, consts.map_height*32-160, consts.map_width*32+consts.ScreenLeft-16, consts.map_height*32-8);
	GfxFont *f=new GfxFont(L"楷体", 22);
	f->Print(16+consts.ScreenLeft+8, consts.map_height*32-160+8, L"%s", s);
	delete f;
	delete s_temp;
}
void showMax(const wchar_t *s)
{
	hgeSprite *s_temp;
	s_temp=new hgeSprite(consts.ht_skin, 0, 0, 128, 128);
	s_temp->SetColor(0xBBFFFFFF);
	s_temp->RenderStretch(16+consts.ScreenLeft, consts.map_height*32-400, consts.map_width*32+consts.ScreenLeft-16, consts.map_height*32-8);
	GfxFont *f=new GfxFont(L"楷体", 22);
	f->Print(16+consts.ScreenLeft+8, consts.map_height*32-400+8, L"%s", s);
	delete f;
	delete s_temp;
}
void init(bool restart=false)
{
	// 初始化
	consts.init();
	hero.init();
	map_floor[0].init();
	// if (restart)
	//	consts.setMsg(L"游戏已重新开始！");
	consts.msg=consts.MESSAGE_START;
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
	if (consts.isFree()&&consts.hge->Input_GetKeyState(HGEK_P)) consts.getRank();
	if (consts.isFree()&&consts.hge->Input_GetKeyState(HGEK_M)) {
		consts.music=!consts.music;
		consts.setMsg(consts.music?L"音乐已开启":L"音乐已关闭");
		if (consts.music) consts.hge->Channel_SetVolume(consts.hc_Music, consts.bgmvolume);
		else consts.hge->Channel_SetVolume(consts.hc_Music, 0);
	}
	if (consts.isFree()&&consts.hge->Input_GetKeyState(HGEK_X)&&consts.item_time>=0)
	{
		consts.item_choose=0;
		consts.item_point=0;
		consts.msg=consts.MESSAGE_ITEM;
	}

	if (consts.msg==consts.MESSAGE_START)
	{

		if (consts.hge->Input_GetKeyState(HGEK_1))
		{
			consts.level=1;
			consts.msg=consts.MESSAGE_NONE;
		}
		else if (consts.hge->Input_GetKeyState(HGEK_2))
		{
			consts.level=2;
			consts.msg=consts.MESSAGE_NONE;
		}
		else if (consts.hge->Input_GetKeyState(HGEK_3))
		{
			consts.level=3;
			consts.msg=consts.MESSAGE_NONE;
		}

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

	// 加点过程
	if (consts.msg==consts.MESSAGE_POINT)
	{
		if (consts.hge->Input_GetKeyState(HGEK_1)) {
			hero.addHP(consts.curr_point);
			consts.curr_point=0;
			consts.msg=consts.MESSAGE_NONE;
		}
		else if (consts.hge->Input_GetKeyState(HGEK_2)) {
			hero.addAtk(consts.curr_point);
			consts.curr_point=0;
			consts.msg=consts.MESSAGE_NONE;
		}
		else if (consts.hge->Input_GetKeyState(HGEK_3)) {
			hero.addDef(consts.curr_point);
			consts.curr_point=0;
			consts.msg=consts.MESSAGE_NONE;
		}
	}

	// 使用道具
	if (consts.msg==consts.MESSAGE_ITEM)
	{
		if (consts.hge->Input_GetKeyState(HGEK_ESCAPE)) consts.msg=consts.MESSAGE_NONE;
		else if (consts.item_choose==0) {
			if (consts.hge->Input_GetKeyState(HGEK_1)) consts.item_choose=1;
			else if (consts.hge->Input_GetKeyState(HGEK_2)) consts.item_choose=2;
		}
		else {
			if (consts.hge->Input_GetKeyState(HGEK_LEFT)&&clock()-consts.lasttime>100) {
				consts.item_point-=10;
				if (consts.item_point<0) consts.item_point=0;
				consts.lasttime=clock();
			}
			else if (consts.hge->Input_GetKeyState(HGEK_DOWN)&&clock()-consts.lasttime>100) {
				consts.item_point--;
				if (consts.item_point<0) consts.item_point=0;
				consts.lasttime=clock();
			}
			else if (consts.hge->Input_GetKeyState(HGEK_UP)&&clock()-consts.lasttime>100) {
				consts.item_point++;
				if (consts.item_choose==1&&consts.item_point>hero.getAtk()) consts.item_point=hero.getAtk();
				if (consts.item_choose==2&&consts.item_point>hero.getDef()) consts.item_point=hero.getDef();
				consts.lasttime=clock();
			}
			else if (consts.hge->Input_GetKeyState(HGEK_RIGHT)&&clock()-consts.lasttime>100) {
				consts.item_point+=10;
				if (consts.item_choose==1&&consts.item_point>hero.getAtk()) consts.item_point=hero.getAtk();
				if (consts.item_choose==2&&consts.item_point>hero.getDef()) consts.item_point=hero.getDef();
				consts.lasttime=clock();
			}
			else if (consts.hge->Input_GetKeyState(HGEK_ENTER)) {
				if (consts.item_choose==1) hero.addAtk(-consts.item_point);
				if (consts.item_choose==2) hero.addDef(-consts.item_point);
				consts.total_point-=consts.item_point/2;
				consts.item_time++;
				wchar_t ss[200];
				wsprintf(ss, L"支付%d点%s成功！\n\n全场怪兽攻防下降%d点。", consts.item_point, 
					consts.item_choose==1?L"攻击力":L"防御力", consts.item_point/2);
				consts.setMsg(ss);
				consts.item_point=consts.item_choose=0;
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
	if (consts.msg==consts.MESSAGE_WIN&&consts.hge->Input_GetKeyState(HGEK_ENTER)) {
		init();
	}

	// 重新开始
	if (consts.msg==consts.MESSAGE_RESTART) {
		if (consts.hge->Input_GetKeyState(HGEK_ENTER))
			init(true);
		else if (consts.hge->Input_GetKeyState(HGEK_ESCAPE))
			consts.msg=consts.MESSAGE_NONE;
	}


	if ((consts.msg==consts.MESSAGE_RESTART || consts.msg==consts.MESSAGE_RANK)
		&& consts.hge->Input_GetKeyState(HGEK_ENTER)) consts.msg=consts.MESSAGE_NONE;

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
	case consts.MESSAGE_START:
		showMessage(L"欢迎来到此塔！感谢您的大力支持！\n请选择难度：\n\n[1] 简单\n[2] 普通\n[3] 困难");
		break;
	case consts.MESSAGE_RESTART:
		showMessage(L"您想重新开始吗？\n\n[ENTER] 重新开始\n[ESC] 返回游戏");
		break;
	case consts.MESSAGE_WIN:
	{
		/* win */
		wchar_t ss[200];

		if (consts.level!=3) {
			wsprintf(ss, L"恭喜通关！您的分数是 %d。\n简单或普通难度将不记录您的成绩。\n（P键可查看当前MAX记录信息。）\n欢迎截图到发布帖下进行炫耀！\n\n[ENTER] 重新开始", hero.getScore());
		}
		// uploading..
		else if (consts.max==0) {
			wsprintf(ss, L"恭喜通关！您的分数是 %d。\n正在上传成绩... 请稍后\n（P键可查看当前MAX记录信息。）\n欢迎截图到发布帖下进行炫耀！\n\n[ENTER] 重新开始", hero.getScore());
		}
		else if (consts.max==-1) {
			wsprintf(ss, L"恭喜通关！您的分数是 %d。\n成绩上传失败，请检查网络设置。\n（P键可查看当前MAX记录信息。）\n欢迎截图到发布帖下进行炫耀！\n\n[ENTER] 重新开始", hero.getScore());
		}
		else {
			wsprintf(ss, L"恭喜通关！您的分数是 %d。\n当前排名%s，当前MAX %d。\n（P键可查看当前MAX记录信息。）\n欢迎截图到发布帖下进行炫耀！\n\n[ENTER] 重新开始", hero.getScore(), consts.rank, consts.max);
		}

		showMessage(ss);
		break;
	}
	case consts.MESSAGE_HINT:
		showMessage(consts.hint.at(consts.nowcnt).c_str());
		break;
	case consts.MESSAGE_SAVE:
	{
		wchar_t ss[200];
		if (consts.sd[consts.wanttosave].hp<0)
			wsprintf(ss, L"存档到文件 %d\n(空白)\n\n[↑] [↓] 更改存档位置\n[ENTER] 确认存档\n[ESC] 取消", consts.wanttosave+1);
		else
			wsprintf(ss, L"存档到文件 %d\n(%s/HP%d/A%d/D%d)\n\n[↑] [↓] 更改存档位置\n[ENTER] 确认存档\n[ESC] 取消",
					consts.wanttosave+1, 
					consts.sd[consts.wanttosave].level==1?L"简单":consts.sd[consts.wanttosave].level==2?L"普通":consts.sd[consts.wanttosave].level==3?L"困难":L"无难度",
					consts.sd[consts.wanttosave].hp,
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
			wsprintf(ss, L"读取存档 %d\n(%s/HP%d/A%d/D%d)\n\n[↑] [↓] 更改读档位置\n[ENTER] 确认读档\n[ESC] 取消",
					consts.wanttosave+1, 
					consts.sd[consts.wanttosave].level==1?L"简单":consts.sd[consts.wanttosave].level==2?L"普通":consts.sd[consts.wanttosave].level==3?L"困难":L"无难度",
					consts.sd[consts.wanttosave].hp,
					consts.sd[consts.wanttosave].atk, consts.sd[consts.wanttosave].def);
		showMessage(ss);
		break;
	}
	case consts.MESSAGE_ITEM:
	{
		wchar_t ss[200];
		if (consts.item_choose==0) {
			wsprintf(ss, L"您已使用该道具%d次。\n\n请选择一项进行支付：\n[1] 攻击力\n[2] 防御力\n[ESC] 取消", consts.item_time);
		}
		else if (consts.item_choose==1 || consts.item_choose==2) {
			wsprintf(ss, L"您要支付%s的点数为：%d\n\n[↑][↓][←][→] 更改数值\n[ENTER] 确认支付\n[ESC] 取消", 
				consts.item_choose==1?L"攻击力":L"防御力", consts.item_point);
		}
		else break;
		showMessage(ss);
		break;
	}
	case consts.MESSAGE_POINT:
	{
		wchar_t ss[200];
		wsprintf(ss, L"所有怪物攻防上升%d。\n\n请选择一项：\n[1] 生命值+%d\n[2] 攻击力+%d\n[3] 防御力+%d", 
			consts.level==1?(int)(consts.curr_point/3.3):consts.level==2?(int)(consts.curr_point/3.15):consts.level==3?consts.curr_point/3:0,
			150*consts.curr_point, consts.curr_point, consts.curr_point);
		showMessage(ss);
		break;
	}
	case consts.MESSAGE_RANK:
	{
		
		wchar_t ss[1200];
		if (consts.max<0) {
			wsprintf(ss, L"拉取MAX记录失败，请检查网络连接，\n或在贴吧下进行反馈。\n\n[ENTER] 确定");
			showMessage(ss);
		}
		else if (consts.max==0) {
			wsprintf(ss, L"正在拉取MAX记录，请稍后...\n这可能需要几秒钟。\n\n[ENTER] 取消");
			showMessage(ss);
		}
		else {
			wcscpy_s(ss, L"当前MAX记录：\n\n");

			for (int i=0; i<10; i++) {
				wchar_t tmp[100];
				wsprintf(tmp, L"TOP%2d: %-8d", i+1, consts.rd[i].score);
				wcscat_s(ss, tmp);
				if (consts.rd[i].score>0) {
					wsprintf(tmp, L"  (%s %s)", consts.rd[i].t1, consts.rd[i].t2);
					wcscat_s(ss, tmp);
				}
				if (i<=2) {
					wsprintf(tmp, L"\n[%d, %d, %d, %d]",
						consts.rd[i].hp, consts.rd[i].atk, consts.rd[i].def, consts.rd[i].item);
					wcscat_s(ss, tmp);
				}
				wcscat_s(ss, L"\n");
			}

			wcscat_s(ss, L"\n[ENTER] 确定");
			showMax(ss);
		}
		
		break;
	}
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
	consts.hge->System_SetState(HGE_TITLE, "可变加点单层 By Sky_天空的梦");
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
