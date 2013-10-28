#include <stdio.h>//printf()
#include <string.h>//strlen()

int main (int argc, char *argv[])
{	
	if(argc < 2)	
	{
		printf("Usage : %s <data to encode/decode>\n",argv[0]);
		return -1;
	}

	char * ss = argv[1];
	char decode[50] = "";

	int i = 0;
	int length = strlen(ss);
	
	for(i = 0; i < length; i++)
	{
		//printf("rot 13 de %c (%d) ==> %c\n",ss[i],ss[i],(ss[i] - 'A' + 13) % 26 + 'A');  -- verbose mode ahah
		if(ss[0] >= 'A' && ss[0] <= 'Z')
		{
			decode[i] = (ss[i] - 'A' +13) % 26 + 'A';
		}
		else
		{
			decode[i] = (ss[i] - 'a' +13) % 26 + 'a';	
		}
	
	}
	
	printf("%s\n",decode);
	
	return 0;
}
