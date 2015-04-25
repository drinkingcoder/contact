#include "all.h"

/*------------------------------------------------------------------*/
/*																	*/
/*	����ļ��������뵼�����֣������ݵ�������Ҳд������ļ��� 	*/
/*																	*/
/*------------------------------------------------------------------*/

char s[100];	//Ϊ���ٺ������ظ����ռ����ʱ���� 

void swaps(char *s1,char*s2)	//��ָ���������ַ������н��� 
{
	memset(s,0,sizeof(s));
	strcpy(s,s1);
	strcpy(s1,s2);
	strcpy(s2,s);
}

void q_sort(int l,int r)		//�������򣬶�contacts���е����ݽ��д��� 
{
	int lt=l,rt=r;
	char tt[100];
	memset(tt,0,sizeof(tt));
	strcpy(tt,contacts[(l+r)/2].name);
	while(lt<=rt)
	{
		while(strcmp(contacts[lt].name,tt)<0) lt++;
		while(strcmp(tt,contacts[rt].name)<0) rt--;
		if(lt<=rt)
		{
			swaps(contacts[lt].name,contacts[rt].name);
			swaps(contacts[lt].number,contacts[rt].number);
			swaps(contacts[lt].email,contacts[rt].email);
			swaps(contacts[lt].birthday,contacts[rt].birthday);
			swaps(contacts[lt].gender,contacts[rt].gender);
			lt++;
			rt--;
		}
	}
	if(lt<r) q_sort(lt,r);
	if(l<rt) q_sort(l,rt);
}

void import(char * s)	//��s�ļ��е������� 
{
	FILE *fp=fopen(s,"r");
	char c;
	char p[50];
	int num=0;
	int now=0;
	change=1;
	if(fp==NULL) return;
	memset(p,0,sizeof(p));
	while((c=fgetc(fp)))
	{
		switch(c)
		{
			case ',':
				switch(now)
				{
					case 0:strcpy(contacts[contacts_num].name,p);break;
					case 1:strcpy(contacts[contacts_num].gender,p);break;
					case 2:strcpy(contacts[contacts_num].birthday,p);break;
					case 3:strcpy(contacts[contacts_num].number,p);break;
					case 4:strcpy(contacts[contacts_num].email,p);break;
					default:break;
				}
				memset(p,0,sizeof(p));
				now=now+1;
				num=0;
				break;
			case 10:
				switch(now)
				{
					case 0:strcpy(contacts[contacts_num].name,p);break;
					case 1:strcpy(contacts[contacts_num].gender,p);break;
					case 2:strcpy(contacts[contacts_num].birthday,p);break;
					case 3:strcpy(contacts[contacts_num].number,p);break;
					case 4:strcpy(contacts[contacts_num].email,p);break;
					default:break;
				}
				memset(p,0,sizeof(p));
				now=now+1;
				contacts[contacts_num].flag=1;
				contacts_num++;
				num=0;
				now=0;
				break;
			default:p[num]=c;num++;break;
		}
		if(feof(fp)) break;
	}
	contacts_num--;
	fclose(fp);
	q_sort(0,contacts_num);
}

void export(char *s)	//��S�ļ��е������� 
{
	FILE* fp=fopen(s,"w");
	int i;
	for(i=1;i<=contacts_num;i++)
		fprintf(fp,"%s,%s,%s,%s,%s\n",contacts[i].name,contacts[i].gender,contacts[i].birthday,contacts[i].number,contacts[i].email);
	fclose(fp);
}
