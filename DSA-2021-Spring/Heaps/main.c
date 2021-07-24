#include<stdio.h>
#include<stdlib.h>
#include "heaps.h"

typedef long long ll;

int main(void){
	Heap minHeap, maxHeap;

	createHeap(2, MINHEAP, &minHeap);
	createHeap(2, MAXHEAP, &maxHeap);
	
	abc.insert(n);

	int n;
	scanf("%d", &n);

	double currMedian = 0;
	while(n!=0){

		//insertion
		if(n >= currMedian)
			minHeap.insert(n, &minHeap);
		else
			maxHeap.insert(n, &maxHeap);

		//balancing
		if(minHeap.size > maxHeap.size+1)
			maxHeap.insert(minHeap.pop(&minHeap), &maxHeap);
		else if(maxHeap.size > minHeap.size+1)
			minHeap.insert(maxHeap.pop(&maxHeap), &minHeap);

		//get average
		if(minHeap.size==maxHeap.size)
			currMedian = ((double)minHeap.getTop(&minHeap)+maxHeap.getTop(&maxHeap))/2;
		else if(minHeap.size > maxHeap.size)
			currMedian = minHeap.getTop(&minHeap);
		else
			currMedian = maxHeap.getTop(&maxHeap);
		
		printf("%lf\n", currMedian);
		scanf("%d", &n);
	}

	deleteHeap(&minHeap);
	deleteHeap(&maxHeap);
}