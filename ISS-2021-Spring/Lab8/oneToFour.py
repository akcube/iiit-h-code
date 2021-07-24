# Q1
s=["hyderabad", "mumbai", "bengal"]
print([(i, len(i)) for i in s])

# Q2
l1=[1,2,3]
l2=[4,5,6]
print([i*j for i in l1 for j in l2])

# Q3
print([i for i in range(1, 50) if i%5==0 or i%6==0])

# Q4
l1=[5, 10, 15]
l2=[-5, -10, -15]
print([i+j for i, j in zip(l1, l2)])
