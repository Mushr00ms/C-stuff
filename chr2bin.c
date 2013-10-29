#include <stdio.h>//putchar()
#include <string.h>//strncpy()

void chrToBin(int);
int str_len(char *);
void strToBin(char *, int);

int main (int argc, char *argv[])
{	
	if(argc < 2)	
	{
		printf("Usage : %s <data to encode>\n",argv[0]);
		return -1;
	}

	char string[256];

	strncpy(string, argv[1], 128);
	
	int len = str_len(string);
	
	strToBin(string, len);
	putchar('\n');

	return 0; 
}

//Functions : chrToBin() - str_len() - strToBin()


void chrToBin(int c)
{
	int i;

	for( i = 7 ; i >= 0 ; i-- )
	{
		putchar(( c & ( 1 << i ) ? '1' : '0'));
	}
}

int str_len(char * s)
{
	int i = 0;

	while( *s )
	{
		i++;
		*s++;
	}
	
	return i; 
}

void strToBin(char * ss, int l)
{
	int j = 0;

	for ( j = 0 ; j < l ; j++ )
	{
		chrToBin(ss[j]);
	}
}
