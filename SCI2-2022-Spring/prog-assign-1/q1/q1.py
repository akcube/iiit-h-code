from biolib import CodonTable, utils

f = open("input.txt","r")                                             # Displaying the DNA sequence
DNA = f.read()
f.close()
print("\nInput DNA Sequence: ", DNA, "\n")

mRNA = utils.DNAtomRNA(DNA)
print("mRNA Sequence: ", mRNA, "\n\n")

proteins = []
st = 0
while st < len(mRNA):
	if(mRNA[st:st+3] in CodonTable.START):
		protein = ""
		fin = -1
		for it in range(st, len(mRNA), 3):
			codon = mRNA[it:it+3]
			if(codon in CodonTable.STOP):
				pfound = True
				fin = it
				break
			elif len(codon) == 3:
				protein += CodonTable.mp[codon] + " "
		if fin != -1:
			print("Protein number: ", len(proteins)+1)
			print("RNA Sequence number: ", st+1, " : ", fin)
			print("mRNA strand: ", mRNA[st:fin])
			print("Synthesized protein: ", protein, "\n")
			proteins.append(protein)
	st += 1
