from biolib import RE

f = open("M.AaaS1ORF662P.txt","r") 
DNA = f.read()
f.close()
print("DNA Sequence Length: ", len(DNA), "bp")

indices = []
l = 0
r = 6
while(r <= len(DNA)):
	window = DNA[l:r]
	if(RE.check_site(window)):
		indices.append(l+1)
		print("Site number: ", len(indices))
		print("RE Site: ", window)
		print("Cut at: ", l+1, " : ", r, "\n")
	l += 1
	r += 1

print("\nRE Map\n")
result = []
for idx in range(len(indices)):
    result.append((indices[idx], indices[(idx+1) % len(indices)]-1))

result.sort(key=lambda x: -x[1] + x[0] - 1 if x[1] > x[0] else -len(DNA) - 1 + x[0] - x[1])

print("-"*40)
print("{:<5} | {:<20} | {:<15}".format(" #", "Location", "Size"))
print("-"*40)
for idx, entry in enumerate(result):
    size = entry[1] - entry[0] + 1 if entry[1] > entry[0] else \
        len(DNA) + 1 - entry[0] + entry[1]
    print("{:<5} | {:<20} | {:<15}".format(
        f" {idx+1}", f"{entry[0]} - {entry[1]}", f"{size}"))
print("-"*40)



