#include<bits/stdc++.h> 
using namespace std; 

string addBinary(string a, string b) 
{ 
    string result = ""; // Initialize result 
    int s = 0;          // Initialize digit sum 
  
    // Traverse both strings starting from last 
    // characters 
    int i = a.size() - 1, j = b.size() - 1; 
    while (i >= 0 || j >= 0 || s == 1) 
    { 
        // Comput sum of last digits and carry 
        s += ((i >= 0)? a[i] - '0': 0); 
        s += ((j >= 0)? b[j] - '0': 0); 
  
        // If current digit sum is 1 or 3, add 1 to result 
        result = char(s % 2 + '0') + result; 
  
        // Compute carry 
        s /= 2; 
  
        // Move to next digits 
        i--; j--; 
    } 
    return result; 
} 

int k,n;

string checkSumGenerate(){
    printf("Enter the data : \n");

    string accumulator = "000000";

    for (int i = 0; i < k; i++)
    {
        string temp;
        cin >> temp;
        temp = addBinary(temp , accumulator);
        if(temp.length() != n){
            temp.erase(0,1);
            accumulator = addBinary(temp, "1");
        }else{
            accumulator = temp;
        }
    }

    return accumulator;
}

int main() {
    printf("Enter No of discrete data : \n");
    scanf("%d", &k);
    printf("Enter No of bits in data : \n");
    scanf("%d", &n);

    

    printf("\n Sender Side \n\n");

    string sendCheck = checkSumGenerate();

    cout << " Generated sum : " << sendCheck ;

    for (int i = 0; i < sendCheck.size(); i++)
    {
        sendCheck[i] = sendCheck[i] == '1' ? '0' : '1';
    }

    cout << " CheckSum : " << sendCheck ;

    printf("\n\n Receiver Side : \n\n");

    string recCheck = checkSumGenerate();

    cout << "\ncheckSum of data received : " << recCheck;

    recCheck = addBinary(recCheck, sendCheck);

    bool isError = false;

    cout << "\nResult : " << recCheck;

    for (int i = 0 ; i < recCheck.size(); i++)
    {
        if(recCheck[i] == '0'){
            isError = true;
            break;
        }
    }

    if(isError){
        printf("\nThere was an Error in the Received Data \n ");
    }
    else
    {
        printf("\nNo Error");
    }
    
    




    
    
    return 0;
}