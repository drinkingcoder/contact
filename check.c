#include<stdio.h>
#include<stdlib.h>
#include<string.h>

char cha1[4],cha2[4],cha3[4],cha4[4];

void transform(char* s1,int* number)
{
	int i,len,num=*number,j;
	char c1[500],c2[500],c;
	FILE* fp=fopen("character","r");
	memset(cha1,0,sizeof(cha1));
	memset(cha2,0,sizeof(cha2));
	memset(cha3,0,sizeof(cha3));
	memset(cha4,0,sizeof(cha4));
	if(num<1) num=*number=1;
	for(i=0;i<400;i++)
	{
		fgets(c1,10000,fp);
		for(j=0;j<strlen(c1);j++)
			if(c1[j]==' ')
			{
				strcpy(c2,c1+j+1);
				c1[j]='\0';
				break;
			}
		if(strcmp(s1,c1)==0)
		{
			len=strlen(c2)/2;
			if(num>len) num=*number=len;
			cha1[0]=c2[num*2-2];
			cha1[1]=c2[num*2-1];
			if(num+1>=len) return;
			cha2[0]=c2[num*2];
			cha2[1]=c2[num*2+1];
			if(num+2>=len) return;
			cha3[0]=c2[num*2+2];
			cha3[1]=c2[num*2+3];
			if(num+3>=len) return;
			cha4[0]=c2[num*2+4];
			cha4[1]=c2[num*2+5];
			fclose(fp);
			return;
		}
	}
	fclose(fp);
	return;
}

int main()
{
	int k;
	char s1[500],s2[500];
	scanf("%s %d",s1,&k);
	transform(s1,&k);
	printf("%s\n%s\n%s\n%s\n",cha1,cha2,cha3,cha4);
	system("pause");
	return 0;
}

