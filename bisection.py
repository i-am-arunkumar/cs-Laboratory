 
from bisect import bisect_left 

def BinarySearch(a, x): 
	i = bisect_left(a, x) 
	if i != len(a) and a[i] == x: 
		return i 
	else: 
		return -1


a = input("Enter String : ")
x = input("Enter Substring : ")

sn = len(x)
an = len(a)
res = BinarySearch(a, x[0]) 
if res == -1: 
	print(x, "is absent") 
else: 
    isTrue = res + (sn-1) < an
    if(isTrue and a[res: res+sn] == x ):
        print(x, "is Present")
    else:
        print(x, "is absent djfsdjlf")


