#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>

int main(int argc, char *argv[])
{
	char input[100];
	int mypid;

	while(1){
		printf("Please insert some text:\n");
		fgets(input,100,stdin);
		
		//Child fork	
		if(	fork() == 0){
			mypid = getpid();
			printf("SON my PID is %d\n", mypid);
			printf("The string is : %s\n",input);
			kill(mypid, SIGSTOP);
			printf("SON Exiting %d\n", mypid);
		}	

	}
	return EXIT_SUCCESS;

}
