#include <iostream>
#include <string.h>
using namespace std;
int main()
{
    int i, j, keylen, msglen;
    char input[100], recInput[100], key[30], temp[30], quot[100], rem[30], key1[30];
    cout << "\nSender Side \n";
    cout << "\nEnter the data to transmit: \n";
    cin >> input;
    cout << "Enter coefficient of polynomial: \n";
    cin >> key;

    keylen = strlen(key);
    msglen = strlen(input);

    strcpy(key1, key);
    for (i = 0; i < keylen - 1; i++)
    {
        input[msglen + i] = '0';
    }
    for (i = 0; i < keylen; i++)
        temp[i] = input[i];
    for (i = 0; i < msglen; i++)
    {
        quot[i] = temp[0];
        if (quot[i] == '0')
            for (j = 0; j < keylen; j++)
                key[j] = '0';
        else
            for (j = 0; j < keylen; j++)
                key[j] = key1[j];
        for (j = keylen - 1; j > 0; j--)
        {
            if (temp[j] == key[j])
                rem[j - 1] = '0';
            else
                rem[j - 1] = '1';
        }
        rem[keylen - 1] = input[i + keylen];
        strcpy(temp, rem);
    }
    strcpy(rem, temp);
    cout << "\nQuotient after performing crc is ";
    for (i = 0; i < msglen; i++)
        cout << quot[i];
    cout << "\nRemainder  after performing crc is ";
    for (i = 0; i < keylen - 1; i++)
        cout << rem[i];
    cout << "\ndata transmitted is: ";
    for (i = 0; i < msglen; i++)
        cout << input[i];
    for (i = 0; i < keylen - 1; i++)
        cout << rem[i];

    printf("\nReceiver Side : \n");

    cout << "\nEnter the data Received : \n";
    cin >> recInput;

    msglen = strlen(recInput);

    strcpy(key1, key);
    for (i = 0; i < keylen - 1; i++)
    {
        recInput[msglen + i] = '0';
    }
    for (i = 0; i < keylen; i++)
        temp[i] = recInput[i];
    for (i = 0; i < msglen; i++)
    {
        quot[i] = temp[0];
        if (quot[i] == '0')
            for (j = 0; j < keylen; j++)
                key[j] = '0';
        else
            for (j = 0; j < keylen; j++)
                key[j] = key1[j];
        for (j = keylen - 1; j > 0; j--)
        {
            if (temp[j] == key[j])
                rem[j - 1] = '0';
            else
                rem[j - 1] = '1';
        }
        rem[keylen - 1] = recInput[i + keylen];
        strcpy(temp, rem);
    }
    strcpy(rem, temp);

    cout << "\nQuotient after Receiving Data is ";
    for (i = 0; i < msglen; i++)
        cout << quot[i];
    cout << "\nRemainder  after Receiving Data  is ";
    for (i = 0; i < keylen - 1; i++)
        cout << rem[i];

    bool error = false;

    for (int i = 0; i < strlen(rem); i++)
    {
        if (rem[i] == '1')
        {
            error = true;
            printf("\nData received with Error\n");
            break;
        }
    }

    if (!error)
        printf("\n No Error\n");
}
