#include<stdio.h>
int main()
{
	char a[10000];
	char temp;
	int cnt=0;
	char ch;
	do{
		ch=getchar();
		a[cnt]=ch;
		cnt++;
	}
	while(ch!=0);
	
	if(cnt%2==0)
	{
		for(int i=1;i<=cnt/2-1;i++)
		{
			temp=a[i];
			a[i]=a[cnt-1-i];
			a[cnt-1-i]=a[i];
		}
		for(int j=1;j<=cnt-2;j+=2)
		{
			printf("%c%c",a[j+1],a[j]);
		}
	}
	else
	{
		for(int k=(cnt-1)/2;k<=cnt-1;k++)
		{
			a[k]=a[k+1];
		}
		for(int m=cnt-2;m>=0;m-=2)
		{
			printf("%c%c",a[m-1],a[m]);
		}
	}
}
