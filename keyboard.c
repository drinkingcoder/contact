#include <graphics.h>
#include "all.h"

#define key_a 0x1E
#define key_b 0x30
#define key_c 0x2E
#define key_d 0x20
#define key_e 0x12
#define key_f 0x21
#define key_g 0x22
#define key_h 0x23
#define key_i 0x17
#define key_j 0x24
#define key_k 0x25
#define key_l 0x26
#define key_m 0x32
#define key_n 0x31
#define key_o 0x18
#define key_p 0x19
#define key_q 0x10
#define key_r 0x13
#define key_s 0x1F
#define key_t 0x14
#define key_u 0x16
#define key_v 0x2F
#define key_w 0x11
#define key_x 0x2D
#define key_y 0x15
#define key_z 0x2C

#define key_0 0x0B
#define key_1 0x02
#define key_2 0x03
#define key_3 0x04
#define key_4 0x05
#define key_5 0x06
#define key_6 0x07
#define key_7 0x08
#define key_8 0x09
#define key_9 0x0A

#define key_point 0x34
#define key_tab 0x0F

#define key_shift 0x2A
#define key_space 0x39
#define key_backspace 0x0E
#define key_up 0x48
#define key_down 0x50
#define key_left 0x4B
#define key_right 0x4D
#define key_esc 0x01
#define key_del 0x53
#define key_ctl 0x1D
#define key_ent 0x1C
#define key_alt 0x38

/*----------------------------------------------------------------*/
/*����ļ��������еļ����������								  */
/*����Ϊ�궨�岻ͬ�ļ�ֵ��������ĳ�����һһ��ӦΪascii�� 		  */
/*----------------------------------------------------------------*/

enum Status old_status=non; //����status��ǰһ��״̬ 
int cha_num=1;				//
char editingpy[20];			//���ڱ༭��ƴ�� 

void clr_editingpy()		//����ƴ���ͺ���������ص����ݳ�ʼ�� 
{
	memset(editingpy,0,sizeof(editingpy));
	memset(cha1,0,sizeof(cha1));
	memset(cha2,0,sizeof(cha2));
	memset(cha3,0,sizeof(cha3));
	memset(cha4,0,sizeof(cha4));
	cha_num=1;
}

void appends(char *s,unsigned char key,int res)	//���ַ�key������ַ���s��β�������Ȳ�����res 
{
	int l=strlen(s);
	if(key=='\b')
	{
		if(l>0)
		{
			l--;
			if(s[l]&(1<<7)) l--; //�����ж���Ҫɾ���������Ļ���Ӣ�ģ�����ռ�����ֽ���Ҫɾ�������ֽ� 
			s[l]='\0';
			return;
		} else return;
	}
	if(key=='\t')				//tab��ʵ���ڼ���������ڵ��л� 
	{
		edit_num=(edit_num+1)%5;
		return;
	}
	if(l==res) return;
	s[l]=key;					//������������������ܼ�����ֱ�ӽ���ǰ����ַ������ڱ༭�ַ����ĺ��� 
	s[l+1]='\0';
}

void solve_cha_trans(unsigned char key)	//�ж϶����������������״̬ ��' '/'1'/'2'/'3'/'4'��ʾ�����ı��е����ĵ�ѡ�� 
{
	switch(key)	//�����жϵ�ǰ���µļ��ǲ��Ƕ��ַ���ѡ���������ѡ��������ַ��������ֽڣ� ��������ڱ༭���ַ����ĺ��� 
		{
			case ' ':
		    case '1':
				appends(editing.name,cha1[0],name_restrict);
				appends(editing.name,cha1[1],name_restrict);
				change=1;
				clr_editingpy();
				return;
			case '2':
				appends(editing.name,cha2[0],name_restrict);
				appends(editing.name,cha2[1],name_restrict);
				clr_editingpy();
				change=1;
				return;
			case '3':
				appends(editing.name,cha3[0],name_restrict);
				appends(editing.name,cha3[1],name_restrict);
				clr_editingpy();
				change=1;
				return;
			case '4':
				appends(editing.name,cha4[0],name_restrict);
				appends(editing.name,cha4[1],name_restrict);
				clr_editingpy();
				change=1;
				return;
		}
		if(key>='a'&&key<='z'||key>='A'&&key<='Z'||key=='\b')	//������Ƕ������ַ���ѡ�񣬾��Ƕ�����ƴ����ֵ��ά��������ά�������ƴ�����ض���26����ĸ�е�һ�� ��ʶ���Сд��ת�� 
		{
			if(key>='A'&&key<='Z') key=key+32;  //��Сдʶ��ת�� 
			if(key=='\b'&&strlen(editingpy)==0) appends(editing.name,key,name_restrict);
			else appends(editingpy,key,py_restrict);
			traflag=1;
			change=1;
		}
}

void solve_9h(unsigned char key)	//����ASCII��ֵkey����������������� 
{
	if(status==cha)	//ʶ��ǰ״̬�������ڱ༭���ģ������⴦�� 
	{
		solve_cha_trans(key);
		return;
	}
    if(status!=ins&&status!=fin&&status!=ipt&&status!=ept) return; //�༭ֻ���⼸��״̬�³��֣���������⼸��״̬����������Ч 
    switch(edit_num)	//ʶ��ǰ���ڱ༭��һ�Ȼ��ֱ��� 
    {
    	case 0:appends(editing.name,key,name_restrict);break;
    	case 1:if(key=='\t') appends(editing.gender,key,4);break;
    	case 2:if(key<='9'&&key>='0'||key=='\t'||key=='\b'||key=='.') appends(editing.birthday,key,birth_restrict);break;
    	case 3:if(key<='9'&&key>='0'||key=='\t'||key=='\b') appends(editing.number,key,num_restrict);break;
    	case 4:appends(editing.email,key,email_restrict);break;
    }
    change=1;
}

void solve_up()	//���û����·�������� ���Ĵ�������״̬������Ч��һ����non��һ����cha���ֱ��� 
{
	if(status==cha)
	{
		cha_num=cha_num-4;
		traflag=1;
		change=1;
		return;
	}
	if(status==ins||status==fin)
	{
		if(edit_num==1)
		{
			if(strcmp(editing.gender,"��")==0) strcpy(editing.gender,"Ů");
			else strcpy(editing.gender,"��");
		}
		change=1;
		return;
	}
	if(status==non)//�ж�ѡ������ܶ���Focus������һ��������top_num��һ�������жϿ��ܳ��ֵĴ�����д��� 
	{
		if(Focus>1) Focus--;
					else if(top_num>1) top_num--;change=1;
	}
}

void solve_down()	//���û����·�������� ���Ĵ�������״̬������Ч��һ����non��һ����cha���ֱ��� 
{
	if(status==cha)
	{
		cha_num=cha_num+4;
		traflag=1;
		change=1;
		return;
	}
	if(status==ins||status==fin)
	{
		if(edit_num==1)
		{
			if(strcmp(editing.gender,"��")==0) strcpy(editing.gender,"Ů");
			else strcpy(editing.gender,"��");
		}
		change=1;
		return;
	}
	if(status==non)//�ж�ѡ������ܶ���Focus������һ��������top_num��һ�������жϿ��ܳ��ֵĴ�����д���
	{
		if(Focus<4) Focus++;
		else if(top_num<contacts_num) top_num++; change=1;
	}
}

void solve_esc()//esc�������⴦�� �����ݲ�ͬ��״̬������������ͬ״̬ 
{
	if(status==cha)
	{
		status=old_status;
		deskflag=1;
		change=1;
		memset(editingpy,0,sizeof(editingpy));
		return;
	}
	if(status==non)
	{
		STOP=1;
		return;
	}
	if(status==nfd)
	{
		status=non;
		change=1;
		return;
	}
	status=non;
	memset(editing.name,0,sizeof(editing.name));
	memset(editing.gender,0,sizeof(editing.gender));
	memset(editing.email,0,sizeof(editing.email));
	memset(editing.number,0,sizeof(editing.number));
	memset(editing.birthday,0,sizeof(editing.birthday));
	change=1;
	return;
}

void solve_ent()			//enter�������⴦�� 
{
	int i;
	switch(status)
	{
		case cha:solve_9h(' ');return;
		case ins:contacts_num++;
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
			q_sort(0,contacts_num);
			change=1;
			return;
		case fin:
			status=non;
			finflag=1;
			edit_num=0;
			change=1;
			return;
		case del:
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
		case ipt:
					status=non;
					impflag=1;
					change=1;
					return;
		case ept:
					status=non;
					expflag=1;
					change=1;
					return;
		case nfd:status=non;change=1;return;
	}
}

void solve_ctl()//ctl�������⴦����ǰ�����������ģ���ȡ�����룬����������Ӣ�ģ���ת��Ϊ�������� 
{
	if(status==fin||status==ins)
						{
							if(edit_num!=0) return;
							old_status=status;
							status=cha;
							cha_num=1;
							clr_editingpy();
							change=1;
						}
	else if(status==cha)
	{
		status=old_status;
		cha_num=1;
		clr_editingpy();
		deskflag=1;
		change=1;
	}
}

void solve_left()		//������������⴦�� 
{
	if(status==non)
	{
		status=ipt;
		change=1;
		return;
	}
}

void solve_right()		//�����Ҽ������⴦�� 
{
	if(status==non)
	{
		status=ept;
		change=1;
		return;
	}
}

void interrupt int_9h(void)//�����жϣ������еļ�ֵ�궨�壬���ڴ˴����� 
{
    unsigned char key;
    static unsigned char KeyShift=0;
    key = inportb(0x60);  /* read key code */
    vol_button(sound1);
	switch(key)
	{
		case key_a:solve_9h(KeyShift?'A':'a');break;
		case key_b:solve_9h(KeyShift?'B':'b');break;
		case key_c:solve_9h(KeyShift?'C':'c');break;
		case key_d:solve_9h(KeyShift?'D':'d');break;
		case key_e:solve_9h(KeyShift?'E':'e');break;
		case key_f:if(status==non){
						status=fin;
						strcpy(editing.gender,"��");
						change=1;
						break;
					}solve_9h(KeyShift?'F':'f');break;
		case key_g:solve_9h(KeyShift?'G':'g');break;
		case key_h:solve_9h(KeyShift?'H':'h');break;
		case key_i:if(status==non)
					{
						status=ins;
						strcpy(editing.gender,"��");
						change=1;
						break;
					}
					solve_9h(KeyShift?'I':'i');break;
		case key_j:solve_9h(KeyShift?'J':'j');break;
		case key_k:solve_9h(KeyShift?'K':'k');break;
		case key_l:solve_9h(KeyShift?'L':'l');break;
		case key_m:solve_9h(KeyShift?'M':'m');break;
		case key_n:solve_9h(KeyShift?'N':'n');break;
        case key_o:solve_9h(KeyShift?'O':'o');break;
		case key_p:solve_9h(KeyShift?'P':'p');break;
		case key_q:solve_9h(KeyShift?'Q':'q');break;
		case key_r:solve_9h(KeyShift?'R':'r');break;
		case key_s:solve_9h(KeyShift?'S':'s');break;
		case key_t:solve_9h(KeyShift?'T':'t');break;
		case key_u:solve_9h(KeyShift?'U':'u');break;
		case key_v:solve_9h(KeyShift?'V':'v');break;
		case key_w:solve_9h(KeyShift?'W':'w');break;
		case key_x:solve_9h(KeyShift?'X':'x');break;
		case key_y:solve_9h(KeyShift?'Y':'y');break;
		case key_z:solve_9h(KeyShift?'Z':'z');break;
		case key_2:solve_9h(KeyShift?'@':'2');break;
		case key_1:solve_9h('1');break;
		case key_3:solve_9h('3');break;
		case key_4:solve_9h('4');break;
		case key_5:solve_9h('5');break;
		case key_6:solve_9h('6');break;
		case key_7:solve_9h('7');break;
		case key_8:solve_9h('8');break;
		case key_9:solve_9h('9');break;
		case key_0:solve_9h('0');break;
		case key_point:solve_9h('.');break;
		case key_space:solve_9h(' ');break;
		case key_backspace:solve_9h('\b');break;
		case key_tab:solve_9h('\t');break;
		case key_shift:KeyShift=1-KeyShift;break;
		case key_up:solve_up();break;
		case key_down:solve_down();break;
		case key_left:solve_left();break;
		case key_right:solve_right();break;
		case key_esc:solve_esc();break;
		case key_del:status=del;change=1;break;
		case key_ctl:solve_ctl();break;
		case key_ent:solve_ent();break;
                case key_alt:soundflag=1-soundflag;bgm(soundflag,music);break;
	}
    outportb(0x20, 0x20); /* End Of Interrupt */
}
