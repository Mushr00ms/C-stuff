#include <sys/socket.h>//socket()-bind()-listen()-accept()
#include <arpa/inet.h>//htonl()-htons()
#include <stdio.h>//perror()-printf()-fgets()
#include <string.h>//strchr()-strlen()-strcmp()-bzero()

#define PORT 2500
#define SOCKET_ERROR -1
#define INVALID_SOCKET -1
#define MAX_CO 5
#define MAX_DATA_SEND 10

/*
1-créer une socket
2-paramétrer la socket
3-communiquer avec le client
4-fermer la connexion
*/


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
	//Création des variables serveur utiles à la connexion
	SOCKET sock;
	SOCKADDR_IN serveur;
	char buffer[50] = {0};
	socklen_t sizeServeur = sizeof(serveur);

	//Création des variables client utiles à la connexion
	SOCKET csock;
	SOCKADDR_IN client;
	socklen_t sizeClient = sizeof(client);


	//Création de la socket 
	//int socket(int domain, int type, int protocol);
	sock = socket(AF_INET,SOCK_STREAM,0);
	//Teste de la création de la socket
	if(!sock)
	{
		printf("La socket n'a pas pu être créer...\n");
		return -1;
	}
	//création des variables pour gérer les erreurs de bindage et d'écoute
	int errorBind, errorListen;
	//contexte d'adressage 
	serveur.sin_addr.s_addr = htonl(INADDR_ANY);
	serveur.sin_family = AF_INET;
	serveur.sin_port = htons(PORT);
	//bindage de la connexion
	//int bind(int socket, const struct sockaddr* addr, socklen_t addrlen); return SOCKET_ERROR si probleme
	errorBind = bind(sock, (SOCKADDR*)&serveur,sizeServeur);
	if(errorBind == SOCKET_ERROR)
	{
		perror("bind");
		return -1;
	}
	printf("La socket est parametrée...\n");
	//Ecoute sur le port
	//int listen(int socket, int backlog); return SOCKET_ERROR si probleme
	errorListen = listen(sock,MAX_CO);
	//Teste de l'écoute
	if(errorListen == SOCKET_ERROR)
	{
		perror("listen");
		return -1;
	}
	printf("Le serveur écoute sur le port %d ...\n",PORT);
	//Acceptation du client 
	//int accept(int socket, struct sockaddr* addr, socklen_t* addrlen); return INVALID_SOCKET si probleme
	printf("Le serveur attend qu'un client se connecte sur le port %d..\n",PORT);
	csock  = accept(sock, (SOCKADDR*)&client, &sizeClient);
	printf("Client connecté sur la socket %d avec l'ip %s sur le port %d\n",sock,inet_ntoa(client.sin_addr),htons(serveur.sin_port));
	//int send(int socket, void* buffer, size_t len, int flags);
	while(strcmp(buffer,"exit") != 0)
	{
		bzero(buffer,50);
		printf("Entrez le msg à envoyé < à 50 char : ");
		fgets(buffer, 50 , stdin);
		char * ptr = NULL;
		ptr = strchr(buffer, '\n');
		*ptr = '\0';
		if(send(csock,buffer,50,0) != SOCKET_ERROR)
		{
			printf("Contenu envoyé au client : %s (%d octets)\n",buffer,(int)strlen(buffer));
		}
		else
		{
			perror("send");
			return -1;
		}
	}
	//le client c'est connecté on ferme la socket client
	printf("Fermeture de la connexion client\n");
	shutdown(csock,2);
	printf("Fermeture de la connexion serveur\n");
	shutdown(sock,2);
	//on ferme la socket serveur
	return 0;
}