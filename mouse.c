#include "all.h"

#define MOUSE_SIZE               16   // 16*16点
#define MOUSE_MOVE               0x01
#define MOUSE_LEFT_BUTTON_DOWN   0x02
#define MOUSE_LEFT_BUTTON_UP     0x04
#define MOUSE_RIGHT_BUTTON_DOWN  0x08
#define MOUSE_RIGHT_BUTTON_UP    0x10
#define MOUSE_MIDDLE_BUTTON_DOWN 0x20
#define MOUSE_MIDDLE_BUTTON_UP   0x40

/*---------------------------------------------------------------------------*/
/*这个文件处理所有鼠标相关事宜，包括点击区域不同的事件响应，与键盘相对应 	 */
/*---------------------------------------------------------------------------*/

word screen_mask[] =
{
   /* 16 words of screen mask */
   0x3FFF, /*0011111111111111*/
   0x1FFF, /*0001111111111111*/
   0x0FFF, /*0000111111111111*/
   0x07FF, /*0000011111111111*/
   0x03FF, /*0000001111111111*/
   0x01FF, /*0000000111111111*/
   0x00FF, /*0000000011111111*/
   0x007F, /*0000000001111111*/
   0x01FF, /*0000000111111111*/
   0x10FF, /*0001000011111111*/
   0xB0FF, /*1011000011111111*/
   0xF87F, /*1111100001111111*/
   0xF87F, /*1111100001111111*/
   0xFC3F, /*1111110000111111*/
   0xFC3F, /*1111110000111111*/
   0xFE1F, /*1111111000011111*/
};

word cursor_mask[] =
{
   /* 16 words of cursor mask */
   0x0000, /*0000000000000000*/
   0x4000, /*0100000000000000*/
   0x6000, /*0110000000000000*/
   0x7000, /*0111000000000000*/
   0x7800, /*0111100000000000*/
   0x7C00, /*0111110000000000*/
   0x7E00, /*0111111000000000*/
   0x7F00, /*0111111100000000*/
   0x7C00, /*0111110000000000*/
   0x4600, /*0100011000000000*/
   0x0600, /*0000011000000000*/
   0x0300, /*0000001100000000*/
   0x0300, /*0000001100000000*/
   0x0180, /*0000000110000000*/
   0x0180, /*0000000110000000*/
   0x00C0, /*0000000011000000*/
};
/*	这两个二维数组为鼠标的形状设定	*/ 
struct 
{
   int x, y;
   struct picture *old_img;
   struct picture *mask;
   struct picture *img;
} mouse;

int f[100][100];//作临时变量用，不必理会 

int  init_mouse(void);
void draw_mouse(int x, int y);
void recover_mouse_background(void);
void save_mouse_background(int x, int y);
void move_mouse(int x, int y);
void __loadds far mouse_event_handler(int event, int x, int y);
void expand_mask_to_image(word m[16], byte *p, byte color, int width, int height);
void build_mouse_image(void);
void (far *old_mouse_event_handler)(int event, int x, int y);
volatile int stop = 0;

int mousex=0,mousey=0;

void solve_non()	//当前状态为non时遇到鼠标事件的处理 
{
	change=1;
	if(check_c1(mousex,mousey)) //鼠标点击到第一个框的感应区域 
	{
		Focus=1;
		return;
	}
	if(check_c2(mousex,mousey)) //鼠标点击到第二个框的感应区域
	{
		Focus=2;
		return;
	}
	if(check_c3(mousex,mousey)) //鼠标点击到第三个框的感应区域
	{
		Focus=3;
		return;
	}
	if(check_c4(mousex,mousey))//鼠标点击到第四个框的感应区域
	{
		Focus=4;
		return;
	}
	if(check_up(mousex,mousey))//鼠标点击到方向框上的感应区域
	{
		if(Focus>1) Focus--;
		else if(top_num>1) top_num--;
		return;
	}
	if(check_down(mousex,mousey))//鼠标点击到方向框下的感应区域
	{
		if(Focus<4) Focus++;
		else if(top_num<contacts_num) top_num++;
		return;
	}
	if(check_add(mousex,mousey))//鼠标点击到功能框添加的感应区域
	{
		status=ins;
		strcpy(editing.gender,"男");
		return;
	}
	if(check_del(mousex,mousey))//鼠标点击到功能框删除的感应区域
	{
		status=del;
		return;
	}
	if(check_exp(mousex,mousey))//鼠标点击到功能框导出的感应区域
	{
		status=ept;
		return;
	}
	if(check_imp(mousex,mousey))//鼠标点击到功能框导入的感应区域
	{
		status=ipt;
		return;
	}
	if(check_fnd(mousex,mousey))//鼠标点击到功能框查找的感应区域
	{
		status=fin;
		strcpy(editing.gender,"男");
		return;
	}
	if(check_vol(mousex,mousey))//鼠标点击到功能框退出的感应区域
	{
		STOP=1;
		return;
	}
	change=0;
}

void solve_ins()	//当前状态为ins时遇到鼠标事件的处理
{
	if(check_badd(mousex,mousey))//鼠标点击到确定框的感应区域，将编辑的内容添加到contacts表中，并初始化editing 
	{
		contacts_num++;
		strcpy(contacts[contacts_num].name,editing.name);
		strcpy(contacts[contacts_num].email,editing.email);
		strcpy(contacts[contacts_num].number,editing.number);
		strcpy(contacts[contacts_num].gender,editing.gender);
		strcpy(contacts[contacts_num].birthday,editing.birthday);
		memset(editing.name,0,sizeof(editing.name));
		memset(editing.gender,0,sizeof(editing.gender));
		memset(editing.email,0,sizeof(editing.email));
		memset(editing.number,0,sizeof(editing.number));
		memset(editing.birthday,0,sizeof(editing.birthday));
		edit_num=0;
		status=non;
		change=1;
		q_sort(0,contacts_num);
		return;
	}
	if(check_nonadd(mousex,mousey))//鼠标点击到取消框的感应区域， 不添加编辑内容，仍初始化editing 
	{
		status=non;
		change=1;
		memset(editing.name,0,sizeof(editing.name));
		memset(editing.gender,0,sizeof(editing.gender));
		memset(editing.email,0,sizeof(editing.email));
		memset(editing.number,0,sizeof(editing.number));
		memset(editing.birthday,0,sizeof(editing.birthday));
		edit_num=0;
		return;
	}
	if(check_insert_name(mousex,mousey)) //鼠标点击到编辑框姓名的感应区域
	{
		edit_num=0;
		change=1;
		return;
	}
	if(check_insert_birthday(mousex,mousey))  //鼠标点击到编辑框生日的感应区域
	{
		edit_num=2;
		change=1;
		return;
	}
	if(check_insert_gender(mousex,mousey))  //鼠标点击到编辑框性别的感应区域
	{
		if(strcmp(editing.gender,"男")==0)
			strcpy(editing.gender,"女");
		else strcpy(editing.gender,"男");
		change=1;
		return;
	}
	if(check_insert_telephone(mousex,mousey)) //鼠标点击到编辑手机号的感应区域
	{
		edit_num=3;
		change=1;
		return;
	}
	if(check_insert_mail(mousex,mousey))  //鼠标点击到编辑框邮箱的感应区域
	{
		edit_num=4;
		change=1;
		return;
	}
	vol_wrong(sound2);
}

void solve_del()	//当前状态为del时遇到鼠标事件的处理
{
	int i;
	if(check_sr1(mousex,mousey)) //鼠标点击到确定框的感应区域，删除掉指定的联系人 
	{
		if(top_num+Focus-1>contacts_num)
		{
			status=non;
			change=1;
			return;
		}
		for(i=top_num+Focus-1;i<contacts_num;i++)
		{
			strcpy(contacts[i].name,contacts[i+1].name);
			strcpy(contacts[i].email,contacts[i+1].email);
			strcpy(contacts[i].number,contacts[i+1].number);
			strcpy(contacts[i].gender,contacts[i+1].gender);
			strcpy(contacts[i].birthday,contacts[i+1].birthday);
		}
		contacts_num--;
		status=non;
		change=1;
		return;
	}
	if(check_cl1(mousex,mousey)) //鼠标点击到取消框的感应区域，不做事情 
	{
		status=non;
		change=1;
		return;
	}
	vol_wrong(sound2);
}

void solve_ipt()//当前状态为ipt时遇到鼠标事件的处理
{
	if(check_sr1(mousex,mousey)) //鼠标点击到确定框的感应区域，改动impflag标记 
	{
		status=non;
		impflag=1;
		change=1;
		return;
	}
	if(check_cl1(mousex,mousey)) //鼠标点击到取消框的感应区域，editing.name清零 
	{
		status=non;
		memset(editing.name,0,sizeof(editing.name));
		change=1;
		return;
	}
	vol_wrong(sound2);
}

void solve_ept()	//当前状态为ept时遇到鼠标事件的处理
{
	if(check_sr1(mousex,mousey))//鼠标点击到确定矿的感应区域，expflag改动 
	{
		status=non;
		expflag=1;
		change=1;
		return;
	}
	if(check_cl1(mousex,mousey))
	{
		status=non;
		memset(editing.name,0,sizeof(editing.name)); //鼠标点击到取消框的感应区域，editing.name清零
		change=1;
		return;
	}
	vol_wrong(sound2);
}

int compare(char *s1,char* s2)	//比较两个字符串s1，s2的相似度，利用LCS算法处理 
{
	int l1=strlen(s1),l2=strlen(s2),i,j;
	memset(f,0,sizeof(f));
	if(l1==0||l2==0) return 0;
	for(i=0;i<l1;i++)
		for(j=0;j<l2;j++)
		{
			if(i==0||j==0)
			{
				if(s1[i]==s2[j]) f[i][j]=1;
				else f[i][j]=0;
				continue;
			}
			if(s1[i]==s2[j])
				f[i][j]=f[i-1][j-1]+1;
			else if(f[i-1][j]>f[i][j-1]) f[i][j]=f[i-1][j];
			else f[i][j]=f[i][j-1];
		}
	return f[l1-1][l2-1];
}

void find()		//查找处理，用LCS的值为权值，从当前状态往下搜索匹配值最高的为选定项 
{
	int i,j,k,start=top_num+Focus,max=0,mark=-1;
	char s[100],ss[100];
	memset(s,0,sizeof(s));
	j=k=0;
	for(k=0;k<strlen(editing.name);k++)
		s[j++]=editing.name[k];
	for(k=0;k<strlen(editing.number);k++)
		s[j++]=editing.number[k];
	for(k=0;k<strlen(editing.email);k++)
		s[j++]=editing.email[k];
	for(k=0;k<strlen(editing.birthday);k++)
		s[j++]=editing.birthday[k];
	for(i=start;i<=contacts_num;i++)
	{
		memset(ss,0,sizeof(ss));
		j=k=0;
		for(k=0;k<strlen(contacts[i].name);k++)
			ss[j++]=contacts[i].name[k];
		for(k=0;k<strlen(contacts[i].number);k++)
			ss[j++]=contacts[i].number[k];
		for(k=0;k<strlen(contacts[i].email);k++)
			ss[j++]=contacts[i].email[k];
		for(k=0;k<strlen(contacts[i].birthday);k++)
			ss[j++]=contacts[i].birthday[k];
		k=compare(s,ss);
		if(k>max)
		{
			max=k;
			mark=i;
		}
	}
	if(mark==-1)
	{
		status=nfd;
		return;
	}
	top_num=mark;
	Focus=1;
}


void solve_fin()	//当前状态为fin时遇到鼠标事件的处理
{
	if(check_badd(mousex,mousey)) //鼠标点击到确定框的感应区域，finflag标志改动，准备进行查找 
	{
		finflag=1;
		status=non;
		edit_num=0;
		change=1;
		return;
	}
	if(check_nonadd(mousex,mousey)) //鼠标点击到取消框的感应区域，editing清零 
	{
		status=non;
		memset(editing.name,0,sizeof(editing.name));
		memset(editing.gender,0,sizeof(editing.gender));
		memset(editing.email,0,sizeof(editing.email));
		memset(editing.number,0,sizeof(editing.number));
		memset(editing.birthday,0,sizeof(editing.birthday));
		edit_num=0;
		change=1;
		return;
	}
	if(check_insert_name(mousex,mousey)) //一下几个感应同插入时的感应，两个的处理大致相同 
	{
		edit_num=0;
		change=1;
		return;
	}
	if(check_insert_birthday(mousex,mousey)) 
	{
		edit_num=2;
		change=1;
		return;
	}
	if(check_insert_gender(mousex,mousey)) 
	{
		if(strcmp(editing.gender,"男")==0)
			strcpy(editing.gender,"女");
		else strcpy(editing.gender,"男");
		change=1;
		return;
	}
	if(check_insert_telephone(mousex,mousey))
	{
		edit_num=3;
		change=1;
		return;
	}
	if(check_insert_mail(mousex,mousey)) 
	{
		edit_num=4;
		change=1;
		return;
	}
	vol_wrong(sound2);
}

void solve_nfd()	//当前状态为nfd时遇到鼠标事件的处理（即查找找不到时的提示框） 
{
	if(check_notfound(mousex,mousey)) //鼠标点击到确定框的感应区域
	{
		status=non;
		change=1;
		return;
	}
	vol_wrong(sound2);
}

void solve_mouse()	//鼠标点击时的处理 
{    
   #pragma aux mouse_event_handler parm [EAX] [ECX] [EDX];
   	switch(status)
   	{
   		case non:solve_non();break;
   		case ins:solve_ins();break;
   		case del:solve_del();break;
   		case ipt:solve_ipt();break;
   		case ept:solve_ept();break;
   		case fin:solve_fin();break;
   		case nfd:solve_nfd();break;
   		default:break;
   	}
}

void __loadds far mouse_event_handler(int event, int x, int y) //鼠标中断，只处理移动和点击两个事件 
{
   #pragma aux mouse_event_handler parm [EAX] [ECX] [EDX];
   if(event & MOUSE_MOVE)
   {
      move_mouse(x, y);
   }
   else if(event & MOUSE_LEFT_BUTTON_UP)
   {
      recover_mouse_background();
      save_mouse_background(x,y);
      draw_mouse(x,y);
      mouse.x=x;
      mouse.y=y;
      solve_mouse();
   }
}

void expand_mask_to_image(word m[16], byte *p, byte color, int width, int height)	//将数组中的数据画出来 
{
   int i, j;
   for(i=0; i<height; i++)
   {
      for(j=0; j<width; j++)
      {
         if(m[i] & 1<<(width-1-j))
            p[i*width+j] = color;
         else
            p[i*width+j] = 0x00;
      }
   }
}

void build_mouse_image(void)	//建立鼠标的图形 
{
   mouse.old_img = malloc(imagesize(0, 0, MOUSE_SIZE-1, MOUSE_SIZE-1));
   mouse.mask = malloc(imagesize(0, 0, MOUSE_SIZE-1, MOUSE_SIZE-1)); 
   mouse.img = malloc(imagesize(0, 0, MOUSE_SIZE-1, MOUSE_SIZE-1));
   mouse.mask->picwidth = mouse.mask->picheight = MOUSE_SIZE;
   mouse.img->picwidth = mouse.img->picheight = MOUSE_SIZE;
   expand_mask_to_image(screen_mask, &mouse.mask->buffer, 0xFF, MOUSE_SIZE, MOUSE_SIZE);
   expand_mask_to_image(cursor_mask, &mouse.img->buffer, WHITE, MOUSE_SIZE, MOUSE_SIZE);   
}

void save_mouse_background(int x, int y)	//保存鼠标所在地的背景 
{
   getimage(x, y, x+MOUSE_SIZE-1, y+MOUSE_SIZE-1, mouse.old_img);
   mouse.x = x;
   mouse.y = y;
}

void draw_mouse(int x, int y)	//在指定位置画出鼠标 
{
   putimage(x, y, mouse.mask, AND_PUT);
   putimage(x, y, mouse.img, OR_PUT);
}

void recover_mouse_background(void)//恢复鼠标占据地方的背景 
{
   putimage(mouse.x, mouse.y, mouse.old_img, COPY_PUT);
}

void move_mouse(int x, int y)	//鼠标移动时的处理，恢复背景，然后在移动处新画一个鼠标 
{
   recover_mouse_background();
   save_mouse_background(x, y);
   draw_mouse(x, y);
   mousex=x;
   mousey=y;
}

int init_mouse(void)	//鼠标初始化，开启鼠标 
{
   int x=mousex, y=mousey;
   union REGS r;
   struct SREGS sr;

   r.w.ax = 0;      /* check mouse driver */
   int86(0x33, &r, &r);
   if(r.w.ax != 0xFFFF)
      return 0;

   r.w.ax = 0x0007; /* set horizontal range */
   r.w.cx = 0;
   r.w.dx = _width-1;
   int86(0x33, &r, &r);
   r.w.ax = 0x0008; /* set vertical range */
   r.w.cx = 0;
   r.w.dx = _height-1;
   int86(0x33, &r, &r);

   r.w.ax = 0x0004; /* position cursor */
   r.w.cx = x;
   r.w.dx = y;
   int86(0x33, &r, &r);

   r.w.ax = 2;      /* hide cursor */
   int86(0x33, &r, &r);

   r.w.ax = 0x0014; /* install mouse event handler */
   r.w.cx = MOUSE_MOVE | MOUSE_LEFT_BUTTON_DOWN | MOUSE_LEFT_BUTTON_UP |
            MOUSE_RIGHT_BUTTON_DOWN | MOUSE_RIGHT_BUTTON_UP; /* monitor these events */
   r.x.edx = FP_OFF(mouse_event_handler);
   memset(&sr, 0, sizeof(sr));
   sr.es   = FP_SEG(mouse_event_handler);
   int86x(0x33, &r, &r, &sr);
   old_mouse_event_handler = MK_FP(sr.es, r.x.edx);
   build_mouse_image();
   save_mouse_background(x, y);   
   move_mouse(x, y);
   return 1;
}

void close_mouse(void)
{
   union REGS r;
   struct SREGS sr;
   r.w.ax = 0x0014; /* install mouse event handler */
   r.w.cx = 0;      // DO NOT monitor any events!!!
   r.x.edx = FP_OFF(old_mouse_event_handler);
   memset(&sr, 0, sizeof(sr));
   sr.es   = FP_SEG(old_mouse_event_handler);
   int86x(0x33, &r, &r, &sr);
   free(mouse.old_img);
   free(mouse.mask);
   free(mouse.img);
}

