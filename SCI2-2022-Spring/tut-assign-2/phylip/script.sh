#!/bin/bash.

# ---------------------------------------------------
# 						Usage
# ---------------------------------------------------
# Create the following directory structure and then 
# run the script by running `source script.sh` on the
# terminal.
# .
# ├── dna.phylip
# ├── fontfile
# ├── protein.phylip
# └── script.sh

# Initialize vars
protfile="protein.phylip"
dnafile="dna.phylip"

# Make directories
mkdir non-bootstrapped
mkdir non-bootstrapped/dna
mkdir non-bootstrapped/protein

mkdir bootstrapped
mkdir bootstrapped/dna
mkdir bootstrapped/protein

# ---------------------------------------------------
# 			NON-BOOTSTRAPPED
# ---------------------------------------------------

# Protein stuff

# Protdist 
cp $protfile infile
yes | protdist 
mv outfile infile
yes | neighbor 
mv outfile non-bootstrapped/protein/ASCII_Protdist.txt
mv outtree intree
yes | drawtree
mv plotfile non-bootstrapped/protein/Protdist
rm infile intree

# Protpars
cp $protfile infile
yes | protpars 
mv outfile non-bootstrapped/protein/ASCII_Protpars.txt
mv outtree intree
yes | drawtree
mv plotfile non-bootstrapped/protein/Protpars
rm infile intree

# Proml
cp $protfile infile
yes | proml 
mv outfile non-bootstrapped/protein/ASCII_Proml.txt
mv outtree intree
yes | drawtree
mv plotfile non-bootstrapped/protein/Proml
rm infile intree

# DNA stuff

# DNAdist
cp $dnafile infile
yes | dnadist 
mv outfile infile
yes | neighbor 
mv outfile non-bootstrapped/dna/ASCII_Dnadist.txt
mv outtree intree
yes | drawtree
mv plotfile non-bootstrapped/dna/Dnadist
rm infile intree

# DNAPars
cp $dnafile infile
yes | dnapars 
mv outfile non-bootstrapped/dna/ASCII_Dnapars.txt
mv outtree intree
yes | drawtree
mv plotfile non-bootstrapped/dna/Dnapars
rm infile intree

# DNAml
cp $dnafile infile
yes | dnaml 
mv outfile non-bootstrapped/dna/ASCII_Dnaml.txt
mv outtree intree
yes | drawtree
mv plotfile non-bootstrapped/dna/Dnaml
rm infile intree

# ---------------------------------------------------
# 				BOOTSTRAPPED
# ---------------------------------------------------

# Protein stuff
 
# Bootstrap
cp $protfile infile
echo "Y\n1331\n" | seqboot 
mv outfile seqfile

# Protdist
cp seqfile infile
echo "M\nD\n100\nY\n" | protdist 
mv outfile infile
echo "M\n100\n1331\nY\n" | neighbor 
rm outfile
mv outtree intree
yes | consense
mv outfile bootstrapped/protein/ASCII_Protdist.txt
mv outtree intree
yes | drawtree 
mv plotfile bootstrapped/protein/Protdist
rm infile intree

# Protpars
cp seqfile infile
echo "M\nD\n100\n1331\n3\nY\n" | protpars
rm outfile
mv outtree intree
yes | consense
mv outfile bootstrapped/protein/ASCII_Protpars.txt
mv outtree intree
yes | drawtree
mv plotfile bootstrapped/protein/Protpars
rm infile intree

# Proml
cp seqfile infile
echo "M\nD\n100\n1331\n3\nY\n" | proml
rm outfile
mv outtree intree
yes | consense
mv outfile bootstrapped/protein/ASCII_Proml.txt
mv outtree intree
yes | drawtree
mv plotfile bootstrapped/protein/Proml
rm infile intree

# Cleanup
rm seqfile

# DNA stuff

# Bootstrap
cp $dnafile infile
echo "Y\n1331\n" | seqboot 
mv outfile seqfile

# DNAdist
cp seqfile infile
echo "M\nD\n100\nY\n" | dnadist 
mv outfile infile
echo "M\n100\n1331\nY\n" | neighbor 
rm outfile
mv outtree intree
yes | consense
mv outfile bootstrapped/dna/ASCII_Dnadist.txt
mv outtree intree
yes | drawtree 
mv plotfile bootstrapped/dna/Dnadist
rm infile intree

# DNApars
cp seqfile infile
echo "M\nD\n100\n1331\n3\nY\n" | dnapars
rm outfile
mv outtree intree
yes | consense
mv outfile bootstrapped/dna/ASCII_Dnapars.txt
mv outtree intree
yes | drawtree
mv plotfile bootstrapped/dna/Dnapars
rm infile intree

# DNAml
cp seqfile infile
echo "M\nD\n100\n1331\n3\nY\n" | dnaml
rm outfile
mv outtree intree
yes | consense
mv outfile bootstrapped/dna/ASCII_Dnaml.txt
mv outtree intree
yes | drawtree
mv plotfile bootstrapped/dna/Dnaml
rm infile intree

# Cleanup
rm seqfile