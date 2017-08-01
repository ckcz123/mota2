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
	lv=1;
	hp=1000;
	atk=10;
	def=10;
	money=0;
	experience=0;
	redkey=0;
	bluekey=0;
	yellowkey=0;
	special=0;
	x=5;
	y=9;
	face=3;
	move=0;
	now_floor=0;
	max_floor=0;
	fly_floor=0;
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
	int special=map_floor[now_floor].getSpecial(x, y);
	if (special==203&&f!=3) return false;
	if (special==204&&f!=1) return false;
	if (special==205&&f!=2) return false;
	if (special==206&&f!=0) return false;
	return map_floor[now_floor].canMove(nextX(), nextY(), f);
}
void c_hero::show()
{
	(new hgeSprite(consts.ht_hero, move*32, face*33, 32, 33))
		->Render(x*32+8*move*dir[0][face]+consts.ScreenLeft, y*32+8*move*dir[1][face]);
}
bool c_hero::nearStair()
{
	if (map_floor[now_floor].getinfo(y, x)->nearStair()) return true;
	if (x>0&&map_floor[now_floor].getinfo(y, x-1)->nearStair()) return true;
	if (y>0&&map_floor[now_floor].getinfo(y-1, x)->nearStair()) return true;
	if (x<consts.map_width-1&&map_floor[now_floor].getinfo(y, x+1)->nearStair()) return true;
	if (y<consts.map_width-1&&map_floor[now_floor].getinfo(y+1, x)->nearStair()) return true;
	return false;
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
		char item=map_floor[now_floor].getItem(x, y);
		if (item>=11&&consts.music)
			consts.hge->Effect_PlayEx(consts.he_GetItem, consts.volume);
		switch (item)
		{
		case 10:
			hp-=100;
			if (hp<=0) hp=1;
			break;
		case 11:atk+=3;
			if (!consts.attack_flag) {
				consts.attack_flag=true;
				consts.setMsg("��ȡ�챦ʯ��������+3");
			}
			break;
		case 12:def+=3;
			if (!consts.defence_flag) {
				consts.defence_flag=true;
				consts.setMsg("��ȡ����ʯ��������+3");
			}
			break;
		case 13:
			consts.book=true;
			consts.setMsg("��ù����ֲᡣ\n����Խ��������ڹ����ϲ�\n������Ļ�����Ϣ�����ϵ���\n����Ϊ��������ơ�Ѫ������\n����������������õĽ��\n�����飬������ɵ��˺���");
			break;
		case 14:
			yellowkey++; bluekey++; redkey++;
			consts.setMsg("��ȡԿ�׺У�ȫԿ������+1");
			break;
		case 15:yellowkey++;
			if (!consts.yellow_flag) {
				consts.yellow_flag=true;
				consts.setMsg("��û�Կ��");
			}
			break;
		case 16:bluekey++;
			if (!consts.blue_flag) {
				consts.blue_flag=true;
				consts.setMsg("�����Կ��");
			}
			break;
		case 17:redkey++;
			if (!consts.red_flag) {
				consts.red_flag=true;
				consts.setMsg("��ú�Կ��");
			}
			break;
		case 18:hp+=200;
			if (!consts.small_flag) {
				consts.small_flag=true;
				consts.setMsg("���СѪƿ������+200");
			}
			break;
		case 19:hp+=500;
			if (!consts.big_flag) {
				consts.big_flag=true;
				consts.setMsg("��ô�Ѫƿ������+500");
			}
			break;
		case 20:atk+=10; consts.setMsg("���������������+10"); break;
		case 21:def+=10; consts.setMsg("������ܣ�������+10"); break;
		case 22:money+=300; consts.setMsg("��ô��ң����+300"); break;
		case 23:lv++; hp+=700; atk+=7; def+=7;
			consts.setMsg("���С��������һ��\n����+700������+7������+7"); break;
		case 24:consts.cross=true;
			consts.setMsg("���ʮ�ּܣ�����0¥������\n���Դ����������������"); break;
		case 25:atk+=70; consts.setMsg("���������������+70"); break;
		case 26:def+=70; consts.setMsg("������ܣ�������+70"); break;
		case 30:hp*=2; consts.setMsg("���ʥˮ������ֵ������"); break;
		case 27:consts.canfly=true; consts.setMsg("���¥�����������F��ʹ��"); break;
		case 28:consts.stick=true; consts.setMsg("��ó�ͷ����Ҫ���������ܿˡ�"); break;
		case 29:lv+=3; hp+=2100; atk+=21; def+=21; consts.setMsg("��ô������������\n����+2100������+21������+21"); break;
		case 31:atk+=150; consts.setMsg("�����ʥ����������+150"); break;
		case 32:def+=150; consts.setMsg("�����ʥ�ܣ�������+150"); break;
		case 33:special=1; consts.setMsg("�ң�\n����ɶ��Ҫ�������˼���һ��\n�ͺ��ˡ�"); break;
		case 34:special=2; consts.setMsg("�ң�\n����ɶ��Ҫ�������˼���һ��\n�ͺ��ˡ�"); break;
		case 35:special=3; consts.setMsg("�ң�\n����ɶ��Ҫ�������˼���һ��\n�ͺ��ˡ�"); break;
		}
		int special=map_floor[now_floor].getSpecial(x, y);
		if (special!=0) {
			if (special==201) {
				map_floor[now_floor].setSpecial(x, y, 202);
			}
			if (special==209) {
				map_floor[now_floor].changeLight(x, y);
			}
			if (special==210||special==211) {
				map_floor[now_floor].setSpecial(x, y, special==210?0:209);
				if (map_floor[now_floor].getSpecial(x+dir[0][face], y+dir[1][face])==0) {
					map_floor[now_floor].setSpecial(x+dir[0][face], y+dir[1][face], 210);
				}
				else if (map_floor[now_floor].getSpecial(x+dir[0][face], y+dir[1][face])==209) {
					map_floor[now_floor].setSpecial(x+dir[0][face], y+dir[1][face], 211);
				}
			}
		}
		if (map_floor[now_floor].checkChallenge())
			map_floor[now_floor].finishChallenge();
		consts.step++;
		if (now_floor==0&&x==5&&y==10) consts.msg=consts.MESSAGE_WIN;
	}
	move++;
	move%=4;
	return c;
}
bool c_hero::openRedDoor()
{
	if (redkey>0)
	{
		redkey--;
		return true;
	}
	return false;
}
bool c_hero::openBlueDoor()
{
	if (bluekey>0)
	{
		bluekey--;
		return true;
	}
	return false;
}
bool c_hero::openYellowDoor()
{
	if (yellowkey>0)
	{
		yellowkey--;
		return true;
	}
	return false;
}
bool c_hero::openSpecialDoor()
{
	if (map_floor[now_floor].getinfo(nextY(), nextX())->canOpen())
		return true;
	return false;
}
void c_hero::upstair()
{
	now_floor++;
	setFlyFloor();
	map_floor[now_floor].getDownPosition(x, y);
	consts.flooring=true;
	consts.step++;
}
void c_hero::downstair()
{
	now_floor--;
	setFlyFloor();
	map_floor[now_floor].getUpPosition(x, y);
	consts.flooring=true;
	consts.step++;
}
void c_hero::specialMove()
{
	consts.flooring=true;
	consts.step++;
	if (now_floor<30) {
		now_floor=31;
		x=10; y=0;
	}
	else {
		now_floor=10;
		x=10; y=0;
	}
}
void c_hero::fly()
{
	if (now_floor<=fly_floor && fly_floor!=0)map_floor[fly_floor].getDownPosition(x, y);
	else map_floor[fly_floor].getUpPosition(x, y);
	now_floor=fly_floor;
	consts.flooring=true;
}
int c_hero::getSpecialLv()
{
	if (lv<=10) return 1;
	if (lv<=20) return 2;
	if (lv<=45) return 3;
	if (lv<=80) return 4;
	return 5;
}
int c_hero::getSpeDef()
{
	int slv=getSpecialLv();
	if (special!=2||slv==1) return 0;
	if (slv==2) return def*0.03;
	if (slv==3) return def*0.06;
	if (slv==4) return def*0.1;
	return def*0.15;
}
int c_hero::getSpeLife(int lf)
{
	int slv=getSpecialLv();
	if (special!=3||slv==1) return 0;
	if (slv==2) return lf*0.2;
	else if (slv==3) return lf*0.33;
	else if (slv==4) return lf*0.5;
	return lf;
}
int c_hero::getSpeAtkTimes()
{
	if (special!=1) return 1;
	return getSpecialLv();
}
void c_hero::printInfo()
{
	int py=16;
	consts.s_storey->Render(16, py);
	if (now_floor<30)
		consts.hgef->printf(60, py, HGETEXT_LEFT, "%d", now_floor);
	else consts.hgef->printf(60, py, HGETEXT_LEFT, "???");
	py+=32;
	consts.s_level->Render(16, py);
	consts.hgef->printf(60, py, HGETEXT_LEFT, "%d", lv);
	if (special!=0) {
		if (special==1)
			consts.s_atk->Render(160, py);
		if (special==2)
			consts.s_def->Render(160, py);
		if (special==3)
			consts.s_life->Render(160, py);
		consts.hgef->printf(204, py, HGETEXT_LEFT, "%d", getSpecialLv());
	}
	py+=32;
	consts.s_heart->Render(16, py);
	consts.hgef->printf(60, py, HGETEXT_LEFT, "%d", hp);
	py+=32;
	consts.s_sword1->Render(16, py);
	consts.hgef->printf(60, py, HGETEXT_LEFT, "%d", atk);
	py+=32;
	consts.s_shield1->Render(16, py);
	if (special!=2)
		consts.hgef->printf(60, py, HGETEXT_LEFT, "%d", def);
	else
		consts.hgef->printf(60, py, HGETEXT_LEFT, "%d (+%d)", def, getSpeDef());
	py+=32;
	consts.s_yellowkey->Render(16, py);
	consts.hgef->printf(60, py, HGETEXT_LEFT, "%d", yellowkey);
	py+=32;
	consts.s_bluekey->Render(16, py);
	consts.hgef->printf(60, py, HGETEXT_LEFT, "%d", bluekey);
	py+=32;
	consts.s_redkey->Render(16, py);
	consts.hgef->printf(60, py, HGETEXT_LEFT, "%d", redkey);
	py+=32;
	consts.s_coin->Render(16, py);
	consts.hgef->printf(60, py, HGETEXT_LEFT, "%d", money);
	py+=32;
	consts.s_expr->Render(16, py);
	consts.hgef->printf(60, py, HGETEXT_LEFT, "%d", experience);

}
bool c_hero::canBeat(c_monster monster) // �ж��ܷ���
{
	return hp>getDamage(monster);
}
int c_hero::getDamage(c_monster monster) // ��ܹ������hp
{
	int monster_def=monster.getSpecial()==2?atk-1:monster.getDef();
	if (atk<=monster_def) return MAX_DAMAGE;
	int val=monster.getSpecial()==1?hp/3:0;
	if (monster.getSpecial()!=3&&getDef()>=monster.getAtk()) return val;
	return val+(monster.getHp()-1)/((atk-monster_def)*getSpeAtkTimes())*(monster.getAtk()-(monster.getSpecial()==3?0:getDef()));
}
bool c_hero::attack(c_monster &monster)
{
	if (consts.music)
		consts.hge->Effect_PlayEx(consts.he_Attack, consts.volume);
	int times=getSpeAtkTimes();
	for (int i=1; i<=times; i++) {
		if (monster.beAttacked(atk))
		{
			money+=monster.getMoney();
			experience+=monster.getExperience();
			return false;
		}
	}
	return true;
}
void c_hero::beAttacked(c_monster monster)
{
	if (monster.getSpecial()==3) hp-=monster.getAtk();
	else if (getDef()<monster.getAtk())
		hp-=monster.getAtk()-getDef();
}
void c_hero::npc(int select)
{
	int npcid=map_floor[now_floor].getinfo(nextY(), nextX())->getNpcID();
	int npctime=map_floor[now_floor].getinfo(nextY(), nextX())->getNpcVisit();
	switch (npcid)
	{
	case 40:
		if (npctime==0)
		{
			const char* npc_hint[50]={
				"���ˣ�\n���ӣ���������Σ�գ�����ô\n�����ˣ�",
				"�ң�\n��Ů���������棬��Ҫ���ȥ\n������",
				"���ˣ�\n�����ɼΣ����б�����ʧ����\n��¥��������ܻ����������\n�ܶ�������������",
				"�ң�\nлл����",
				"���ˣ�\n���⣬�������������ǽ���\n�Ի�����õ��ܶ����õ��鱨\n�ġ�",
				"���ˣ�\n���У�һ��Ҫע����ʱ�浵��"
			};
			consts.setMsg(npc_hint);
			map_floor[now_floor].getinfo(nextY(), nextX())->visitNpc();
		}
		else
			consts.setMsg("���ˣ�\n�������������ǽ��жԻ���\n��õ��ܶ����õ��鱨�ġ�\nͬʱ��һ��Ҫע����ʱ�浵��");
		break;
	case 41:
		if (npctime==0)
		{
			atk+=30;
			map_floor[now_floor].getinfo(nextY(), nextX())->visitNpc();
			consts.setMsg("���ˣ�\n���ӣ���л������ҡ�\n��30�㹥������������ģ�");
		}
		else
			consts.setMsg("���ˣ�\n�������ҵ����۳���100����\nֵ����ͽ��������ֵ�۵�1��");
		break;
	case 42:
		if (npctime==0)
		{
			def+=30;
			map_floor[now_floor].getinfo(nextY(), nextX())->visitNpc();
			consts.setMsg("���ˣ�\n���ӣ���л������ҡ�\n��30���������������ģ�");
		}
		else
			consts.setMsg("���ˣ�\n����ʥˮ��Ҫ����ȥȡ������\n���������ֵ������");
		break;
	case 43:
		if (npctime==0)
		{
			map_floor[2].getinfo(6, 1)->setOpened();
			map_floor[now_floor].getinfo(nextY(), nextX())->visitNpc();
			const char* thief_hint[50]={
				"�ң�\n����˭����ô����Ѻ�����",
				"�ܿˣ�\n�ҽнܿˣ���ס�ڸ�����һ��\n������˵��������б��أ�\n�Ҿͽ����ˣ�����ս����ͱ�\nץ�ˡ�",
				"�ң�\n���أ�ʲô���أ�",
				"�ܿˣ�\n��Ҳֻ����˵... \n����лл������ң�",
				"�ң�\n��Ὺ����",
				"�ܿˣ�\n�ᰡ����ô�ˣ�",
				"�ң�\n�����ܰѶ�¥���Ŵ���",
				"�ܿˣ�\n�õģ������ȥ����򿪣���\n�⣬��������ҵ�����ʧ�ĳ�\nͷ����Ҳ�ܰ����18¥���Ÿ�\n�򿪡�",
				"�ң�\nлл�������ȥ��������ĳ�\nͷ��"
			};
			consts.setMsg(thief_hint);
		}
		else if (npctime==1)
		{
			if (consts.stick) {
				map_floor[18].getinfo(5, 5)->setOpened();
				map_floor[now_floor].getinfo(nextY(), nextX())->visitNpc();
				consts.setMsg("�ܿˣ�\n���ҵ����ҵĳ�ͷ����\n18¥�����Ѿ�Ϊ��򿪡�");
			}
			else {
				consts.setMsg("�ܿˣ�\n��ͷ�ҵ�����");
			}
		}
		else
			consts.setMsg("�ܿˣ�\n����ʲô����");
		break;

	case 44:
		if (npctime==0)
		{
			const char* fairy_hint[50]={
				"�ң�\n������ʲô��ط�����ɭɭ�ģ�\n\n[���س�������]",
				"�ң�\n�������Ů���ѽ�Ա��ʱ��\n����Ϊfor�����Ƿ�ӿո��\n���⣬һ�Բ��ϣ�����Ȼ����\n������...��",
				"�ң�\n�������׷��������������\n���������İ�.....��\n......\n�������������ɣ����ɣ���",
				"���ӣ�\n������˭��Ϊʲô�ܵ������ˣ�",
				"�ң�\n�������ģ���ô��ô��ɭ��\n������˭��",
				"���ӣ�\n��������������ѹ��һ��ħ�\n����������������ӡ�\n�ⲻ��������ĵط�������\nȥ�ɡ�",
				"�ң�\n������ã��㿴����һ��СŮ\n����\n......\n���Ȼ��������ô�ߣ�������",
				"���ӣ�\n�������ˣ����ոճ�������\n�Ҷ�û���ü���ס������",
				"�ң�\n����ȥ�ˣ�����ҲҪ��ȥ������\n",
				"���ӣ�\n����ʱ������Ѿ���ħ��ץ��\n���ˣ��׶༪�٣����ȥҲû\n�õġ�",
				"�ң�\n�����ҵ�Ů���ѣ�\n��һ��Ҫ������ȫ��������\n",
				"���ӣ�\n����������ħ������͵ģ���\n���Ƕ�¥��boss���������ú�\n����",
				"�ң�\n�Ǹ���ô�죿��ô���ܾȳ���\n�أ�",
				"���ӣ�\n������ܰ���¥��ʮ�ּܽ���\n�ң��Ҿ��ܴ������������\n��������������ܾȳ����ˡ�",
				"�ң�\n�ã������ȥ�����һ����ʮ\n�ּܣ�������һ���ܰ�������\n������",
				"���ӣ�\nȥ�ɣ��������㣡ף����ˣ�",
				"S/L: �浵/����\nF: ¥����У����������\nR: ���¿�ʼ\nM: ���ֿ���\nH: �鿴����\nQ: �˳���Ϸ",
				"���ӣ�\n������ĺ��Ӱ�......��"
			};
			consts.setMsg(fairy_hint);
			map_floor[0].getinfo(7, 5)->setOpened();
			map_floor[now_floor].getinfo(nextY(), nextX())->visitNpc();
		}
		else if (npctime==1)
		{
			if (consts.cross) {
				consts.setMsg("���ӣ�\n�ԣ��������ʮ�ּܣ�\n��������...�䣡\n......\nȫ�������25%��\nȥ�ɣ���ֻ�ܰ��㵽�����ˣ�");
				hp=hp*1.25;
				atk=atk*1.25;
				def=def*1.25;
				map_floor[20].getinfo(6, 5)->setOpened();
				map_floor[20].getinfo(7, 4)->setOpened();
				map_floor[20].getinfo(7, 6)->setOpened();
				map_floor[20].getinfo(8, 5)->setOpened();
				map_floor[now_floor].getinfo(nextY(), nextX())->visitNpc();
			}
			else {
				consts.setMsg("���ӣ�\n�ҵ�ʮ�ּ�����");
			}
		}
		else if (consts.lefttime<80) {
			if (consts.trueend) {
				consts.setMsg("���ӣ�\n���߰ɺ��ӣ��ٲ��߾�������\n�ˣ�");
			}
			else {
				consts.trueend=true;
				const char* princess_hint[50]={
					"���ӣ�\n����İ����ȳ����ˣ�",
					"�ң�\nлл���ӣ�������������Ҫ��\n�ˣ��㲻�Ͽ쳷����",
					"���ӣ����ˣ���\n������������������У���ȥ\n�ġ�����Ҫ���ˣ���Ҳ��Ҫȥ\n�ˡ������ɣ�������ʣ�����\nΪ��ף������һ���Ҹ�������",
					"�ң�\n����......",
					"���ӣ�\n���߰ɣ����ǵ�һ�����ܳ���\n��ף�����ǣ�"
				};
				consts.setMsg(princess_hint);
			}
		}
		else consts.setMsg("���ӣ�\n��ֻ�ܰ��㵽�����ˣ����Ͱ�\n��Ů���Ѿȳ����ɣ�");
		break;

	case 45: // The first exp store
		if (select==1&&experience>=100)
		{
			lv++;
			hp+=700;
			atk+=7;
			def+=7;
			experience-=100;
		}
		if (select==2&&experience>=30)
		{
			atk+=5;
			experience-=30;
		}
		if (select==3&&experience>=30)
		{
			def+=5;
			experience-=30;
		}
		break;
	case 46: // The key store
		if (select==1&&money>=10)
		{
			yellowkey++;
			money-=10;
		}
		if (select==2&&money>=50)
		{
			bluekey++;
			money-=50;
		}
		if (select==3&&money>=100)
		{
			redkey++;
			money-=100;
		}
		break;
	case 47: // The first store
		if (select==1&&money>=25)
		{
			hp+=400;
			money-=25;
		}
		if (select==2&&money>=25)
		{
			atk+=4;
			money-=25;
		}
		if (select==3&&money>=25)
		{
			def+=4;
			money-=25;
		}
		break;
	case 48: // The second store
		if (select==1&&money>=100)
		{
			hp+=2000;
			money-=100;
		}
		if (select==2&&money>=100)
		{
			atk+=20;
			money-=100;
		}
		if (select==3&&money>=100)
		{
			def+=20;
			money-=100;
		}
		break;
	case 49: // The second exp store
		if (select==1&&experience>=270)
		{
			experience-=270;
			lv+=3;
			hp+=2100;
			atk+=21;
			def+=21;
		}
		if (select==2&&experience>=95)
		{
			experience-=95;
			atk+=17;
		}
		if (select==3&&experience>=95)
		{
			experience-=95;
			def+=17;
		}
		break;
	case 50: // sell keys store
		if (select==1&&yellowkey>=1)
		{
			yellowkey--;
			money+=7;
		}
		if (select==2&&bluekey>=1)
		{
			bluekey--;
			money+=35;
		}
		if (select==3&&redkey>=1)
		{
			redkey--;
			money+=70;
		}
		break;
	case 51:
		if (npctime==0)
		{
			const char *princess_hint[50]={
				"�ң�\n���ɣ������ҵ����ˣ�\n����Σ�գ�����һ�ȥ��",
				"�ң�\n��������\n...���ɡ�������",
				"����������������\n��������������˭����\n",
				"�ң�\n����˭�����أ�",
				"��������\n�����Ѿ�������ץ������ȥ��\n����ʱ������Ѿ�...",
				"�ң�\n�㣡�������ǣ�����",
				"��������\n������Ļ��ͳ嵽��¥���ɣ�\n�����������һ��ս��",
				"�ң�\n�ã�Ҫս��ս��\n�������������ң��Һܿ����..."
			};
			consts.setMsg(princess_hint);
			map_floor[now_floor].getinfo(nextY(), nextX())->visitNpc();
			map_floor[18].getinfo(10, 9)->setOpened();
		}
		else {
			if (consts.lefttime<80)
				consts.setMsg("��������\n������һ������ɣ���������");
			else
				consts.setMsg("��������\n�������ˣ�����ͱ��������\n�ˣ�");
		}
		break;
	case 52:
		if (npctime==0)
		{
			const char *princess_hint[50]={
				"�ң�\n���ɣ����������������",
				"���ɣ���������\n���������£��㣬����������",
				"�ң�\n�����ˣ����������ˣ�\n��Щħ����û������ô���ɣ�",
				"���ɣ�\n��û��... �һ���....",
				"�ң���������\n�����Ҳ��ã����ú���������\n�Ժ�һ�����鶼����ģ��Ҳ�\n���ٺ���ֿ��ˣ�",
				"���ɣ�\n���������...",
				"�ң�\n�ţ���˵������Ҫ���ˣ��˵�\n���˾��������ǸϿ��߰ɣ�",
				"�ң�\n��������"
			};
			consts.setMsg(princess_hint);
			map_floor[now_floor].getinfo(nextY(), nextX())->visitNpc();
			map_floor[21].getinfo(7, 4)->setOpened();
			map_floor[21].getinfo(7, 6)->setOpened();
			map_floor[0].getinfo(10, 5)->setOpened();
		}
		else consts.setMsg("���ɣ�\n��Ҫ���ˣ����߰ɣ�������\n������");
		break;
	case 53:
		if (npctime==0)
		{
			if (select==1&&experience>=500)
			{
				experience-=500;
				atk+=120;
				map_floor[now_floor].getinfo(nextY(), nextX())->visitNpc();
			}
		}
		else
			consts.setMsg("���ˣ�\nע�ⱸ��Կ�ף�С�Ĳ�����");
		break;
	case 54:
		if (npctime==0)
		{
			if (select==1&&money>=500)
			{
				money-=500;
				def+=120;
				map_floor[now_floor].getinfo(nextY(), nextX())->visitNpc();
			}
		}
		else
			consts.setMsg("���ˣ�\nʮ�ּ���ó嵽17¥ʱ�ٸ���\n�ӣ�̫��Ļ���û�취���ġ�\n��Ȼ������������վ�սǰ��\n��ʮ�ּܸ����ӣ��Ǿ͸�û��\nѹ���ˡ�");
		break;
	case 55:
	{
		const char* npc_hint[50]={
			"���ˣ�\n��Ѫ���ｫ���ȿ۳���1/3��\nѪ��������ս������̹����\n��������Զ����Ĺ�������1��\nħ�����ｫ������ķ���ֵ��",
			"���ˣ�\n������Ѫ���ѪԽ��ɱ����\nЧ��Խ�ã���˿��Ծ�������\nѪƿ������ȥ�ԣ���Ѫ����ʱ\n��ȥɱ����",
			"���ˣ�\n���ڼ�̹����õķ�ʽ��\n�ǡ���ɱ������Ҳ���ǽ����\n�������ӵ���С���乥������\n������������ɱ����",
			"���ˣ�\n����ħ������ҵ��䡰�ٽ�\n�㡱������Ĺ����ӵ������\n���ٽ�㡱֮�ϣ��Ϳ�������\nС������ֵ����ɱ������"
		};
		consts.setMsg(npc_hint);
	}
	break;
	case 56:
	{
		const char* npc_hint[50]={
			"���ˣ�\n����������21�㣬ʵ���Ϸ�Ϊ\n���������֣�1��7��Ϊ��һ��\n�֣�����սʤ������Ϊ�磻8\n��16��Ϊ�ڶ����֣�����սʤ\n����ħ��Ϊ�硣",
			"���ˣ�\n17��21��Ϊ�������֣�����ս\nʤ����bossΪ�硣\n\n���ͣ�"
		};
		consts.setMsg(npc_hint);
	}
	break;
	case 57:
	{
		const char* npc_hint[50]={
			"���ˣ�\n������Ƕ�¥�ˣ�Ҳ��boss��\n���ڵأ���ȥ����²����ˡ�\n�����ȴ������ȥ���������\n�������ԣ��Է������վ�ս��"
		};
		consts.setMsg(npc_hint);
	}
	break;
	case 58:
		consts.setMsg("���ˣ�\n8-12���д���һ�����أ��ҵ�\n������Ȼ�����·���������\n��......");
		break;
	case 61:
	{
		if (npctime==0) {
			const char* npc_hint[50]={
				"���ˣ�\n�㾹Ȼ�ҵ�������ط���",
				"�ң�\n���ã����������ģ�",
				"���ˣ�\n����һ������Ī��ĵط�����\n���˸��ֻ��ء�������ܴ���\nÿһ���������Ҳ��������\n�ĺô��ڵ�����Ŷ��",
				"�ң�\n���������Ҫȥ�����ˣ�",
				"���ˣ�\n��ע�⣬����Щ���ز㣬����\n��ʹ�÷�������¥�ݱ߲��ܴ�\n����һ�����뽫û�л�ͷ·��\n�ߣ����������ؽ���ÿһ����",
				"���ˣ�\n���ﲻ��ʹ�÷�������¥�ݱ�\n���ܴ浵��",
				"���ˣ�\n���ﲻ��ʹ�÷�������¥�ݱ�\n���ܴ浵��\n����Ҫ������˵���飩",
				"�ң�\n����..����֪����..лл����",
				"���ˣ�\n����һ���У��ҵ����а�ǽ��\n��ͨ����"
			};
			consts.setMsg(npc_hint);
			map_floor[now_floor].getinfo(nextY(), nextX())->visitNpc();
			map_floor[now_floor].getinfo(1, 10)->setOpened();
		}
		else consts.setMsg("���ˣ�\n����һ���У��ҵ����а�ǽ��\n��ͨ����");
		break;
	}
	case 62:
		consts.setMsg("���ˣ�\nÿ����ֻ׼ͨ��һ�Σ�������\n�еƼ���ͨ����");
		break;
	case 63:
		consts.setMsg("���ˣ�\n�����Ϸ��3*3�档");
		break;
	case 64:
		consts.setMsg("���ˣ�\n�����Ϸ��4*4�档");
		break;
	case 65:
		consts.setMsg("���ˣ�\n�����������ҵ���ȷ��·�ġ�");
		break;
	case 66:
		consts.setMsg("���ˣ�\n��¥�ϵ�ͼ�����ҷ�ת������");
		break;
	case 67:
		consts.setMsg("���ˣ�\n���¥��¥����һЩ������");
		break;
	case 68:
		consts.setMsg("���ˣ�\n��Ҫ������ɥ�Ĳ���������\n��Ĳ���д�ġ�������");
		break;
	case 69:
		consts.setMsg("���ˣ�\n������5*5�İɡ�\n\n��ʾһ�£���һ��11000��");
		break;
	case 70:
		consts.setMsg("���ˣ�\n��¥�ϵ�ͼ���У����������\n�������³�����ÿ�ν�������\n�һ����������ߣ���ô���ж�\n���ֲ�ͬ���߷���");
		break;
	case 71:
		consts.setMsg("���ˣ�\n�������һ���ˣ��ұ�֤��");
		break;
	case 72:
		if (special==0)
		{
			consts.setMsg("���ˣ�\n��û���õ�¥�ϵġ��¡���");
			break;
		}
		else
		{
			if (npctime==0) {
				if (special==1) {
					const char* npc_hint[50]={
						"���ˣ�\n�������ߵ����ҵ���ǰ������\n���治��",
						"�ң�\n�����ҿ�������¥�ϵõ�����\n����ʲô��",
						"���ˣ�\n����������ǡ�����֮�¡���",
						"�ң�\n����֮�£�",
						"���ˣ�\n����֮�¿���������ÿ�غϵ�\n���������ģ�Ҳ������������\n����˵����������֮�£���ÿ\n�غϴ�������Σ�����Ż��\n��һ�Ρ�",
						"�ң�\n��ô�ã����µĵȼ��ǿ�����\n������",
						"���ˣ�\n��Ȼ���ԣ��µĵȼ�����ĵ�\n���йء�����1-10��ʱ��Ϊ1\n����11-20��ʱ��Ϊ2����21-\n45��ʱ��Ϊ3����46-80��ʱ��\nΪ4����81������ʱ��Ϊ5����",
						"���ˣ�\n����֮���Ǽ�������ÿ�غϾ�\n�����������Ρ�",
						"�ң�\n�õģ�лл�����ҶԾȳ��İ�\n���������Ÿ���İ������ء�",
						"���ˣ�\nȥ�ɣ��㻹�и���Ҫ����Ҫ��\n���Ͽ�ȥ�����İ����˾ȳ���\n�ɡ�"
					};
					consts.setMsg(npc_hint);
				}
				else if (special==2) {
					const char* npc_hint[50]={
						"���ˣ�\n�������ߵ����ҵ���ǰ������\n���治��",
						"�ң�\n�����ҿ�������¥�ϵõ�����\n����ʲô��",
						"���ˣ�\n����������ǡ�����֮�¡���",
						"�ң�\n����֮�£�",
						"���ˣ�\n����֮���ǿ��԰�����������\n�ķ������ġ���������İ���\n֮�£��Ϳ���������3%�ķ���\n����",
						"�ң�\n��ô�ã����µĵȼ��ǿ�����\n������",
						"���ˣ�\n��Ȼ���ԣ��µĵȼ�����ĵ�\n���йء�����1-10��ʱ��Ϊ1\n����11-20��ʱ��Ϊ2����21-\n45��ʱ��Ϊ3����46-80��ʱ��\nΪ4����81������ʱ��Ϊ5����",
						"���ˣ�\nһ���İ���֮����û������Ч\n���ģ������İ���֮������3%\n������������������6%������\n���ļ�������10%����������\n��������15%��������",
						"�ң�\n�õģ�лл�����ҶԾȳ��İ�\n���������Ÿ���İ������ء�",
						"���ˣ�\nȥ�ɣ��㻹�и���Ҫ����Ҫ��\n���Ͽ�ȥ�����İ����˾ȳ���\n�ɡ�"
					};
					consts.setMsg(npc_hint);
				}
				else if (special==3) {
					const char* npc_hint[50]={
						"���ˣ�\n�������ߵ����ҵ���ǰ������\n���治��",
						"�ң�\n�����ҿ�������¥�ϵõ�����\n����ʲô��",
						"���ˣ�\n����������ǡ�����֮�¡���",
						"�ң�\n����֮�£�",
						"���ˣ�\n����֮���ǿ�����ս���󰴱�\n�����չ��������ֵ�ġ�����\n����������֮�¿�����ս����\n����20%�Ĺ���ԭʼ����ֵ��",
						"�ң�\n��ô�ã����µĵȼ��ǿ�����\n������",
						"���ˣ�\n��Ȼ���ԣ��µĵȼ�����ĵ�\n���йء�����1-10��ʱ��Ϊ1\n����11-20��ʱ��Ϊ2����21-\n45��ʱ��Ϊ3����46-80��ʱ��\nΪ4����81������ʱ��Ϊ5����",
						"���ˣ�\nһ��������֮����û������Ч\n���ģ�����������֮������20\n%����ֵ������������33%����\nֵ���ļ�������50%����ֵ��\n�弶������100%����ֵ��",
						"�ң�\n�õģ�лл�����ҶԾȳ��İ�\n���������Ÿ���İ������ء�",
						"���ˣ�\nȥ�ɣ��㻹�и���Ҫ����Ҫ��\n���Ͽ�ȥ�����İ����˾ȳ���\n�ɡ�"
					};
					consts.setMsg(npc_hint);
				}
				map_floor[now_floor].getinfo(nextY(), nextX())->visitNpc();
			}
			else consts.setMsg("���ˣ�\nȥ�ɣ��㻹�и���Ҫ����Ҫ��\n������������ͣ���ˡ�");
		}
		break;
	default:
		consts.setMsg("�ң�\n����ɶ��");
		break;
	}
}
void c_hero::save(FILE* f)
{
	fprintf_s(f, "%d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d\n",
		lv, hp, atk, def, money, experience, redkey, bluekey, yellowkey, special, x, y, face, now_floor, max_floor, fly_floor);
}
void c_hero::load(FILE* f)
{
	fscanf_s(f, "%d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d\n",
		&lv, &hp, &atk, &def, &money, &experience, &redkey, &bluekey, &yellowkey, &special, &x, &y, &face, &now_floor, &max_floor, &fly_floor);
}
void c_hero::setFlyFloor(int delta)
{
	if (delta==0&&now_floor<30)
		fly_floor=now_floor;
	else
	{
		int tmpfloor=fly_floor+delta;
		if (tmpfloor<=max_floor && tmpfloor>=0&&tmpfloor<=20) fly_floor=tmpfloor;
	}
}