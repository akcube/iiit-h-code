#include<stdio.h>
#include<stdint.h>
#include<string.h>
#include<ctype.h>
#include<stdbool.h>
#include"hashtable.h"
#include"bloom_filter.h"



int main(int argc, char *argv[]){
	
    cw_load(argv[1]);

    FILE *file = fopen(argv[2], "r");

    // Prepare to report misspellings
    printf("\nMISSPELLED WORDS\n\n");

    // Prepare to spell-check
    int index = 0, misspellings = 0, words = 0;
    char word[48];

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
                    continue;
                }
            #endif
            
            misspelled = !check(word);
            
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

    printf("%d\n", misspellings);

}