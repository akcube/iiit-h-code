#include <time.h>

#include "../include/utils.h"
#include "../include/global.h"

int get_time(){
	struct timespec finish;
	clock_gettime(CLOCK_REALTIME, &finish);
	long long sec = (finish.tv_sec - start.tv_sec);
	long long nsec = (finish.tv_nsec - start.tv_nsec);
	if(sec > 0 && nsec < 0) return sec-1;
	else if(sec < 0 && nsec > 0) return sec + 1;
	return sec;
}

struct timespec getTimespec(int t){
	struct timespec retval;
	retval.tv_sec = start.tv_sec + t;
	retval.tv_nsec = start.tv_nsec;
	return retval;
}