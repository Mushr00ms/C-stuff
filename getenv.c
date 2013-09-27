#include <stdio.h>//printf()
#include <stdlib.h>//getenv()

int main(int argc, char const *argv[])
{
	if(argc != 2)
	{
		printf("Usage : %s <variable name>\n", argv[0]);
		return -1;
	}

	void * addr = getenv(argv[1]);

	if(addr == NULL)
		printf("The variable %s doesn't exist.\n", argv[1]);
	else
		printf("Addr for %s : %p\n", argv[1], addr);
	return 0;
}