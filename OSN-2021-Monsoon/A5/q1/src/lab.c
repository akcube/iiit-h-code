#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/lab.h"

void create_lab(Lab *l){
	l->name = NULL;
	l->num_students = 0;
	l->limit = 0;
	l->available = NULL;
}

void destroy_lab(Lab *l){
	memset(l, 0, sizeof(Lab));
	free(l);
}

void read_labs(Lab *L, int num_labs){
	L = calloc(num_labs, sizeof(Lab));
	char buf[1024];

	for(int i=0; i < num_labs; i++){
		Lab *l = &L[i];
		create_lab(l);
		scanf("%s %d %d", buf, &(l->num_students), &(l->limit));

		l->name = strdup(buf);
		l->available = calloc(l->limit, sizeof(int));

		l->available[0] = l->num_students;
	}
}
