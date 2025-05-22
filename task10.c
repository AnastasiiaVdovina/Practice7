#include <stdio.h>
#include <stdlib.h>
#include <time.h>

double rand_0_1(){
	return (double)rand() / (double)RAND_MAX;
}

double rand_0_n(double n){
	return rand_0_1() * n;
}

void print_random_numbers(double max_value, int count){
	for(int i = 0; i < count; i++){
		double value = rand_0_n(max_value);
		printf("%.2f\n", value);	
	}
}


int main(){
	srand(time(NULL));
	int count = 10;
	double max_1 = 1.0; //for range [0;1];
	double max_2 = 3.5; //for range [0;n];
	
	printf("10 random numbers in the range [0;%.1f]: \n", max_1);
	print_random_numbers(max_1, count);

	printf("10 random numbers int the range [0;%.1f]: \n", max_2);
	print_random_numbers(max_2, count);

	return 0;

}

