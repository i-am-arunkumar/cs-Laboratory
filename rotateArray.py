import array

def leftRotate(arr, d, n):
    for i in range(d):
        leftRotatebyOne(arr, n)
 
def leftRotatebyOne(arr, n):
    temp = arr[0]
    for i in range(n-1):
        arr[i] = arr[i+1]
    arr[n-1] = temp
         
 
def printArray(arr,size):
    print("Rotated Array is : ")
    for i in range(size):
        print ("%d"% arr[i],end=" ")


n = int(input("Enter number of Elements : "))

inputArray  = []

print("Enter the elements : \n")

for i in range(n):
    inputArray.append(int(input("")))

d = int(input("Enter the amount to rotate : "))

leftRotate(inputArray,d,n)

printArray(inputArray,n)

 

