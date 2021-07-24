#ifndef __BLOOM_FILTER
#define __BLOOM_FILTER

void bloomAdd(unsigned char *word);
bool bloomCheck(unsigned char *word);

#endif