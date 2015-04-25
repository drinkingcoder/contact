#ifndef _all_h_
#define _all_h_

//drawtext
void draw_text(int x,int y,char *buf,int size);
extern int Background_Color,Front_Color;

//h
#include<stdio.h>
#include<math.h>
#include<graphics.h>
#include<dos.h>
#include<unistd.h>
#include<time.h>
#include<stdlib.h>
#include<string.h>
#include<bios.h>

//position
#define btn_pgu_lt_x 715 /* 向上按钮坐标  btn=botton pgu=page up lt= left top rd=right down*/
#define btn_pgu_lt_y 30
#define btn_pgu_rd_x 780
#define btn_pgu_rd_y 90

#define btn_pgd_lt_x 715 /* 向下按钮坐标 */
#define btn_pgd_lt_y 525
#define btn_pgd_rd_x 780
#define btn_pgd_rd_y 580

#define btn_add_lt_x 722 /* 插入按钮坐标 */
#define btn_add_lt_y 118
#define btn_add_rd_x 770
#define btn_add_rd_y 155

#define btn_del_lt_x 722 /* 删除按钮坐标 */
#define btn_del_lt_y 183
#define btn_del_rd_x 770
#define btn_del_rd_y 222

#define btn_exp_lt_x 722 /* 导出按钮坐标 exp=export*/
#define btn_exp_lt_y 253
#define btn_exp_rd_x 770
#define btn_exp_rd_y 293

#define btn_imp_lt_x 722 /* 导入按钮坐标 imp=import*/
#define btn_imp_lt_y 320
#define btn_imp_rd_x 770
#define btn_imp_rd_y 362

#define btn_fnd_lt_x 722 /* 查找按钮坐标 */
#define btn_fnd_lt_y 388
#define btn_fnd_rd_x 770
#define btn_fnd_rd_y 430

#define btn_vol_lt_x 722 /* 音效按钮坐标 */
#define btn_vol_lt_y 455
#define btn_vol_rd_x 770
#define btn_vol_rd_y 495

#define c1_lt_x 5
#define c1_lt_y 210
#define c1_rd_x 690
#define c1_rd_y 295

#define c2_lt_x 5
#define c2_lt_y 305
#define c2_rd_x 690
#define c2_rd_y 390

#define c3_lt_x 5
#define c3_lt_y 405
#define c3_rd_x 690
#define c3_rd_y 490

#define c4_lt_x 5
#define c4_lt_y 500
#define c4_rd_x 690
#define c4_rd_y 585

#define btn_badd_lt_x 225 
#define btn_badd_lt_y 325
#define btn_badd_rd_x 340
#define btn_badd_rd_y 360

#define btn_nonadd_lt_x 445
#define btn_nonadd_lt_y 325
#define btn_nonadd_rd_x 560
#define btn_nonadd_rd_y 360

#define btn_bfnd_lt_x 225 
#define btn_bfnd_lt_y 325
#define btn_bfnd_rd_x 340
#define btn_bfnd_rd_y 360

#define btn_nonfnd_lt_x 445
#define btn_nonfnd_lt_y 325
#define btn_nonfnd_rd_x 560
#define btn_nonfnd_rd_y 360

#define btn_sr1_lt_x 230 
#define btn_sr1_lt_y 309
#define btn_sr1_rd_x 345
#define btn_sr1_rd_y 339

#define btn_cl1_lt_x 445
#define btn_cl1_lt_y 309
#define btn_cl1_rd_x 560
#define btn_cl1_rd_y 339

#define btn_sr2_lt_x 230 
#define btn_sr2_lt_y 309
#define btn_sr2_rd_x 345
#define btn_sr2_rd_y 339

#define btn_cl2_lt_x 450
#define btn_cl2_lt_y 309
#define btn_cl2_rd_x 604
#define btn_cl2_rd_y 339

#define btn_sr3_lt_x 230 
#define btn_sr3_lt_y 309
#define btn_sr3_rd_x 345
#define btn_sr3_rd_y 339

#define btn_cl3_lt_x 450
#define btn_cl3_lt_y 309
#define btn_cl3_rd_x 604
#define btn_cl3_rd_y 339

#define insert_name_x 120  
#define insert_gender_x 250
#define insert_birthday_x 320
#define insert_telephone_x 420
#define insert_mail_x 550
#define insert_y 280

#define insert_name_lt_x 115
#define insert_name_lt_y 275  
#define insert_name_rd_x 230  
#define insert_name_rd_y 310    

#define insert_gender_lt_x 245
#define insert_gender_lt_y 275
#define insert_gender_rd_x 295
#define insert_gender_rd_y 310

#define insert_birthday_lt_x 315
#define insert_birthday_lt_y 275
#define insert_birthday_rd_x 405
#define insert_birthday_rd_y 310


#define insert_telephone_lt_x 420
#define insert_telephone_lt_y 275
#define insert_telephone_rd_x 535
#define insert_telephone_rd_y 310

#define insert_mail_lt_x 550
#define insert_mail_lt_y 275
#define insert_mail_rd_x 690
#define insert_mail_rd_y 310

#define notfound_lt_x 360
#define notfound_lt_y 305
#define notfound_rd_x 445
#define notfound_rd_y 335

#define insert_export_lt_x 490
#define insert_export_lt_y 254
#define insert_export_rd_x 570
#define insert_export_rd_y 284


#define insert_export_x 495
#define insert_export_y 259

#define cha1_x 160
#define cha1_y (157+210)
#define cha2_x 160
#define cha2_y (197+210)
#define cha3_x 160
#define cha3_y (237+210)
#define cha4_x 160
#define cha4_y (277+210)
#define pinyin_x 135 
#define pinyin_y 339

#define name_restrict 20
#define email_restrict 30
#define num_restrict 14
#define birth_restrict 14
#define py_restrict 8


//main.c
#define _contacts_length 10000
extern int contacts_num;
extern int Focus,top_num,cha_num;
extern WAVE *sound1,*sound2;
extern MIDI *music;

extern struct contact
{
	char  name[40],email[40],birthday[40],number[40];
	char gender[5];
	byte flag;
} contacts[_contacts_length],editing;

extern enum Status
{
	del,ins,ipt,ept,fin,pgu,pgd,non,nfd,cha
} status,old_status;

extern int pos[4][5][2]={100,265,235,265,300,265,415,265,535,265,
                  100,361,235,361,300,361,415,361,535,361,
                  100,457,235,457,300,457,415,457,535,457,
                  100,550,235,550,300,550,415,550,535,550};

//mouse.c                  
void (far *old_mouse_event_handler)(int event, int x, int y);
int init_mouse(void);
void close_mouse(void);
extern int mousex,mousey,change,impflag,expflag,edit_num,STOP,traflag,deskflag,finflag,soundflag;
void find();

//io.c
void import(char*);
void export(char*);

//checkin.c
int check_up(int x,int y);
int check_down(int x,int y);
int check_add(int x,int y);
int check_del(int x,int y);
int check_exp(int x,int y);
int check_imp(int x,int y);
int check_fnd(int x,int y);
int check_vol(int x,int y);
int check_c1(int x,int y);
int check_c2(int x,int y);
int check_c3(int x,int y);
int check_c4(int x,int y);
int check_sr1(int x,int y);
int check_sr2(int x,int y);
int check_sr3(int x,int y);
int check_cl1(int x,int y);
int check_cl2(int x,int y);
int check_cl3(int x,int y);
int check_bfnd(int x,int y);
int check_nonfnd(int x,int y);
int check_badd(int x,int y);
int check_nonadd(int x,int y);
int check_insert_name(int x,int y);
int check_insert_birthday(int x,int y);
int check_insert_gender(int x,int y);
int check_insert_telephone(int x,int y);
int check_insert_mail(int x,int y);
int check_notfound(int x,int y);
int check_insert_export(int x,int y);

//keyboard.h
void interrupt int_9h(void);

//input.h
extern char cha1[400],cha2[400],cha3[400],cha4[400];
extern char editingpy[20];
void transform(char *s1,int *number);

void q_sort(int l,int r);

void vol_button(WAVE *sound);
void vol_wrong(WAVE *sound);
void bgm(int x,MIDI *sound);

#endif

