#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define N 64
#define M 64
	int len;
	unsigned long H[8]={0xc1059ed8,0x367cd507,0x3070dd17,
						0xf70e5939,0xffc00b31,0x68581511,
						0X64f98fa7,0Xbefa4fa4};	
	unsigned long A[8];
	unsigned long *w;
	unsigned char *input;
	unsigned char *p;
	unsigned long k[64] = {
        0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
        0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
        0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
        0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
        0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
        0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
        0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
        0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208, 0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2,
    };
	void code(unsigned char *input);
	unsigned long R0(unsigned long *w);
	unsigned long R1(unsigned long *w);	
	unsigned long E0(unsigned long *w);
	unsigned long E1(unsigned long *w);
	unsigned long SHR(int n,unsigned long w);
	unsigned long ROTR(int n,unsigned long w);
	unsigned long CH(unsigned long x,unsigned long y,unsigned long z);
	unsigned long MAJ(unsigned long x,unsigned long y,unsigned long z);
 
	char * readfile(char *argv);
	char Len_calculation(unsigned long a,unsigned char *input);
	void prepareMessage(unsigned char *input,unsigned long *w);
	void iteration(unsigned long *w,unsigned long H[],unsigned long A[]);
int main(int argc,char *argv[])
{	int i,n;
	input = (unsigned char *)malloc(sizeof(unsigned char)*N);
	w = (unsigned long *)malloc(sizeof(unsigned long)*M);
	//p=readfile("a.txt");
	//input=p;
	printf("input:\n");
	scanf("%s",input);
	len=strlen(input);
	printf("input=%s\n",input);
	//printf("len=%d\n",len); 
//************************************
while(*input)
{	n=strlen(input);
	if(n<64)	break;
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
	


for(i=0;i<7;i++)
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
		for(i=n+1;i<60;i++)
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
unsigned long ROTR(int n,unsigned long w)
{	
//	return (((w>>(n))&(0x7fffffff>>(31-n)))|(w<<(32-n)));
	return (((w)>>n)|((w)<<(32-n)));
}
unsigned long SHR(int n,unsigned long w)
{
//	return ((w>>n)&(0x7fffffff>>(n-1)));	
	return ((w)>>n);
}
unsigned long R1(unsigned long *w)
{	unsigned long t;
	
	t=ROTR(17,w)^ROTR(19,w)^SHR(10,w);
	return  t;
}
unsigned long R0(unsigned long *w)
{	unsigned long t;
	t=ROTR(7,w)^ROTR(18,w)^SHR(3,w);
	return  t;
}
unsigned long E0(unsigned long *w)
{	unsigned long t;
	t=ROTR(2,w)^ROTR(13,w)^ROTR(22,w);
	return t;


}
unsigned long E1(unsigned long *w)
{	unsigned long t;
	t=ROTR(6,w)^ROTR(11,w)^ROTR(25,w);
	return t;
}

unsigned long CH(unsigned long x,unsigned long y,unsigned long z)
{
	return ((x&y)^((~x)&z));
//	return ((x&y)|(~y&z));
}
unsigned long MAJ(unsigned long x,unsigned long y,unsigned long z)
{
	return ((x&y)^(x&z)^(y&z)) ;
	//return ((x&y)|(x&z)|(y&z));
}

void prepareMessage(unsigned char *input,unsigned long *w)
{
	int i,j;unsigned long t,t1;
	
	for(i=0;i<16;i++)
	{	j=4*i;
		*(w+i)=((long)input[j])<<24|((long)input[1+j])<<16|((long)input[2+j]<<8)|((long)input[3+j]<<0);
	}
	
	for(i=16;i<64;i++)
	{	
		*(w+i)=R1(w[i-2])+w[i-7]+R0(w[i-15])+w[i-16];
		
		
	}
	
	
}

void iteration(unsigned long *w,unsigned long H[],unsigned long A[])
{	int i,flag;
	/* a  b  c  d  e  f  g  h
	   a0 a1 a2 a3 a4 a5 a6 a7
	*/
	unsigned long t1,t2;
	for(i=0;i<8;i++)
		A[i]=H[i];
	for(i=0;i<64;i++)
	{	t1=A[7]+E1(A[4])+CH(A[4],A[5],A[6])+k[i]+w[i];
		t2=E0(A[0])+MAJ(A[0],A[1],A[2]);
		A[7] = A[6];
		A[6] = A[5];
		A[5] = A[4];
		A[4] = A[3]+t1;
		A[3] = A[2];
		A[2] = A[1];
		A[1] = A[0];
		A[0] = t1+t2;


	}
for(i=0;i<8;i++)
H[i]=H[i]+A[i];



}
