


l = list(input("Enter the list : ").strip().split())

n = int(input("Enter n : "))

print("Concatenated list is ", [ f'{x}{y + 1}' for y in range(n) for x in l])
