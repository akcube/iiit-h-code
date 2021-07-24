#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<stdbool.h>
#include<iostream>
#include"badhash.h"
#include "bloom_filter.h"

using namespace std;

int main(int argc, char *argv[]){

	FILE *file = fopen(argv[1], "r");
	char tword[48];

	hashChaining* table = createhashChaining();		
	while(!feof(file)){
		fscanf(file, "%s", tword);
		insert(table, tword);
	}


	file = fopen(argv[2], "r");

    // Prepare to report misspellings
    printf("\nMISSPELLED WORDS\n\n");

    // Prepare to spell-check
    int index = 0, misspellings = 0, words = 0;
    char word[48];

    int ct = 0;
    // Spell-check each word in text
    for (int c = fgetc(file); c != EOF; c = fgetc(file))
    {
        // Allow only alphabetical characters and apostrophes
        if (isalpha(c) || (c == '\'' && index > 0))
        {
            // Append character to word
            word[index] = c;
            index++;

            // Ignore alphabetical strings too long to be words
            if (index > 47)
            {
                // Consume remainder of alphabetical string
                while ((c = fgetc(file)) != EOF && isalpha(c));
                // Prepare for new word
                index = 0;
            }
        }
        // Ignore words with numbers (like MS Word can)
        else if (isdigit(c))
        {
            // Consume remainder of alphanumeric string
            while ((c = fgetc(file)) != EOF && isalnum(c));
            // Prepare for new word
            index = 0;
        }
        // We must have found a whole word
        else if (index > 0)
        {
            // Terminate current word
            for(int j=index; j<48; j++)
                word[j] = '\0';
            // Update counter
            words++;
            // Check word's spelling
            bool misspelled;

            #ifdef WITHBLOOM
                if(!bloomCheck((unsigned char*)word)){
                    printf("BLOOM: %s\n", word);
                    misspellings++;
                    index = 0;
                    ct++;
                    continue;
                }
            #endif
            
            misspelled = !find(table, word);
            
            // Print word if misspelled
            if (misspelled)
            {
                printf("%s\n", word);
                misspellings++;
            }

            // Prepare for next word
            index = 0;
        }
    }

    cerr<<ct<<"/"<<misspellings<<endl;

}