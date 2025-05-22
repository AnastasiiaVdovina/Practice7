#include <stdio.h>
#include <time.h>

int main(){
	clock_t start = clock();
	
	long long sum = 0;
	for(long long i = 0; i < 100000000; i ++){
		sum += i;
	}

	clock_t end = clock();
	
	double elapsed_time = (double)(end - start) / CLOCKS_PER_SEC;

	printf("Elapsed time: %.2f s\n", elapsed_time);
	
	return 0;
}
