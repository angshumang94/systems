/*	Angshuman Ghosh		2017CS01	Date:23-10-2017

Program to catch the SIGCHLD signal in the parent which is created when child exits to evoke a handler
that prints the return code of the child  process

*/


#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>



void term(int sig){

	int rv;

	wait(&rv);	// get the return code of the child

	printf("Child returned value : %d\n",WEXITSTATUS(rv));

	exit(0);

}



int main(){

	int rv;

	signal(SIGCHLD, term);	// install signal

	switch(fork()){		// create child

		case -1:
			printf("Child spawn unsuccessful\n");
			return 1;
		case 0:
			printf("Child spawned with pid = %d\n", getpid());
			sleep(3);
			printf("Child exiting ... enter return value : ");
			scanf("%d",&rv);
			exit(rv);
		default:
			printf("Spawned child\n");
			while(1);			// wait for child to terminate
	}

	return 0;
}
