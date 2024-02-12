#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>
#include <sys/wait.h>

#define MAX_KIDS 10

int main(int argc, char *argv[])
{
	char input[100];
	int mypid,i,pid,child_nap;
	int list_childs[10];
	
	for(i=0;i< MAX_KIDS ;i++){
				
		pid = fork();
		if(pid == -1)
		{
			printf("couldn't fork, exiting with error");
			exit(EXIT_FAILURE);
		}
		else if(pid == 0){	//Child fork
			mypid = getpid();
			srandom(time(NULL));
			int t;
			t=(random()^i)%10;
			sleep(t);
			printf("I slept for %d seconds. SON %d PID is %d\n",t,i, mypid);
			exit(t);
			kill(mypid, SIGSTOP);
			printf("SON Exiting %d\n", mypid);
		}
		list_childs[i]=pid;
	}
	
	int woken_kids=0;
	i=0;
	while(woken_kids<MAX_KIDS)
	{
		
		if(	waitpid(list_childs[i],&child_nap,WNOHANG)>0)
		{
			printf("My child %d slept for %d seconds\n",list_childs[i],child_nap);
			woken_kids++;
		}
		i++;
		if(i==MAX_KIDS)
			i=0;

	}


	return EXIT_SUCCESS;
}
