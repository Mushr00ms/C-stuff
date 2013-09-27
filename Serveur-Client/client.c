#include <sys/socket.h>//socket()-bind()-listen()-accept()
#include <arpa/inet.h>//htonl()-htons()-inet_ntoa()
#include <stdio.h>//perror()-printf()
#include <string.h>//strlen()-strcmp()

#define PORT 2500

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
	char buffer[50] = {0};
	SOCKET sock;
	sockaddr_in client;
	socklen_t sizeClient = sizeof(client);
	//creation socket
	sock = socket(AF_INET, SOCK_STREAM,0);
	//contexte d'adressage
	client.sin_addr.s_addr=inet_addr("127.0.0.1");
	client.sin_port = htons(PORT);
	client.sin_family = AF_INET;
	//int connect(int socket, struct sockaddr* addr, socklen_t addrlen);
	if(connect(sock,(sockaddr*)&client,sizeClient) == 0)
	{
		printf("Connexion en cours @%s:%d..\n",inet_ntoa(client.sin_addr),htons(PORT));
		while(strcmp(buffer, "exit") != 0)
		{
			//int recv(int socket, void* buffer, size_t len, int flags)
			if(recv(sock, (void *)buffer, sizeof(buffer),0)!=-1)
			{
				printf("Contenu envoyé par le serveur : %s (%d octets)\n", buffer, (int)strlen(buffer));
			}
			else
			{
				perror("recv");
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
	//on ferme la co
	return 0;
}