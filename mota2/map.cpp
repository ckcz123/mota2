#include "stdafx.h"

extern c_map_floor map_floor[50];
extern c_hero hero;
extern constants consts;

/***** 地图数据 *****/
const int map[30][30] = {
	{11,11,11,11,11,11,99,11,11,11,11,11,11},
	{11,81,10,82,10,83,24,84,10,85,10,86,11},
	{11,10,10,10,10,10,10,10,10,10,10,10,11},
	{11,75,10,76,10,77,10,78,10,79,10,80,11},
	{11,10,10,10,10,10,10,10,10,10,10,10,11},
	{11,69,10,70,10,71,10,72,10,73,10,74,11},
	{11,10,10,10,10,10,31,10,10,10,10,10,11},
	{11,63,10,64,10,65,10,66,10,67,10,68,11},
	{11,10,10,10,10,10,10,10,10,10,10,10,11},
	{11,57,10,58,10,59,10,60,10,61,10,62,11},
	{11,10,10,10,10,10,10,10,10,10,10,10,11},
	{11,51,10,52,10,53,41,54,10,55,10,56,11},
	{11,11,11,11,11,11,10,11,11,11,11,11,11},
};
/***** 地图数据 *****/

void c_map_door::init(int t)
{
	type=t;
	for (int i=0; i<4; i++) door[i]=new hgeSprite(consts.ht_map, 32*(t-21), 32*(i+2), 32, 32);
	opened = false;
	state=0;
}
void c_map_door::show(int i, int j)
{
	if (type!=0)door[state]->Render(j*32+consts.ScreenLeft, i*32);
}
bool c_map_door::open()
{
	state++;
	if (state==3)
	{
		this->init(0);
		return true;
	}
	return false;
}
void c_map_point::init(int s_type,int s_item, int s_monster, int s_door, int s_npc)
{
	type=s_type;
	item=s_item;
	monster.init(s_monster);
	door.init(s_door);
	npc.init(s_npc);
}
void c_map_point::show(GfxFont* f, int i, int j)
{
	(type==11?consts.s_wall:consts.s_ground)->Render(j*32+consts.ScreenLeft, i*32);
	if (item==31) consts.s_floor->Render(j*32+consts.ScreenLeft, i*32);
	monster.show(f, i, j);
	door.show(i, j);
	npc.show(i, j);
}
bool c_map_point::canMove(int f)
{
	if (type==10)
	{
		if (door.getType()!=0)
		{
			return false;
			

			if (true)
			{
				consts.opening=true;
				consts.map_openingdoor=&door;
				if (consts.music)
					consts.hge->Effect_PlayEx(consts.he_OpenDoor, consts.volume);
			}
			return false;

		}
		if (monster.getId()!=0)
		{
			if (hero.canBeat(monster))
			{

				// beat here!
				if (consts.music)
					consts.hge->Effect_PlayEx(consts.he_Attack, consts.volume);

				int point = monster.getMoney(), id=monster.getId();
				monster.init(0);

				// 打死了boss
				if (id == 99) {
					consts.msg = consts.MESSAGE_WIN;
				}
				else {
					consts.curr_point = point;
					consts.total_point += point / 3;
					consts.msg = consts.MESSAGE_POINT;

					// 全部杀完？
					int left = 0;
					for (int i = 0; i < consts.map_height; i++) {
						for (int j = 0; j < consts.map_width; j++) {
							if (map_floor[0].getinfo(i, j)->monster.getId() != 0)
								left++;
						}
					}
					if (left == 1) {
						consts.opening = true;
						consts.map_openingdoor = &(map_floor[0].getinfo(1, 6)->door);
					}

				}

			}
			return false;
		}
		if (npc.getId()!=0) {

			consts.map_npc = &npc;

			if (npc.getId() == 41) {
				
				consts.book = true;
				const wchar_t* msg[50] = {
					L"欢迎来到这个可变加点塔，\n请仔细阅读以下说明。\n怪物手册请收好，可将鼠标\n放在怪物上查看怪物属性。\n\n[ENTER] 下一页",
					L"本塔共36+1个怪，清空外围\n36个怪物后机关门会打开。\n每打死一个怪物就可以进行\n加点，同时地图上所有怪物\n攻防都会发生变化。",
					L"当你杀死一个点数为X的怪\n物后，你可以选择加X点攻\n击或X点防御或150X点生命\n值，同时地图上所有怪物攻\n防上升X/3（向下取整）。",
					L"得分计算公式：\n分数=150*(攻击+防御)+生命\n\n成绩将上传到服务器和大家\n进行比较，P键可查看当前\nMAX。",
					L"S/L: 存/读档\nR: 重新开始\nX: 使用道具\nP: 查看当前MAX\nM: 音乐开关",
					L"本塔由Sky_天空的梦使用C++\n编写而成，代码开源在：\nhttps://github.com/ckcz123/mota2/\n\n如有问题，请于发布帖下进\n行回复和反馈，谢谢支持！"
				};

			}

			return false;

		}
		return true;
	}
	else return false;
}
bool c_map_point::openSpecial()
{
	if (door.getType()!=8) return false;
	door.setOpen();
	consts.opening=true;
	consts.map_openingdoor=&door;
	if (consts.music)
		consts.hge->Effect_PlayEx(consts.he_OpenDoor, consts.volume);
	return true;
}
void c_map_point::save(FILE* f)
{
	fprintf_s(f, "%d %d %d %d %d\n", type, item, monster.getId(), door.getType(), npc.getId());
}
void c_map_point::load(FILE* f)
{
	int m, d, n;
	fscanf_s(f, "%d %d %d %d %d\n", &type, &item, &m, &d, &n);
	monster.init(m);
	door.init(d);
	npc.init(n);
}
void c_map_floor::init() {
	init(map);
}
void c_map_floor::init(const int ch[30][30])
{
	for (int i=0; i<consts.map_height; i++)
	{
		for (int j=0; j<consts.map_width; j++)
		{
			if (ch[i][j] == 10)info[i][j].init(10, 0, 0, 0, 0);
			if (ch[i][j] == 11)info[i][j].init(11, 0, 0, 0, 0);
			if (ch[i][j] == 24)info[i][j].init(10, 0, 0, 24, 0);
			if (ch[i][j] == 31)info[i][j].init(10, 31, 0, 0, 0);
			if (ch[i][j] == 41)info[i][j].init(10, 0, 0, 0, 41);
			if (ch[i][j] >= 51 && ch[i][j] <= 99)
				info[i][j].init(10, 0, ch[i][j], 0, 0);
		}
	}
}
void c_map_floor::show()
{
	GfxFont *f=new GfxFont(L"楷体", 12, true);
	for (int i=0; i<consts.map_height; i++)
	{
		for (int j=0; j<consts.map_width; j++)
		{
			info[i][j].show(f, i, j);
		}
	}
	delete f;
}
void c_map_floor::animation()
{
	for (int i=0; i<consts.map_height; i++)
		for (int j=0; j<consts.map_width; j++)
			info[i][j].animation();
}
void c_map_floor::printMonsterInfo(int i, int j)
{
	info[j][i].printMonsterInfo();
}
bool c_map_floor::canMove(int x, int y, int f)
{
	return info[y][x].canMove(f);
}
int c_map_floor::getItem(int x, int y)
{
	int c=info[y][x].getItem();
	if (c>0) info[y][x].distroy();
	return c;
}
void c_map_floor::save(FILE* f)
{
	for (int i=0; i<consts.map_height; i++)
	{
		for (int j=0; j<consts.map_width; j++)
		{
			info[i][j].save(f);
		}
	}
}
void c_map_floor::load(FILE* f)
{
	for (int i=0; i<consts.map_height; i++)
	{
		for (int j=0; j<consts.map_width; j++)
		{
			info[i][j].load(f);
		}
	}
}