#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define N 64
#define M 80
	int len;
	unsigned long H[5]={0x67452301,0xefcdab89,0x98badcfe,0x10325476,0xc3d2e1f0};	
	unsigned long A[5];
	unsigned long *w;
	unsigned char *input;
	unsigned char *p;
	unsigned long k; 
	void code(unsigned char *input);
	char * readfile(char *argv);
	char Len_calculation(unsigned long a,unsigned char *input);
	void prepareMessage(unsigned char *input,unsigned long *w);
	void iteration(unsigned long *w,unsigned long H[5],unsigned long A[5]);
int main(int argc ,char *argv[])
{	int i,n;
	input = (unsigned char *)malloc(sizeof(unsigned char)*N);
	w = (unsigned long *)malloc(sizeof(unsigned long)*M);
	p=readfile(argv[1]);
	input=p;
	printf("len=%d\n",len); 
//************************************
while(*input)
{	n=strlen(input);
	if(n<64)	break;
	//fun();
	prepareMessage(input,w);
	iteration(w,H,A);
	input=input+64;
}	
if(n%64<56){
	code(input);
	prepareMessage(input,w);
	iteration(w,H,A);
}
else if(n%64>=56)
{	
	code(input);
	prepareMessage(input,w);
	iteration(w,H,A);
	input=input+64;
	Len_calculation(len*8,input);
	prepareMessage(input,w);
	iteration(w,H,A);
	
}
	


for(i=0;i<5;i++)
{
	printf("%lx ",H[i]);
}	
	
	printf("\n");
	return 0;
}
void fun()
{
	prepareMessage(input,w);
	iteration(w,H,A);

}
 char * readfile( char *argv)
{	FILE *fp;
	//int length;
	 char *p;
	if((fp=fopen(argv,"r"))==NULL)
		{
			printf("cannot open this file!\n");
			exit (0);
		}
	fseek(fp,0,SEEK_END);
	len=ftell(fp);
	p=( char *)malloc(sizeof( char)*len);
	rewind(fp);
	fread(p,1,len,fp);
	fclose(fp);
	return p;
	
}

void   code(unsigned char *input)
{	long x;
	int n,i;
	n=strlen(input);
	if(n<56)
	{	x=len*8;
		Len_calculation(x,input);
		*(input+n)=0x80;
		for(i=n+1;i<56;i++)
		*(input+i)=0x00;
	
	}
	else if(n>=56)
	{	
	
		*(input+n)=0x80;
		for(i=n+1;i<64;i++)
		*(input+i)=0x00;
	
	}
	
}
char Len_calculation(unsigned long a,unsigned char *input)
{	
	unsigned long t, p;
	int i,j;
	t=0;
	p=~(~t<<8);
	for(i=0;i<4;i++)
	{	j=8*i;
		*(input+63-i)=(char)((a&(p<<j))>>j);
	}
	
	return '0';
}
void prepareMessage(unsigned char *input,unsigned long *w)
{
	int i,j;unsigned long t,t1;
	for(i=0;i<16;i++)
	{	j=4*i;
		*(w+i)=((long)input[j])<<24|((long)input[1+j])<<16|((long)input[2+j]<<8)|((long)input[3+j]<<0);
	}
	for(i=16;i<80;i++)
	{	
		*(w+i)=w[i-16]^w[i-14]^w[i-8]^w[i-3];
		t=w[i]<<1;
		t1=w[i]>>31;
		w[i]=t|t1;
	}
}

void iteration(unsigned long *w,unsigned long H[5],unsigned long A[5])
{	int i,flag;
	unsigned long t,t1,t2,t3,k,f;
	for(i=0;i<5;i++)
		A[i]=H[i];
	for(i=0;i<80;i++)
	{
		flag=i/20;
		switch(flag)
		{
			case 0: k=0x5a827999;f=(A[1]&A[2])|(~A[1]&A[3]);break;
			case 1: k=0x6ed9eba1;f=A[1]^A[2]^A[3];break;
			case 2: k=0x8f1bbcdc;f=(A[1]&A[2])|(A[1]&A[3])|(A[2]&A[3]);break;
			case 3: k=0xca62c1d6;f=A[1]^A[2]^A[3];break;
		}
		t1=A[0]<<5;
		t2=A[0]>>27;
		t3=t1|t2;
		t=t3+f+A[4]+*(w+i)+k;
		A[4]=A[3];
		A[3]=A[2];

		t1=A[1]<<30;
		t2=A[1]>>2;
		A[2]=t1|t2;
		A[1]=A[0];
		A[0]=t;
	
}

for(i=0;i<5;i++)
{
	H[i]=H[i]+A[i];
}	


}
