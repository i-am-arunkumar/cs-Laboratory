

n = int(input("Enter the no of tuples : "))

l = []

for i in range(n):
    l.append(tuple(list(map(int, input("Enter tuple : ").strip().split()))))

l.sort(key=lambda x: x[1])

print("Sorted List is ", l )
