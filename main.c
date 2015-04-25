#include <graphics.h>
#include "all.h"
#include "drawtext.c"
#include "mouse.c"
#include "io.c"
#include "checkin.c"
#include "keyboard.c"
#include "input.c"
#include "sound.c"

struct contact contacts[_contacts_length],editing;  //���ݴ�������飬�Լ����ڱ༭�Ĵ��� 

int contacts_num=0,top_num=1,Focus=0,timeflag=1,change=1,impflag=0,expflag=0,edit_num=0,STOP=0,traflag=0,deskflag=0,finflag=0, soundflag=1;

WAVE *sound1,*sound2;
MIDI *music;

/*-----------------------------------------------------------------------------------------------------------*/ 
/*contacts_num������ϵ����Ŀ																				 */
/*top_num����������ͼ�ĵ�һ����ϵ�˵�λ�� 																	 */
/*Focus������ͼ��ѡ��Ĵ��ڱ�� 																			 */
/* timeflag����ʱ���־��1��ʾʱ��ѭ����һ�����ڣ�0��ʾ��û�е� 											 */
/*change�����Ƿ���Ҫ�ı�ı�־��1��ʾ��Ҫ���»����ڣ�0��ʾά��ԭ״											 */
/*imflag�����Ƿ���Ҫ����ı�־																				 */
/*expflag�����Ƿ���Ҫ�����ı�־																				 */
/*edit_num������ǰ���ڱ༭��������һ�����0,1,2,3,4 �ֱ��ʾname��gender��number��birthday�� Email         */
/*STOP���������Ƿ�����ı�־																				 */
/*traflag�����Ƿ���Ҫ�������ƴ��ת��Ϊ���ĵı�־															 */
/*deskflag�����Ƿ���Ҫ���ر����ı�־																		 */
/* finflag�����Ƿ���Ҫ���ҵı�־ 																			 */
/*-----------------------------------------------------------------------------------------------------------*/

//WAVE *sound1,*sound2,*music;

enum Status status=non;   //״̬�ı�ʾ 
char cnum[100];

void tide(char *s,int k)  //�����Ӧ���ַ����������������ȶ��ĳ��� 
{
	int l=strlen(s);
	if(l>k)
	{
		s[k-2]='.';
		s[k-1]='.';
		s[k]='\0';
	}
}

void convert() //���������ж��ٸ�����ϵ��
{
    int len,k,num;
    memset(cnum,0,sizeof(cnum));
    strcpy(cnum,"������ϵ��: ");
    len=strlen(cnum);
    k=1;
    num=contacts_num;
    if(num==0)
    {
        strcpy(cnum+len,"0 ��");
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
    strcpy(cnum+len," ��");
    return;
}

void Drawcontacts()      //����Ҫ��ʾ���ĸ���ϵ��д��ͼ�� 
{
	int i;
	struct contact now;
	Background_Color=WHITE;
	Front_Color=BLACK;	//������ֵı�����ɫ��ǰ����ɫ������ 
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

void Drawcontact()  //������ڱ༭�Ĵ�����������edit_num������λ�� 
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

void load_desktop() //���뱳������ 
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

void drawcharacter() //�������ƴ��������д���� 
{
	draw_text(cha1_x,cha1_y,cha1,2);
	draw_text(cha2_x,cha2_y,cha2,2);
	draw_text(cha3_x,cha3_y,cha3,2);
	draw_text(cha4_x,cha4_y,cha4,2);
	draw_text(pinyin_x,pinyin_y,editingpy,1);
}

void DrawDesktop()  //�������еĻ�ͼ���� �����ݲ�ͬ�ı�Ǻ�״̬���� 
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
		case ins:if(strcmp(editing.gender,"��")==0) load_8bit_bmp(50,210,"insert1.bmp");
				 else load_8bit_bmp(50,210,"insert2.bmp");Drawcontact();break;
		case fin:if(strcmp(editing.gender,"��")==0) load_8bit_bmp(50,210,"search1.bmp");
				 else load_8bit_bmp(50,210,"search2.bmp");Drawcontact();break;
		case ipt:load_8bit_bmp(190,229,"import.bmp");draw_text(insert_export_x,insert_export_y,editing.name,1);break;
		case ept:load_8bit_bmp(190,229,"export.bmp");draw_text(insert_export_x,insert_export_y,editing.name,1);break;
		case nfd:vol_wrong(sound2);load_8bit_bmp(270,230,"notfound.bmp");break;
		case cha:
				if(old_status==fin)
				{
					if(strcmp(editing.gender,"��")==0) load_8bit_bmp(50,210,"search1.bmp");
					else load_8bit_bmp(50,210,"search2.bmp");
				}
				else if(old_status==ins) 
				{
					if(strcmp(editing.gender,"��")==0) load_8bit_bmp(50,210,"insert1.bmp");
					else load_8bit_bmp(50,210,"insert2.bmp");
				}
				load_8bit_bmp(66+50,111+210,"input.bmp");drawcharacter();Drawcontact();break;
	}
}

void interrupt int_8h(void)  //ʱ���жϣ�����timeflag��� 
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
	setvect(8, int_8h);			//ʱ���ж� 
	setvect(9,int_9h);			//�����ж� 
	initgraph(&driver,&drivermode,"");
        initsound();
        sound1=load_wave("button.wav");
        sound2=load_wave("wrong.wav");
	DrawDesktop();
	init_mouse();				//����ж� 
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
