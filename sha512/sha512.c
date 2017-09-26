#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define CH(x,y,z) (((x) & (y)) ^ ((~(x)) & (z)))
#define MAJ(x,y,z) (((x) & (y)) ^ ((x) & (z)) ^ ((y) & (z)))
#define ROTR(x,n)   (((x)>>(n)) | ((x) << (64 - (n))))
#define E0(x)	(ROTR(x,28) ^ ROTR(x,34) ^ ROTR(x,39))
#define E1(x)	(ROTR(x,14) ^ ROTR(x,18) ^ ROTR(x,41))
#define R0(x)	(ROTR(x,1)  ^ ROTR(x,8)  ^ ((x)>>7))
#define R1(x)	(ROTR(x,19) ^ ROTR(x,61) ^ ((x)>>6))
#define N 128
#define M 80
	long long len;
	unsigned long long H[8]={
	0x6a09e667f3bcc908,
    	0xbb67ae8584caa73b,
    	0x3c6ef372fe94f82b,
    	0xa54ff53a5f1d36f1,
    	0x510e527fade682d1,
    	0x9b05688c2b3e6c1f,
    	0x1f83d9abfb41bd6b,
    	0x5be0cd19137e2179
};
	unsigned long long A[8];
	unsigned long long *w;
	unsigned char *input;
	unsigned char *p;
	unsigned long long k[80] =  {
		0x428a2f98d728ae22, 0x7137449123ef65cd,
    	0xb5c0fbcfec4d3b2f, 0xe9b5dba58189dbbc,
    	0x3956c25bf348b538, 0x59f111f1b605d019,
    	0x923f82a4af194f9b, 0xab1c5ed5da6d8118,
    	0xd807aa98a3030242, 0x12835b0145706fbe,
		0x243185be4ee4b28c, 0x550c7dc3d5ffb4e2,
    	0x72be5d74f27b896f, 0x80deb1fe3b1696b1,
    	0x9bdc06a725c71235, 0xc19bf174cf692694,
    	0xe49b69c19ef14ad2, 0xefbe4786384f25e3,
    	0x0fc19dc68b8cd5b5, 0x240ca1cc77ac9c65,
    	0x2de92c6f592b0275, 0x4a7484aa6ea6e483,
    	0x5cb0a9dcbd41fbd4, 0x76f988da831153b5,
    	0x983e5152ee66dfab, 0xa831c66d2db43210,
    	0xb00327c898fb213f, 0xbf597fc7beef0ee4,
    	0xc6e00bf33da88fc2, 0xd5a79147930aa725,
    	0x06ca6351e003826f, 0x142929670a0e6e70,
    	0x27b70a8546d22ffc, 0x2e1b21385c26c926,
    	0x4d2c6dfc5ac42aed, 0x53380d139d95b3df,
    	0x650a73548baf63de, 0x766a0abb3c77b2a8,
    	0x81c2c92e47edaee6, 0x92722c851482353b,
    	0xa2bfe8a14cf10364, 0xa81a664bbc423001,
    	0xc24b8b70d0f89791, 0xc76c51a30654be30,
    	0xd192e819d6ef5218, 0xd69906245565a910,
    	0xf40e35855771202a, 0x106aa07032bbd1b8,
    	0x19a4c116b8d2d0c8, 0x1e376c085141ab53,
    	0x2748774cdf8eeb99, 0x34b0bcb5e19b48a8,
    	0x391c0cb3c5c95a63, 0x4ed8aa4ae3418acb,
    	0x5b9cca4f7763e373, 0x682e6ff3d6b2b8a3,
    	0x748f82ee5defb2fc, 0x78a5636f43172f60,
    	0x84c87814a1f0ab72, 0x8cc702081a6439ec,
    	0x90befffa23631e28, 0xa4506cebde82bde9,
    	0xbef9a3f7b2c67915, 0xc67178f2e372532b,
    	0xca273eceea26619c, 0xd186b8c721c0c207,
    	0xeada7dd6cde0eb1e, 0xf57d4f7fee6ed178,
    	0x06f067aa72176fba, 0x0a637dc5a2c898a6,
    	0x113f9804bef90dae, 0x1b710b35131c471b,
    	0x28db77f523047d84, 0x32caab7b40c72493,
    	0x3c9ebe0a15c9bebc, 0x431d67c49c100d4c,
    	0x4cc5d4becb3e42b6, 0x597f299cfc657e2a,
    	0x5fcb6fab3ad6faec, 0x6c44198c4a475817
    };
	void code(unsigned char *input);
	unsigned long long Wconversion(unsigned char *input ,int j);
	char * readfile(char *argv);
	char Len_calculation(unsigned long long a,unsigned char *input);
	void prepareMessage(unsigned char *input,unsigned long long *w);
	void iteration(unsigned long long *w,unsigned long long H[8],unsigned long long A[8]);
int main(int argc,char *argv[])
{	int i,n;
	input = (unsigned char *)malloc(sizeof(unsigned char)*N);
	w = (unsigned long long *)malloc(sizeof(unsigned long long)*M);
	p=readfile(argv[1]);
	input=p;
while(*input)
{	n=strlen(input);
	if(n<128)	break;
	prepareMessage(input,w);
	iteration(w,H,A);
	input=input+128;
}	
if(n%128<112){
	code(input);
	prepareMessage(input,w);
	iteration(w,H,A);
}
else if(n%128>=112)
{		code(input);
	prepareMessage(input,w);
	iteration(w,H,A);
	input=input+64;
	Len_calculation(len*8,input);
	prepareMessage(input,w);
	iteration(w,H,A);
	
}
for(i=0;i<8;i++)
	printf("%llx ",H[i]);
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
	if(n<112)
	{	x=len*8;
		Len_calculation(x,input);
		*(input+n)=0x80;
		for(i=n+1;i<120;i++)
		*(input+i)=0x00;
	
	}
	else if(n>=112)
	{	
	
		*(input+n)=0x80;
		for(i=n+1;i<128;i++)
		*(input+i)=0x00;
	
	}
	
}
char Len_calculation(unsigned long long a,unsigned char *input)
{	
	unsigned long long t, p;
	int i,j;
	t=0;
	p=~(~t<<8);
	for(i=0;i<4;i++)
	{	j=8*i;
		*(input+127-i)=(char)((a&(p<<j))>>j);
	}
	
	return '0';
}
unsigned long long Wconversion(unsigned char *input ,int j)
	{	unsigned long long t;
		t = (((long long)input[j])<<56)|(((long long)input[j+1])<<48)|(((long long)input[j+2])<<40)|(((long long)input[j+3])<<32)|(((long long)input[j+4])<<24)|(((long long)input[j+5])<<16)|(((long long)input[j+6])<<8|((long long)input[j+7])<<0);
		return t;
	}
void prepareMessage(unsigned char *input,unsigned long long *w)
{
	int i,j;
	
	for(i=0;i<16;i++)
	{	j=8*i;
		*(w+i)=Wconversion(input,j);
	}
	
	for(i=16;i<80;i++)
	{	
		*(w+i)=R1(w[i-2])+w[i-7]+R0(w[i-15])+w[i-16];	
	}
	

}

void iteration(unsigned long long *w,unsigned long long H[8],unsigned long long A[8])
{	int i;	
	unsigned long long t1,t2;
	for(i=0;i<8;i++)
		A[i]=H[i];
	for(i=0;i<80;i++)
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
