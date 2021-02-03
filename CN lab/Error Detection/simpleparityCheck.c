#include <stdio.h>

void main()
{
    int n, i;

    printf("Sender Side : \n");

    printf("Enter Number of Bits : \n");
    scanf("%d", &n);

    int bits[n + 1];

    printf("enter data : ");

    int evenCounter = 0;

    for (i = 0; i < n; i++)
    {
        scanf("%d", &bits[i]);
        if (bits[i] == 1)
        {
            evenCounter++;
        }
    }

    bits[n] = (evenCounter % 2 == 0) ? 0 : 1;

    printf("The data with parity bit : ");

    for (i = 0; i < n + 1; i++)
    {
        printf("%d", bits[i]);
    }

    printf("\n");

    printf("Receiver Side : \n");

    int receivedBits[n + 1];

    printf("Enter the data received : \n");

    int rcounter = 0;
    for (i = 0; i < n + 1; i++)
    {
        scanf("%d", &receivedBits[i]);
        if (receivedBits[i] == 1)
        {
            rcounter++;
        }
    }

    if (rcounter % 2 == 0)
    {
        printf("There is no Error in Received Data");
    }
    else
    {
        printf("There is Error in Received Data");
    }
}