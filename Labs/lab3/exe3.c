#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
	char input[100];
	int mypid,i,pid,child_nap;
	
	for(i=0;i<10;i++){
				
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
		}else{ //Parent fork
			wait(&child_nap);
			printf("My child %d slept for %d seconds\n",pid,child_nap);

		}

	}

	return EXIT_SUCCESS;
}
