#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>
#include <sys/wait.h>


int stop;
void alarm_handler(int signum)
{
	stop=1;
}


int main(int argc, char *argv[])
{

	signal(SIGALRM,alarm_handler);
	while(1)
	{
		stop=0;
		alarm(1);
		for(int i=0;stop==0;i++)
		{
			printf("%d\n",i);
		}
	
	}

	return EXIT_SUCCESS;
}
