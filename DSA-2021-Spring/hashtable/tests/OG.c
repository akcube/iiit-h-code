// Implements a dictionary's functionality
#define _GNU_SOURCE

#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

#include <immintrin.h>

#include "dictionary.h"

// Represents a node in a hash table
struct node
{
    uint32_t me:24;
}__attribute__((packed));
typedef struct node node;


#define N 524288
#define NN 524287
#define SHIFT 12
#define DJBCONST 5381 //0xcc9e2d51
// Number of buckets in hash table
//const int N = 1048576; //30389 //79283 //86269 //143063 //131072 //262144 //524288 //1048576
unsigned int sizex;
// Hash table
uint32_t table[N];
uint8_t temp_word[LENGTH + 1];
char *file_in_mem;
uint32_t hashval, copy;
uint32_t clusters;
//uint32_t temp[4] = {0x20202020, 0x20202020, 0x20202020, 0x20202020};

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    //__m256i reg256 = _mm256_load_si256 (&word[0]);
    uint64_t hashcode = DJBCONST;
    uint8_t i=0;
    *((uint32_t*)&temp_word[i]) = *((uint32_t*)&word[i]) | 0x20202020;
    for(;((*((uint32_t*)&word[i])-0x01010101) & ~(*((uint32_t*)&word[i])) & 0x80808080) == 0;)
    {
        hashcode = ((hashcode<<5)+hashcode) + *((uint32_t*)&temp_word[i]);
        i+=4;
        *((uint32_t*)&temp_word[i]) = *((uint32_t*)&word[i]) | 0x20202020;
    }

    if(word[i]=='\0'){
    }
    else if(word[i+1]=='\0'){
        hashcode = ((hashcode<<5)+hashcode) + temp_word[i++];
    }
    else if(word[i+2]=='\0'){
        hashcode = ((hashcode<<5)+hashcode) + *((uint16_t*)&temp_word[i]);
        i+=2;
    }
    else{
        hashcode = ((hashcode<<5)+hashcode) + *((uint16_t*)&temp_word[i]);
        hashcode = ((hashcode<<5)+hashcode) + temp_word[i+2];
        i+=3;
    }
    hashcode = ((hashcode>>SHIFT) ^ hashcode) & NN;
    hashval = hashcode;
    temp_word[i++] = '\n';

    for(;table[hashcode]!=0;){
        if(memcmp(&file_in_mem[table[hashcode]], temp_word, i)==0){
            copy = table[hashval];
            table[hashval] = table[hashcode];
            table[hashcode] = copy;
            return true;
        }
        clusters++;
        hashcode = (hashcode * 11400714819323198485llu) >> 45;
    }
    return false;
}

// Hashes word to a number during check routine
unsigned int hash(const char *word)
{
    // Source: https://docs.oracle.com/javase/6/docs/api/java/lang/String.html#hashCode%28%29
    // Hashing technique used by Java

    return 0;
}


// Hashes word to a number
/*unsigned int hash(const char *word)
{
    // Source: https://docs.oracle.com/javase/6/docs/api/java/lang/String.html#hashCode%28%29
    // Hashing technique used by Java
    int ans = 0;
    for (int n = strlen(word), i = 0; i < n; i++)
    {
        ans = (ans * 31 + word[i]) % N;
    }
    return ans;
}
*/
// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{

    //table = mmap(NULL, N*4, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0);
    memset(table, 0, N*4);
    sizex = 0;
    int fd = open(dictionary, O_RDONLY, S_IRUSR | S_IWUSR);
    struct stat sb;

    if(fstat(fd, &sb)==-1)
    {
        printf("Error opening file");
        return false;
    }

    file_in_mem = mmap(NULL, sb.st_size, PROT_READ, MAP_PRIVATE, fd, 0);

    uint64_t ans = DJBCONST;
    uint32_t prev_i = 1;
    for(int i=0; i<sb.st_size;)
    {
        switch(*((uint64_t*)&file_in_mem[i]) & 0x2020202020202020){
            case 0x2020202020202020:
                ans = (((ans << 5) + ans) + *((uint32_t*)&file_in_mem[i]));
                ans = (((ans << 5) + ans) + *((uint32_t*)&file_in_mem[i+4]));
                i += 8;
                continue;
        }

        if(file_in_mem[i]==10){
            i++;
        }
        else if(file_in_mem[i+1]==10){
            ans = (((ans << 5) + ans) + file_in_mem[i]);// & NN;
            i+=2;
        }
        else if(file_in_mem[i+2]==10){
            ans = (((ans << 5) + ans) + *((uint16_t*)&file_in_mem[i]));// & NN;
            i+=3;
        }
        else if(file_in_mem[i+3]==10){
            ans = (((ans << 5) + ans) + *((uint16_t*)&file_in_mem[i]));// & NN;
            ans = (((ans << 5) + ans) + file_in_mem[i+2]);// & NN;
            i+=4;
        }
        else if(file_in_mem[i+4]==10){
            ans = (((ans << 5) + ans) + *((uint32_t*)&file_in_mem[i]));
            i+=5;
        }
        else if(file_in_mem[i+5]==10){
            ans = (((ans << 5) + ans) + *((uint32_t*)&file_in_mem[i]));
            ans = (((ans << 5) + ans) + file_in_mem[i+4]);// & NN;
            i+=6;
        }
        else if(file_in_mem[i+6]==10){
            ans = (((ans << 5) + ans) + *((uint32_t*)&file_in_mem[i]));
            ans = (((ans << 5) + ans) + *((uint16_t*)&file_in_mem[i+4]));// & NN;
            i+=7;
        }
        else if(file_in_mem[i+7]==10){
            ans = (((ans << 5) + ans) + *((uint32_t*)&file_in_mem[i]));
            ans = (((ans << 5) + ans) + *((uint16_t*)&file_in_mem[i+4]));// & NN;
            ans = (((ans << 5) + ans) + file_in_mem[i+6]);// & NN;
            i+=8;
        }
            ans = ((ans>>SHIFT) ^ ans) & NN;
            for(;table[ans]!=0;){
                ans = (ans * 11400714819323198485llu) >> 45;
            }
            table[ans] = prev_i;
            ans = DJBCONST;
            sizex++;
            prev_i = i + 1;
    }
    close(fd);
    file_in_mem--;
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return sizex;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    printf("Clusters: %i\n", clusters);
    //free(table);
    /*
    int clusters = 0;
    int arr[131072] = {0};
    int filled = 0;
    int totalhits = 0;
    float avglen = 0;
    int maxlen = 0;
    int emptybuckets;
    int freq[15] = {0};
    for(int i=0; i<N; i++){
        if(table[i]!=NULL)
        {
            if(table[i]->next!=NULL){
                clusters++;
            }
            filled++;
        }
        for(node *curr = table[i]; curr != NULL; curr = curr->next){
            arr[i]++;
        }
        freq[arr[i]]++;
        totalhits += arr[i];
        maxlen = (arr[i]>maxlen)?arr[i]:maxlen;
    }
    avglen = (float) totalhits / filled;
    emptybuckets = N-filled;
    printf("Clusters                :%i\n", clusters);
    printf("Filled                  :%i\n", filled);
    printf("Avg len                 :%f\n", avglen);
    printf("Max len                 :%i\n", maxlen);
    printf("Empty buckets           :%i\n", emptybuckets);
    printf("Frequency distribution:\n");
    for(int i=1; i<15; i++){
        printf("Number of %i's                :%i\n", i, freq[i]);
    }*/
    return true;
}