#ifndef __SIM_UTILS
#define __SIM_UTILS

#define RED "\x1B[31m"
#define GREEN "\x1B[32m"
#define YELLOW "\x1B[33m"
#define BLUE "\x1B[34m"
#define PINK "\x1B[35m"
#define CYAN "\x1B[36m"
#define WHITE "\x1B[37m"
#define RESET "\x1B[0m"

typedef struct pair{
	void *first;
	void *second;
} pair;

int get_time();
struct timespec getTimespec(int t);
void cprintf(const char *color, const char *format, ...);

#endif