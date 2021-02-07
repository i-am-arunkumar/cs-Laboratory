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
BOOL isValidIpAddress(char *);
char * toString(char * str, int num);

int main(int argc, char const *argv[])
{
    int sock = 0, flag;
    struct sockaddr_in serv_addr;

    struct sockaddr_in echoServAddr; // Echo server address
    struct sockaddr_in fromAddr;     // Source address of echo
    unsigned short serverPort;       // Echo server port
    unsigned int fromSize;           // In-out of address size for recvfrom()
    char *servIP;                    // IP address of server
    char echoString[MAX];            // String to send to echo server
    char echoBuffer[MAX];            // Buffer for receiving echoed string
    unsigned long echoStringLen;     // Length of string to echo
    int respStringLen;               // Length of received response
    char *domainName;
    char *ipToAdd;
    char *action;
    char str[2];

    //windows init
    initForWindows();

    if ((argc < 4) || (argc > 6)) // Test for correct number of arguments
    {
        printf("\n\t\tNo of command line parametes aren't enough and proper for the request");
        exit(1);
    }

    servIP = argv[1];           // First arg: server IP address (dotted quad)
    serverPort = atoi(argv[2]); // Use given port, if any
    action = argv[3];

    strcpy(echoString, toString(str, argc));
    strcat(echoString, "#"); // Formatting the string to be sent with "#" in between each argument
    strcat(echoString, action);
    strcat(echoString, "#");

    switch (argc)
    { // Check for the number of args entered by the Client
    case 5:
        domainName = argv[4];
        strcat(echoString, domainName);
        strcat(echoString, "#");
        printf("\nCommand Sent: %s %s %s %s", argv[1], argv[2], argv[3], argv[4]);
        break;

    case 6:
        //To validate the IP Address format
        if (isValidIpAddress(argv[5]))
        {
            domainName = argv[4];
            strcat(echoString, domainName); // Concatenate the Domain name to the string
            strcat(echoString, " ");
            ipToAdd = argv[5];
            strcat(echoString, ipToAdd); // Concatenate the IP to the string
            strcat(echoString, "#");
            printf("\nCommand Sent: %s %s %s %s %s", argv[1], argv[2], argv[3], argv[4], argv[5]);
            break;
        }
        else
            DieWithError("Invalid IP Address entered by the client");

    default:
        printf("\nCommand Sent: %s %s %s", argv[1], argv[2], argv[3]);
        break;
    }
    echoStringLen = strlen(echoString);

    printf("Creating UDP Socket..... \n");
    sock = createSocket();

    bzero(&serv_addr, sizeof(serv_addr));

    echoServAddr.sin_family = AF_INET;                // Internet addr family
    echoServAddr.sin_addr.s_addr = inet_addr(servIP); // Server IP address
    echoServAddr.sin_port = htons(serverPort);

    /* Send the string to the server */
    if (sendto(sock, echoString, echoStringLen, 0, (struct sockaddr *)&echoServAddr, sizeof(echoServAddr)) != echoStringLen)
        DieWithError("sendto() sent a different number of bytes than expected");

    /* Recv a response */
    fromSize = sizeof(fromAddr);
    if ((respStringLen = recvfrom(sock, echoBuffer, MAX, 0,
                                  (struct sockaddr *)&fromAddr, &fromSize)) < 0)
        DieWithError("recvfrom() failed");

    if (echoServAddr.sin_addr.s_addr != fromAddr.sin_addr.s_addr)
    {
        fprintf(stderr, "Error: received a packet from unknown source.\n");
        exit(1);
    }
    echoBuffer[respStringLen] = '\0';

    /* null-terminate the received data */
    printf("\nReceived: %s\n", echoBuffer); // Print the echoed arg

    WSACleanup();
    close(sock);
    return 0;
}

BOOL isValidIpAddress(char *ipAddress)
{
    struct sockaddr_in sa;
    int result = inet_pton(AF_INET, ipAddress, &(sa.sin_addr));
    return result != 0;
}

char * toString(char * str, int num)
{
    int i, rem, len = 0, n;
    
    n = num;
    while (n != 0)                  // Count the number of digits
    {
        len++;
        n /= 10;
    }
    for (i = 0; i < len; i++)       // Convert each digit to a char in the character array
    {
        rem = num % 10;
        num = num / 10;
        str[len - (i + 1)] = rem +'0' ;
    }
    str[len] = '\0';
    
    return str;                     // Return the converted string
}

void initChat(int sockfd, struct sockaddr_in serv_addr)
{
    char buff[MAX];
    int n, flag, len;

    len = sizeof(serv_addr);
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
