#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>


int main(int argc, char *argv[])
{
	char input[100];
	int mypid,i;
	
	for(i=0;i<10;i++){
				
		//Child fork	
		if(	fork() == 0){
			mypid = getpid();
			srandom(time(NULL));
			int t;
			t=random()%10^i;
			sleep(t);
			printf("I slept for %d seconds. SON %d PID is %d\n",t,i, mypid);
			kill(mypid, SIGSTOP);
			printf("SON Exiting %d\n", mypid);
		}	

	}
	sleep(15);

	return EXIT_SUCCESS;
}
