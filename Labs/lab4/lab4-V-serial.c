#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#define MAXNUM 10



void *mult(void* arg){// vec[], int len, int n){
	//Our argument is a vector of pointers
	void **args=arg;
	int i;
	
	// by design the first position points to an integer
	int n = *(int*)args[0];
	// by design the second position points to a vector of int
	int *vec = (int*)args[1];
	for(i=0; i<MAXNUM; i++){
		if(vec[i]%n == 0)
			printf("mult %d %d\n", n, vec[i]);
		else
			printf("- %d not multiple of %d -\n",vec[i],n);
	}

	int* ptr=malloc(sizeof(int));
	*ptr = n;
	pthread_exit(ptr);
	return NULL;
}

int main(){
	int *num_vec;
	int i,n,max_num=MAXNUM,n_threads=4;
	int numbers[4]={2,3,5,7};

	pthread_t thread_ids[4];
	void *thread_args[4][2]={{NULL}};


	num_vec= malloc(sizeof(int)*MAXNUM);
	if(num_vec==NULL){
		exit(-1);
	}

	for(i=0; i< MAXNUM; i++){
		num_vec[i]= random()%20;
	}


	for (n= 0; n < n_threads; n++)
	{
		thread_args[n][0]=&numbers[n];
		thread_args[n][1]=num_vec;
    	pthread_create(&thread_ids[n], NULL, mult, thread_args[n]);
	}

/*
	mult(num_vec, MAXNUM, 2);
	mult(num_vec, MAXNUM, 3);
	mult(num_vec, MAXNUM, 5);
	mult(num_vec, MAXNUM, 7);
*/
	void* val;
	for(n=0;n<n_threads;n++)
	{
		pthread_join(thread_ids[n],&val);
		if (val != 0) {
			printf("thread %d - %d\n",n,*(int*)val);
			free(val);
		} else {
   			printf("thread failed\n");
   		}
	}
	free(num_vec);
	exit(0);
}
