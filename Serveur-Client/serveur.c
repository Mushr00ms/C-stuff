#include <sys/socket.h>//socket()-bind()-listen()-accept()-shutdown()-recv()-inet_ntoa()
#include <arpa/inet.h>//htonl()-htons()-inet_ntoa()
#include <stdio.h>//perror()-printf()-fgets()
#include <string.h>//strchr()-strlen()-strcmp()-memset()-strstr()

#define PORT 31337
#define SOCKET_ERROR -1
#define INVALID_SOCKET -1
#define MAX_CO 5
#define MAX_DATA_SEND 10

typedef int SOCKET;
typedef struct sockaddr_in SOCKADDR_IN;
typedef struct sockaddr SOCKADDR;

/*
typedef int SOCKET;
typedef struct sockaddr_in SOCKADDR_IN;
typedef struct sockaddr SOCKADDR;

struct sockaddr_in
{
    short      sin_family;
    unsigned short   sin_port;
    struct   in_addr   sin_addr;
    char   sin_zero[8];
};*/



int main()
{
	SOCKET sock;
	SOCKADDR_IN serveur;
	socklen_t sizeServeur = sizeof(serveur);

	SOCKET csock;
	SOCKADDR_IN client;
	socklen_t sizeClient = sizeof(client);

	char buffer[256] = "";
	int errorBind, errorListen;

	//int socket(int domain, int type, int protocol);
	sock = socket(AF_INET,SOCK_STREAM,0);
	
	if(!sock)
	{
		perror("socket");
		return -1;
	}
	
	serveur.sin_addr.s_addr = htonl(INADDR_ANY);
	serveur.sin_family = AF_INET;
	serveur.sin_port = htons(PORT);
	
	//int bind(int socket, const struct sockaddr* addr, socklen_t addrlen); return SOCKET_ERROR si probleme
	errorBind = bind(sock, (SOCKADDR*)&serveur,sizeServeur);
	
	if(errorBind == SOCKET_ERROR)
	{
		perror("bind");
		return -1;
	}
	
	//int listen(int socket, int backlog); return SOCKET_ERROR si probleme
	errorListen = listen(sock,MAX_CO);
	
	if(errorListen == SOCKET_ERROR)
	{
		perror("listen");
		return -1;
	}
	printf("Listening on port %d ...\n",PORT);
	
	//int accept(int socket, struct sockaddr* addr, socklen_t* addrlen); return INVALID_SOCKET si probleme
	csock  = accept(sock, (SOCKADDR*)&client, &sizeClient);
	
	if(csock == INVALID_SOCKET)
	{
		perror("accept");
		return -1;
	}

	printf("User connected : ip %s:%d\n",inet_ntoa(client.sin_addr),htons(serveur.sin_port));
	
	while(1)
	{
		//int recv(int socket, void* buffer, size_t len, int flags)
		memset(buffer, 0 , 256);
		if(recv(csock, (void *)buffer, sizeof(buffer),0)!=-1)
		{
			if(strstr(buffer,"!quit") != NULL)
			{
				printf("!quit command intercept, server will shutdown\n");
				shutdown(csock,2);
				shutdown(sock,2);
				return 0;
			}
			printf("Data(s) : %s\n", buffer);
		}
		else
		{
			perror("recv");
			return -1;
		}
	}

	shutdown(csock,2);
	shutdown(sock,2);

	return 0;
}
