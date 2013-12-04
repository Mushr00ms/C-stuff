#include <sys/socket.h>//socket()-bind()-listen()-accept()-inet_addr()-connect()-send()-shutdown()
#include <arpa/inet.h>//htonl()-htons()-inet_ntoa()-inet_addr()
#include <stdio.h>//perror()-printf()-fgets()
#include <string.h>//strlen()-strcmp()-strstr()-memset()-strchr()


#define PORT 31337
#define SOCKET_ERROR -1

typedef int SOCKET;
typedef struct sockaddr_in sockaddr_in;
typedef struct sockaddr sockaddr;

/*
struct sockaddr_in
{
    short      sin_family;
    unsigned short   sin_port;
    struct   in_addr   sin_addr;
    char   sin_zero[8];
};*/

int main(void)
{
	char buffer[256] =  "";
	int c = 0;
	
	SOCKET sock;
	sockaddr_in client;
	socklen_t sizeClient = sizeof(client);
	
	sock = socket(AF_INET, SOCK_STREAM,0);
	
	client.sin_addr.s_addr = inet_addr("127.0.0.1");
	client.sin_port = htons(PORT);
	client.sin_family = AF_INET;

	//int connect(int socket, struct sockaddr* addr, socklen_t addrlen);
	if(connect(sock,(sockaddr*)&client,sizeClient) == 0)
	{
		printf("Connected to %s:%d..\n",inet_ntoa(client.sin_addr),htons(PORT));

		while(1)
		{
			memset(buffer, 0 , 256);
			printf("TXT > ");
			scanf("%256s",buffer);
			while((c = getchar()) != '\n');

			//int send(int socket, void* buffer, size_t len, int flags);
			if(send(sock,buffer,sizeof(buffer),0) != SOCKET_ERROR)
			{
				if(strstr(buffer,"!quit") != NULL)
				{
					shutdown(sock,2);
					return 0;
				}
				printf("Sent : %s\n",buffer);
			}
			else
			{
				perror("send");
				return -1;
			}
		}
	}
	else
	{
		perror("connect");
		return -1;
	}

	shutdown(sock,2);

	return 0;
}
