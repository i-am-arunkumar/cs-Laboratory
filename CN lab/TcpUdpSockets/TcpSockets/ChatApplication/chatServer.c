// Server side Tcp Socket !Linker! -> -lws2_32
#include <unistd.h>
#include <stdio.h>
#include <winsock2.h> // for windows system
// #include <sys/socket.h>  //for linux systems
#include <stdlib.h>
#include <ws2tcpip.h> //for windows system
//#include <netinet/in.h>  //for linux systems
#include <string.h>
#include <time.h>
#define PORT 8080
#define MAX 1024
#define bzero(b,len) (memset((b), '\0', (len)), (void) 0)  

void initChat(int);
void initForWindows();
int createSocket();
void configSocket(int);
void bindSocket(int, struct sockaddr_in );
void listenSocket(int);
int acceptConnections(int, struct sockaddr_in);

int main(int argc, char const *argv[])
{

    //inits
    int server_fd, live_socket, flag;
    struct sockaddr_in address;

    //windows socket init
    initForWindows();

    // Creating socket file descriptor

    printf("Creating TCP Socket...  \n");
    server_fd = createSocket();

    // Forcefully attaching socket to the port 8080~
    configSocket(server_fd);

    //setting address
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Forcefully attaching socket to the port 8080
    bindSocket(server_fd, address);

    // listening to the port
    char ipAddress[INET_ADDRSTRLEN];
    inet_ntop( AF_INET, &address, ipAddress, INET_ADDRSTRLEN );
    printf("Listening to the port -> %d on local Address -> %s ... \n", (int) ntohs(address.sin_port), ipAddress);
    listenSocket(server_fd);

    //accept connections
    printf("looking for a client... \n");
    live_socket = acceptConnections(server_fd, address);

    printf("A client has been connected... \n");
    initChat(live_socket);
    close(server_fd);
    WSACleanup();
    return 0;
}

void initChat(int sockfd)
{
    char buff[MAX];
    int n, flag = 0;
    while (1)
    {
        bzero(buff, MAX);

        flag = recv(sockfd, buff, sizeof(buff), 0);
        if (flag < 0)
        {
            perror("Error in read : ");
        }

        printf("\nFrom client: %s \n", buff);
        printf("To client [exit, date] : ");

        bzero(buff, MAX);
        n = 0;
        while ((buff[n++] = getchar()) != '\n');

        if (strncmp("date", buff, 4) == 0){
            bzero(buff, MAX);
            char currentTime[MAX];
            time_t  ticks=time(NULL);
            strcpy(currentTime,ctime(&ticks)); 
            strcpy(buff, "Current date and Time is : ");
            strcat(buff,currentTime);
        }

        flag = send(sockfd, buff, sizeof(buff), 0);

        if (flag < 0)
        {
            perror("Error in write");
        }

        if (strncmp("exit", buff, 4) == 0){
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
        return ;
    }
}

int createSocket()
{
    int server_fd;
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) <= 0)
    {
        perror("socket failed");
        WSACleanup();
        exit(EXIT_FAILURE);
    }

    return server_fd;
}

void configSocket(int fd)
{

    BOOL opt = TRUE;
    if (setsockopt(fd, SOL_SOCKET, SO_REUSEADDR /* | SO_REUSEPORT */,
                   (char *)&opt, sizeof(BOOL)))
    {
        perror("setsockopt");
        WSACleanup();
        exit(EXIT_FAILURE);
    }
}

void bindSocket(int fd, struct sockaddr_in address)
{
    if (bind(fd, (struct sockaddr *) &address,
             sizeof(address)) < 0)
    {
        perror("bind failed ");
        printf("%d",WSAGetLastError());
        WSACleanup();
        exit(EXIT_FAILURE);
    }
}

void listenSocket(int fd)
{
    if (listen(fd, 3) < 0)
    {
        perror("listen");
        WSACleanup();
        exit(EXIT_FAILURE);
    }
}

int acceptConnections(int fd, struct sockaddr_in address)
{
    int live_socket;
    int addrlen = sizeof(address);
    if ((live_socket = accept(fd, (struct sockaddr *)&address,
                              (socklen_t *)&addrlen)) < 0)
    {
        perror("accept");
        WSACleanup();
        exit(EXIT_FAILURE);
    }

    return live_socket;
}