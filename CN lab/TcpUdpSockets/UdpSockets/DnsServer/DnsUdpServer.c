// Server side UDP Socket !Linker! -> -lws2_32
#include <unistd.h>
#include <stdio.h>
#include <winsock2.h> // for windows system
// #include <sys/socket.h>  //for linux systems
#include <stdlib.h>
#include <ws2tcpip.h> //for windows system
//#include <netinet/in.h>  //for linux systems
#include <string.h>
#include <time.h>
#define PORT 43454
#define MAX 1024
#define bzero(b, len) (memset((b), '\0', (len)), (void)0)

void initChat(int, struct sockaddr_in);
void initForWindows();
int createSocket();
void bindSocket(int, struct sockaddr_in);


int main(int argc, char const *argv[])
{
    //inits
    int server_fd, flag;
    struct sockaddr_in serv_addr, cli_addr;

    //windows socket init
    initForWindows();

    // Creating socket file descriptor
    printf("Creating UDP Socket...  \n");
    server_fd = createSocket();

    memset(&serv_addr, 0, sizeof(serv_addr)); 
    memset(&cli_addr, 0, sizeof(cli_addr)); 

    //setting address
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(PORT);

    // Forcefully attaching socket to the port 8080
    bindSocket(server_fd, serv_addr);

    // listening to the port
    char ipAddress[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &serv_addr, ipAddress, INET_ADDRSTRLEN);
    printf("port ->  %d , ipAddress of Server -> %s \n", ntohs(serv_addr.sin_port), ipAddress);

    printf("looking for client... \n");

    initChat(server_fd, cli_addr);
    close(server_fd);
    WSACleanup();
    return 0;
}

void initChat(int sockfd, struct sockaddr_in cli_addr)
{
    char buff[MAX];
    int n, flag = 0, len;
    while (1)
    {
        bzero(buff, MAX);

        len = sizeof(cli_addr);
        n = recvfrom(sockfd, buff, MAX,
                        0, (struct sockaddr *)&cli_addr,
                        &len);

        if(n < 0){
            perror("error");
        }
      
        buff[n] = '\0';

        printf("\nFrom client: %s \n", buff);

        char ipAddress[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &cli_addr, ipAddress, INET_ADDRSTRLEN);
        printf("ip address of client -> %s \n ", ipAddress);


        printf("\nTo client [exit] : ");

        bzero(buff, MAX);
        n = 0;
        while ((buff[n++] = getchar()) != '\n') ;


        flag = sendto(sockfd, buff, strlen(buff),
                      0, (const struct sockaddr *)&cli_addr,
                      len);
        
        if (strncmp("exit", buff, 4) == 0)
        {
            printf("Server Exiting...\n");
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
    int server_fd;
    if ((server_fd = socket(AF_INET, SOCK_DGRAM, 0)) <= 0)
    {
        perror("socket failed");
        WSACleanup();
        exit(EXIT_FAILURE);
    }

    return server_fd;
}

void bindSocket(int fd, struct sockaddr_in address)
{
    if (bind(fd, (struct sockaddr *)&address,
             sizeof(address)) < 0)
    {
        perror("bind failed ");
        printf("%d", WSAGetLastError());
        WSACleanup();
        exit(EXIT_FAILURE);
    }
}

