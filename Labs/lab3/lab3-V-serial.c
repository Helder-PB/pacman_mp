#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>
#include <sys/wait.h>

#include <time.h>
#define MAXNUM 1000000
#define MAX_KIDS 4

void mult(int vec[], int len, int n){
  int i;
  for(i=0; i< len; i++){
    if(vec[i]%n == 0)
      printf("mult %d %d\n", n, vec[i]);
  }
}

int main(){
  int *num_vec;
  int i;
  int primes[MAX_KIDS]={2,3,5,7};
  int list_kids[MAX_KIDS];
  num_vec= malloc(sizeof(int)*MAXNUM);
  if(num_vec==NULL){
    exit(-1);
  }

  for(i=0; i< MAXNUM; i++){
    num_vec[i]= random();
  }

	time_t ptr_start_fork, ptr_end_fork;
	time_t ptr_start_serial,ptr_end_serial;
	
	clock_t clock_start_fork,clock_end_fork;
	clock_t clock_start_serial,clock_end_serial;

	ptr_start_fork = time(NULL);
	clock_start_fork = clock();
	
	for(i=0;i<MAX_KIDS;i++)
	{
		int pid = fork();
		if(pid == 0){
			  mult(num_vec, MAXNUM, primes[i]);
			exit(0);
		}
		list_kids[i]=pid;
	}

	int child_nap,woken_kids=0;
	i=0;
	while(woken_kids<MAX_KIDS)
	{
		
		if(	waitpid(list_kids[i],&child_nap,WNOHANG)>0)
		{
			printf("PID- %d - My child %d ended\n",list_kids[i],primes[i]);
			woken_kids++;
		}
		i++;
		if(i==MAX_KIDS)
			i=0;

	}

	ptr_end_fork = time(NULL);
	clock_end_fork = clock();

	
	ptr_start_serial = time(NULL);
	clock_start_serial = clock();

  mult(num_vec, MAXNUM, 2);
  mult(num_vec, MAXNUM, 3);
  mult(num_vec, MAXNUM, 5);
  mult(num_vec, MAXNUM, 7);

	ptr_end_serial = time(NULL);
	clock_end_serial = clock();
	printf("With fork time: %f seconds\n",difftime(ptr_end_fork,ptr_start_fork));
	printf("With serial time: %f seconds\n",difftime(ptr_end_serial,ptr_start_serial));

	printf("With fork clock: %f seconds\n",((float) (clock_end_fork-clock_start_fork)) / CLOCKS_PER_SEC);
	printf("With serial time: %f seconds\n",((float) (clock_end_serial-clock_start_serial)) / CLOCKS_PER_SEC);


  exit(0);
}
