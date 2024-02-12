#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main (){
	
	srand(time(NULL));
	int r;
	for(int i = 0; i < 10000; i++){
		r = rand()%100;
		if(r%2==0)
			printf("Number %d is multiple of 2\n",r);
		if(r%3==0)
			printf("Number %d is multiple of 3\n",r);
		if(r%5==0)
			printf("Number %d is multiple of 5\n",r);
		if(r%7==0)
			printf("Number %d is multiple of 7\n",r);
	}

	return EXIT_SUCCESS;
}
