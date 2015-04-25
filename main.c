#include <graphics.h>
#include "all.h"
#include "drawtext.c"
#include "mouse.c"
#include "io.c"
#include "checkin.c"
#include "keyboard.c"
#include "input.c"
#include "sound.c"

struct contact contacts[_contacts_length],editing;  //数据储存的数组，以及正在编辑的词条 

int contacts_num=0,top_num=1,Focus=0,timeflag=1,change=1,impflag=0,expflag=0,edit_num=0,STOP=0,traflag=0,deskflag=0,finflag=0, soundflag=1;

WAVE *sound1,*sound2;
MIDI *music;

/*-----------------------------------------------------------------------------------------------------------*/ 
/*contacts_num——联系人数目																				 */
/*top_num——载入视图的第一个联系人的位置 																	 */
/*Focus——视图中选择的窗口编号 																			 */
/* timeflag——时间标志，1表示时间循环了一个周期，0表示还没有到 											 */
/*change——是否需要改变的标志，1表示需要重新画窗口，0表示维持原状											 */
/*imflag——是否需要导入的标志																				 */
/*expflag——是否需要导出的标志																				 */
/*edit_num——当前正在编辑词条的哪一个款项，0,1,2,3,4 分别表示name，gender，number，birthday， Email         */
/*STOP——程序是否结束的标志																				 */
/*traflag——是否需要将输入的拼音转化为中文的标志															 */
/*deskflag——是否需要重载背景的标志																		 */
/* finflag——是否需要查找的标志 																			 */
/*-----------------------------------------------------------------------------------------------------------*/

//WAVE *sound1,*sound2,*music;

enum Status status=non;   //状态的表示 
char cnum[100];

void tide(char *s,int k)  //整理对应的字符串，不让它超出既定的长度 
{
	int l=strlen(s);
	if(l>k)
	{
		s[k-2]='.';
		s[k-1]='.';
		s[k]='\0';
	}
}

void convert() //处理现在有多少个的联系人
{
    int len,k,num;
    memset(cnum,0,sizeof(cnum));
    strcpy(cnum,"已有联系人: ");
    len=strlen(cnum);
    k=1;
    num=contacts_num;
    if(num==0)
    {
        strcpy(cnum+len,"0 人");
        return;
    } 
    while(num/k!=0) k=k*10;
    k=k/10;
    while(k!=0)
    {
        cnum[len++]=(char)(num/k+48);
        num=num%k;
        k=k/10;
    }
    strcpy(cnum+len," 人");
    return;
}

void Drawcontacts()      //将需要显示的四个联系人写到图中 
{
	int i;
	struct contact now;
	Background_Color=WHITE;
	Front_Color=BLACK;	//输出文字的背景颜色和前置颜色的设置 
	if(contacts_num-top_num>=4)
	{
		for(i=top_num;i<top_num+4;i++)
		{
			now=contacts[i];
			tide(now.name,14);
			tide(now.gender,4);
			tide(now.birthday,10);
			tide(now.number,12);
			tide(now.email,15);
			draw_text(pos[i-top_num][0][0],pos[i-top_num][0][1],now.name,1);
			draw_text(pos[i-top_num][1][0],pos[i-top_num][1][1],now.gender,1);
			draw_text(pos[i-top_num][2][0],pos[i-top_num][2][1],now.birthday,1);
			draw_text(pos[i-top_num][3][0],pos[i-top_num][3][1],now.number,1);
			draw_text(pos[i-top_num][4][0],pos[i-top_num][4][1],now.email,1);
		}
	} else
	{
		for(i=top_num;i<=contacts_num;i++)
		{
			now=contacts[i];
			tide(now.name,14);
			tide(now.gender,4);
			tide(now.birthday,10);
			tide(now.number,12);
			tide(now.email,15);
			draw_text(pos[i-top_num][0][0],pos[i-top_num][0][1],now.name,1);
			draw_text(pos[i-top_num][1][0],pos[i-top_num][1][1],now.gender,1);
			draw_text(pos[i-top_num][2][0],pos[i-top_num][2][1],now.birthday,1);
			draw_text(pos[i-top_num][3][0],pos[i-top_num][3][1],now.number,1);
			draw_text(pos[i-top_num][4][0],pos[i-top_num][4][1],now.email,1);
		}
	}
	convert();
	draw_text(100,180,cnum,1);
}

void Drawcontact()  //输出正在编辑的词条，并根据edit_num输出光标位置 
{
	struct contact now=editing;
	int l;
	switch(edit_num)
	{
		case 0:l=strlen(now.name);now.name[l]='_';now.name[l+1]='\0';break;
		case 1:l=strlen(now.gender);now.gender[l]='_';now.gender[l+1]='\0';break;
		case 2:l=strlen(now.birthday);now.birthday[l]='_';now.birthday[l+1]='\0';break;
		case 3:l=strlen(now.number);now.number[l]='_';now.number[l+1]='\0';break;
		case 4:l=strlen(now.email);now.email[l]='_';now.email[l+1]='\0';break;
	}
	draw_text(insert_name_x,insert_y,now.name,1);
	draw_text(insert_birthday_x,insert_y,now.birthday,1);
	draw_text(insert_telephone_x,insert_y,now.number,1);
	draw_text(insert_mail_x,insert_y,now.email,1);
}

void load_desktop() //载入背景桌面 
{
	switch(Focus)	
	{
		case 0:load_8bit_bmp(0,0,"cover.bmp");break;
		case 1:load_8bit_bmp(0,0,"cover1.bmp");break;
		case 2:load_8bit_bmp(0,0,"cover2.bmp");break;
		case 3:load_8bit_bmp(0,0,"cover3.bmp");break;
		case 4:load_8bit_bmp(0,0,"cover4.bmp");break;
	}
}

void drawcharacter() //将输入的拼音和中文写出来 
{
	draw_text(cha1_x,cha1_y,cha1,2);
	draw_text(cha2_x,cha2_y,cha2,2);
	draw_text(cha3_x,cha3_y,cha3,2);
	draw_text(cha4_x,cha4_y,cha4,2);
	draw_text(pinyin_x,pinyin_y,editingpy,1);
}

void DrawDesktop()  //处理所有的画图事项 （根据不同的标记和状态处理） 
{
	if(impflag)
	{
		impflag=0;
		import(editing.name);
		memset(editing.name,0,sizeof(editing.name));
	}
	if(expflag)
	{
		expflag=0;
		export(editing.name);
		memset(editing.name,0,sizeof(editing.name));
	}
	if(traflag)
	{
		transform(editingpy,&cha_num);
		traflag=0;
	}
	if(deskflag)
	{
		deskflag=0;
		load_desktop();
		Drawcontacts();
	}
	if(finflag)
	{
		finflag=0;
		find();
		memset(editing.name,0,sizeof(editing.name));
		memset(editing.gender,0,sizeof(editing.gender));
		memset(editing.email,0,sizeof(editing.email));
		memset(editing.number,0,sizeof(editing.number));
		memset(editing.birthday,0,sizeof(editing.birthday));
	}  
	switch(status)
	{
		case non:load_desktop();Drawcontacts();break;
		case del:load_8bit_bmp(190,229,"delete.bmp");break;
		case ins:if(strcmp(editing.gender,"男")==0) load_8bit_bmp(50,210,"insert1.bmp");
				 else load_8bit_bmp(50,210,"insert2.bmp");Drawcontact();break;
		case fin:if(strcmp(editing.gender,"男")==0) load_8bit_bmp(50,210,"search1.bmp");
				 else load_8bit_bmp(50,210,"search2.bmp");Drawcontact();break;
		case ipt:load_8bit_bmp(190,229,"import.bmp");draw_text(insert_export_x,insert_export_y,editing.name,1);break;
		case ept:load_8bit_bmp(190,229,"export.bmp");draw_text(insert_export_x,insert_export_y,editing.name,1);break;
		case nfd:vol_wrong(sound2);load_8bit_bmp(270,230,"notfound.bmp");break;
		case cha:
				if(old_status==fin)
				{
					if(strcmp(editing.gender,"男")==0) load_8bit_bmp(50,210,"search1.bmp");
					else load_8bit_bmp(50,210,"search2.bmp");
				}
				else if(old_status==ins) 
				{
					if(strcmp(editing.gender,"男")==0) load_8bit_bmp(50,210,"insert1.bmp");
					else load_8bit_bmp(50,210,"insert2.bmp");
				}
				load_8bit_bmp(66+50,111+210,"input.bmp");drawcharacter();Drawcontact();break;
	}
}

void interrupt int_8h(void)  //时间中断，处理timeflag标记 
{
	static int count=0;
	count++;
	if(count==2)
	{
		timeflag=1;
		count=0;
	}	
	outportb(0x20,0x20);
}

int main()
{
	int time1,time2;
	int driver=DETECT,drivermode=VESA_800x600x8bit;
	InterruptFunctionPointer old_8h=getvect(8);
	InterruptFunctionPointer old_9h=getvect(9);
	setvect(8, int_8h);			//时间中断 
	setvect(9,int_9h);			//键盘中断 
	initgraph(&driver,&drivermode,"");
        initsound();
        sound1=load_wave("button.wav");
        sound2=load_wave("wrong.wav");
	DrawDesktop();
	init_mouse();				//鼠标中断 
	DrawDesktop();
	set_timer_frequency(10000);
        music=load_midi("bgm.mid");
        bgm(1,music);
	while(1)
	{
		if(timeflag&&change) 
		{
			DrawDesktop();
			timeflag=0;
			change=0;
		}
		if(STOP) break;
	}
	setvect(8,old_8h);
	setvect(9,old_9h);
        free_wave(sound1);
        free_wave(sound2);
        if(soundflag==1)bgm(0,music);
	close_mouse();
	closegraph();
        closesound();
	export("contacts.csv");
	return 0;
}
