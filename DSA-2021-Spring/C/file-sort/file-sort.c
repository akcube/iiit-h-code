#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>

#define dtype uint64_t

void print_arr(dtype N, dtype arr[]){
	//printf("\n\n");
	for(dtype i=0; i<N; i++){
		printf("%ld\n", arr[i]);
	}
	//printf("\n");
}

void radix_sort(char* filename, dtype *largest){
	
	dtype max; 
    FILE *fptr = fopen(filename, "r");
	dtype inp;
	uint64_t size = 0;

    if(fptr == NULL){
    	puts("Please mention a valid file name");
    	return;
    }

	if(largest!=NULL){
		max = *largest;
	}
	else{
		fscanf(fptr, "%ld", &max);
		rewind(fptr);
		while(fscanf(fptr, "%ld", &inp) != EOF){
			max = (inp>max)?inp:max;
			size++;
		}
	}

	uint64_t *digit_count = malloc(sizeof(uint64_t)*10);
	uint64_t *offset = malloc(sizeof(uint64_t)*10);
	
	FILE *temp = fopen("temp", "wb+");
	ftruncate(fileno(temp), size*sizeof(uint64_t));

	memset(digit_count, 0, sizeof(uint64_t)*10);
	memset(offset, 0, sizeof(uint64_t)*10);

	rewind(fptr);
	while(fscanf(fptr, "%ld", &inp) != EOF){
		digit_count[(inp%10)]++;
	}
	for(int i=1; i<10; i++){
		digit_count[i] += digit_count[i-1];
	}
	rewind(fptr);
	while(fscanf(fptr, "%ld", &inp) != EOF){
		uint8_t dig = inp%10;
		uint64_t index = (dig>0)?digit_count[dig-1]:0;
		fseek(temp, (index+offset[dig])*sizeof(uint64_t), SEEK_SET);
		fwrite(&inp, sizeof(uint64_t), 1, temp);
		offset[dig]++;
	}

	remove(filename);

	FILE *temp2 = fopen("temp2", "wb+");
	ftruncate(fileno(temp2), size*sizeof(uint64_t));

	//O(k)
	for(uint64_t radix = 10; max/radix > 0; radix*=10){
		
		memset(digit_count, 0, sizeof(uint64_t)*10);
		memset(offset, 0, sizeof(uint64_t)*10);
		rewind(temp);
		rewind(temp2);
		while(fread(&inp, sizeof(uint64_t), 1, temp) != 0){
			digit_count[((inp/radix)%10)]++;
		}

		for(int i=1; i<10; i++){
			digit_count[i] += digit_count[i-1];
		}
		rewind(temp);
		while(fread(&inp, sizeof(uint64_t), 1, temp) != 0){
			uint8_t dig = ((inp/radix)%10);
			uint64_t index = (dig>0)?digit_count[dig-1]:0;
			fseek(temp2, (index+offset[dig])*sizeof(uint64_t), SEEK_SET);
			fwrite(&inp, sizeof(uint64_t), 1, temp2);
			offset[dig]++;
		}

	    FILE *t = temp;
	    temp = temp2; 
	    temp2 = t;		
	}

	remove("temp2");

	fclose(fptr);
	rewind(temp);
	fptr = fopen(filename, "w+");


	while(fread(&inp, sizeof(uint64_t), 1, temp) != 0){
		//printf("%ld\n", inp);
		fprintf(fptr, "%ld\n", inp);
	}

	remove("temp");

}


int main(int argc, char *argv[]){
	dtype largest = 1L;
    radix_sort(argv[1], NULL);        
}
