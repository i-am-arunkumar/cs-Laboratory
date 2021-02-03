#include <stdio.h>

void main()
{

    int r, c, i, j;

    printf("Sender Side : \n");

    printf("Enter no of  rows and column \n");

    scanf("%d %d", &r, &c);

    int bits[r + 1][c + 1];

    printf("Enter Binary Data String : \n");

    int columnCounter[c + 1];

    for ( i = 0; i < c + 1; i++)
    {
        columnCounter[i] = 0;
    }
    

    int rowCounter = 0;

    for (i = 0; i < r; i++)
    {
        rowCounter = 0;
        for (j = 0; j < c; j++)
        {
            scanf("%d", &bits[i][j]);
            if (bits[i][j] == 1)
            {
                columnCounter[j]++;
                rowCounter++;
            }
        }
        bits[i][c] = (rowCounter % 2 == 0) ? 0 : 1;
        if (bits[i][c] == 1)
        {
            columnCounter[c]++;
        }
    }

    for (i = 0; i < c + 1; i++)
    {
        bits[r][i] = (columnCounter[i] % 2 == 0) ? 0 : 1;
    }

    printf("The Encoded data is : ");

    for (i = 0; i < r + 1; i++)
    {
        for (j = 0; j < c + 1; j++)
        {
            printf("%d", bits[i][j]);
        }

        printf(" ");
    }

    return;
}