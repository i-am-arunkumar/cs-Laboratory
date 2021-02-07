// Client side Tcp Socket Program ! Linker ! -> -lws2_32
#include <stdio.h>
#include <winsock2.h> //for windows
//#include <sys/socket.h> //for linux
#include <Ws2tcpip.h> // for windows
//#include <arpa/inet.h>  //for linux
#include <unistd.h>
#include <string.h>
#define PORT 8080
#define MAX 1024
#define bzero(b, len) (memset((b), '\0', (len)), (void)0)

void initChat(int);
void initForWindows();
int createSocket();
void convertLoopBackToBinary(struct sockaddr_in * );
void connectToServer(int ,struct sockaddr_in );

int main(int argc, char const *argv[])
{
	int sock = 0, flag;
	struct sockaddr_in serv_addr;

	//windows init
	initForWindows();

	printf("Creating TCP Socket..... \n");
	sock = createSocket();

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(PORT);

	// Convert IPv4 and IPv6 addresses from text ("127.0.0.1") to binary form
	convertLoopBackToBinary(&serv_addr);
	
	//connecting to server
	char ipAddress[INET_ADDRSTRLEN];
    inet_ntop( AF_INET, &serv_addr, ipAddress, INET_ADDRSTRLEN );
	printf("Connecting to Server at port ->  %d , ipAddress of Server -> %s \n", ntohs(serv_addr.sin_port),ipAddress);
	connectToServer(sock,serv_addr);

	printf("Connected to server ... \n\n");	
	initChat(sock);
	WSACleanup();
	close(sock);
	return 0;
}

void initChat(int sockfd)
{
	char buff[MAX];
	int n, flag;
	while (1)
	{
		bzero(buff, sizeof(buff));

		printf("Enter message to server : ");

		n = 0;
		while ((buff[n++] = getchar()) != '\n')
			;

		flag = send(sockfd, buff, sizeof(buff), 0);
		if (flag < 0)
		{
			perror("Error in write");
		}

		bzero(buff, sizeof(buff));

		flag = recv(sockfd, buff, sizeof(buff), 0);
		if (flag < 0)
		{
			perror("Error in read");
		}

		printf("From Server : %s \n", buff);

		if ((strncmp(buff, "exit", 4)) == 0)
		{
			printf("Client Exit...\n");
			break;
		}
	}
}

void initForWindows()
{
	WSADATA wsaData;
	int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != NO_ERROR)
	{
		wprintf(L"Error at WSAStartup()\n");
		return;
	}
}

int createSocket()
{
	int sock;
	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		printf("\n Socket creation error \n");
		WSACleanup();
		exit(EXIT_FAILURE);
	}
	return sock;
}

void convertLoopBackToBinary(struct sockaddr_in* serv_addr){
	if (inet_pton(AF_INET, "127.0.0.1", &serv_addr->sin_addr) <= 0)
	{
		printf("\nInvalid address/ Address not supported \n");
		WSACleanup();
		exit(EXIT_FAILURE);
	}
}

void connectToServer(int sock,struct sockaddr_in serv_addr){
	if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
	{
		printf("\nConnection Failed  500 ! \n");
		printf("%d", WSAGetLastError());
		WSACleanup();
		exit(EXIT_FAILURE);
	}
}
