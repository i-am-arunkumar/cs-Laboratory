#include <math.h> 
#include <stdio.h> 
  
int input[32]; 
  
int code[32]; 
  
int ham_calc(int, int); 
void solve(int input[]); 
  

int ham_calc(int position, int c_l) 
{ 
    int count = 0, i, j; 
    i = position - 1; 
  
    while (i < c_l) { 
  
        for (j = i; j < i + position; j++) { 
  
            // If current boit is 1 
            if (code[j] == 1) 
                count++; 
        } 
  
        i = i + 2 * position; 
    } 
  
    if (count % 2 == 0) 
        return 0; 
    else
        return 1; 
} 
  
void solve(int data[]) 
{ 
    data[6]=data[0]^data[2]^data[4];
	data[5]=data[0]^data[1]^data[4];
	data[3]=data[0]^data[1]^data[2];
 
	printf("\nEncoded data is\n");
	for(int i=0;i<7;i++)
        printf("%d",data[i]);
 
} 


void checkForError(int* receiverInput) {
    int c1=receiverInput[6]^receiverInput[4]^receiverInput[2]^receiverInput[0];
	int c2=receiverInput[5]^receiverInput[4]^receiverInput[1]^receiverInput[0];
	int c3=receiverInput[3]^receiverInput[2]^receiverInput[1]^receiverInput[0];
	int c=c3*4+c2*2+c1 , i;
 
    if(c==0) {
		printf("\nNo error while transmission of data\n");
    }
	else {
		printf("\nError on position %d",c);
    	
		printf("\nData sent : ");
        for(i=0;i<7;i++)
        	printf("%d",code[i]);
        
		printf("\nData received : ");
        for(i=0;i<7;i++)
        	printf("%d",receiverInput[i]);
		
		printf("\nError Correction : \n");
 
		//if errorneous bit is 0 we complement it else vice versa
		if(receiverInput[7-c]==0)
			receiverInput[7-c]=1;
        else
			receiverInput[7-c]=0;
		
		for (i=0;i<7;i++) {
			printf("%d",receiverInput[i]);
		}
	}
}
  
void main() 
{ 
    int N; 
    printf("Enter No of Bits in data  : \n");
    scanf("%d", &N);

    printf("\n Sender Side : \n\n");

    printf("Enter the Data \n");
    
    for (int i = 0; i < 4; i++)
    {
        scanf("%d", &input[i]);
    }

    printf("Generating hamming code .... ");


    // Function Call 
    solve(input);

    printf("\n\nReceiver Side : \n\n");

    printf("Enter the data received :  \n");

    int receivedData[32];

    for (int i = 0; i < 7; i++)
    {
        scanf("%d", &receivedData[i]);
    }

    checkForError(receivedData);
}



