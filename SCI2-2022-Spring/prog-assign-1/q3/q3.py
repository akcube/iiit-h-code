from biolib import utils

f = open("sequence.txt","r") 
DNA = f.read()
f.close()

print("DNA Sequence Length: ", len(DNA), "bp")
print("Possible recognition sites for pBR322 sequence: ")

sites = []
dnaLen = len(DNA)
DNA += DNA
for length in range(4, 9):
	for i in range(dnaLen):
		window = DNA[i:i+length].lower()
		complement = utils.get_complement(window)
		if complement[::-1] == window:
			sites.append((i, length))
			print("Site no: ", len(sites))
			print("Length: ", length)
			print("Position: ", i%dnaLen+1)
			print("Site: ", window, "\n")