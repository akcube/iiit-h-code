#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <sys/mman.h>
#include "murmur.h"
#include "hashtable.h"
#include "bloom_filter.h"

#define N 524288
#define NN 524287
#define SHIFT 12

p_node *Table;
char *file_in_mem;
uint8_t temp_word[48] __attribute__((aligned(16)));


char *open_file_in_mem(char *filename, int *sz){
	int fd = open(filename, O_RDONLY, S_IRUSR | S_IWUSR);
    struct stat sb;
    if(fstat(fd, &sb)==-1) return NULL;
    *sz = sb.st_size;
    return (char*) mmap(NULL, sb.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
}

bool check(const char *word)
{
    uint64_t h1 = 0;
    uint8_t i=0;
    *((uint64_t*)&temp_word[i]) = *((uint64_t*)&word[i]) | 0x2020202020202020;
    uint64_t k1;
    uint64_t c1 = BIG_CONSTANT(0x87c37b91114253d5);
    for(;((*((uint64_t*)&word[i])-0x0101010101010101) & ~(*((uint64_t*)&word[i])) & 0x8080808080808080) == 0;)
    {
        k1 = *((uint64_t*)&temp_word[i]);
        k1 *= c1; k1  = ROTL64(k1,31);
        h1 ^= k1;
        h1 = ROTL64(h1,27);
        h1 = ((h1<<2)+h1)+0x52dce729;  
        i+=8;
        *((uint64_t*)&temp_word[i]) = *((uint64_t*)&word[i]) | 0x2020202020202020;
    }
    uint64_t len = (*((uint64_t*)&word[i]));
    len = (len-0x0101010101010101) & ~(len) & 0x8080808080808080;
    len =  ((__builtin_ffsl(len))>>3)-1;

    uint8_t *tail = (uint8_t*)&temp_word[i];
    i+=len;

    k1 = 0;
    switch(len){
        case  8: k1 ^= (uint64_t)(tail[7]) << 56;
        case  7: k1 ^= (uint64_t)(tail[6]) << 48;
        case  6: k1 ^= (uint64_t)(tail[5]) << 40;
        case  5: k1 ^= (uint64_t)(tail[4]) << 32;
        case  4: k1 ^= (uint64_t)(tail[3]) << 24;
        case  3: k1 ^= (uint64_t)(tail[2]) << 16;
        case  2: k1 ^= (uint64_t)(tail[1]) << 8;
        case  1: k1 ^= (uint64_t)(tail[0]) << 0;
                 k1 *= c1; 
                 k1  = ROTL64(k1,31); 
                 h1 ^= k1;
    }

    h1 ^= i;
    h1 = fmix64(h1);
    h1 = h1&NN;
    temp_word[i++] = '\n';
    int hashcode = h1;
    for(int j=1;Table[hashcode]!=0;j++){
        if(memcmp(&file_in_mem[Table[hashcode]], temp_word, i)==0){
            int copy = Table[h1];
            Table[h1] = Table[hashcode];
            Table[hashcode] = copy;
            return true;
        }
        //hashcode = (h1 + j*j)&NN;
        // clusters++;
        hashcode = (hashcode * 11400714819323198485llu) >> 45;
    }
    return false;
}

void cw_load(char *filename){
	Table = (p_node*) mmap(NULL, N*sizeof(p_node), PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0);
	int filesize;
    file_in_mem = open_file_in_mem(filename, &filesize);
    uint64_t k1, h1;
    h1 = 0;
    uint32_t prev_i = 1;
    uint64_t c1 = BIG_CONSTANT(0x87c37b91114253d5);
    int curlen = 0;
    for(int i=0; i<filesize;)
    {
        switch(*((uint64_t*)&file_in_mem[i]) & 0x2020202020202020){
            case 0x2020202020202020:
                k1 = *((uint64_t*)&file_in_mem[i]);
                k1 *= c1; k1  = ROTL64(k1,31);
                h1 ^= k1;
				h1 = ROTL64(h1,27);
				h1 = ((h1<<2)+h1)+0x52dce729;	
                i += 8;
                curlen += 8;
                continue;
        }
        uint64_t len = (*((uint64_t*)&file_in_mem[i])) ^ 0x0A0A0A0A0A0A0A0A;
        len = (len-0x0101010101010101) & ~(len) & 0x8080808080808080;
        len =  ((__builtin_ffsl(len))>>3)-1;
        curlen += len;
        uint8_t *tail = (uint8_t*)&file_in_mem[i];
        k1 = 0;
        switch(len){
        	case  8: k1 ^= (uint64_t)(tail[7]) << 56;
 			case  7: k1 ^= (uint64_t)(tail[6]) << 48;
  			case  6: k1 ^= (uint64_t)(tail[5]) << 40;
  			case  5: k1 ^= (uint64_t)(tail[4]) << 32;
  			case  4: k1 ^= (uint64_t)(tail[3]) << 24;
  			case  3: k1 ^= (uint64_t)(tail[2]) << 16;
  			case  2: k1 ^= (uint64_t)(tail[1]) << 8;
  			case  1: k1 ^= (uint64_t)(tail[0]) << 0;
           	         k1 *= c1; 
                     k1  = ROTL64(k1,31); 
                     h1 ^= k1;
        }

        h1 ^= curlen;
        h1 = fmix64(h1);

        i += len+1;

        h1 = h1&NN;
        uint64_t hashval = h1;
        //insert
        for(int j=1;Table[h1]!=0;j++){
            h1 = (h1 * 11400714819323198485llu) >> 45;
            //h1 = (hashval + j*j)&NN;
        }
        Table[h1] = prev_i;
        h1 = 0;
        curlen = 0;
        prev_i = i + 1;
    }
    file_in_mem--;
}

