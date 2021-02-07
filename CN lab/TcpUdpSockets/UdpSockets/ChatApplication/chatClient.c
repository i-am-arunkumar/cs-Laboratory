// Client side UDP Socket Program ! Linker ! -> -lws2_32
#include <stdio.h>
#include <winsock2.h> //for windows
//#include <sys/socket.h> //for linux
#include <ws2tcpip.h>
#include <unistd.h>
#include <string.h>
#define PORT 43454
#define MAX 1024
#define bzero(b, len) (memset((b), '\0', (len)), (void)0)

void initChat(int, struct sockaddr_in);
void initForWindows();
int createSocket();


int main(int argc, char const *argv[])
{
    int sock = 0, flag;
    struct sockaddr_in serv_addr;

    //windows init
    initForWindows();

    printf("Creating UDP Socket..... \n");
    sock = createSocket();

    bzero(&serv_addr,sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    serv_addr.sin_addr.s_addr=inet_addr("127.0.0.1");
    //connecting to server
    char ipAddress[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &serv_addr, ipAddress, INET_ADDRSTRLEN);
    printf("port ->  %d , ipAddress of Server -> %s \n", ntohs(serv_addr.sin_port), ipAddress);

    initChat(sock, serv_addr);

    WSACleanup();
    close(sock);
    return 0;
}

void initChat(int sockfd, struct sockaddr_in serv_addr)
{
    char buff[MAX];
    int n, flag, len;

    len=sizeof(serv_addr);
    while (1)
    {
        bzero(buff, sizeof(buff));

        printf("Enter message to server : ");

        n = 0;
        while ((buff[n++] = getchar()) != '\n')
            ;

        n = sendto(sockfd, buff, strlen(buff),
                      0, (const struct sockaddr *)&serv_addr,
                      sizeof(serv_addr));

        bzero(buff, sizeof(buff));

        n = recvfrom(sockfd, buff, MAX,
                        0, (struct sockaddr *)&serv_addr,
                        &len);
       

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
    if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
        printf("\n Socket creation error \n");
        WSACleanup();
        exit(EXIT_FAILURE);
    }
    return sock;
}


