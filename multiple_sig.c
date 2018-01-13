/*	Angshuman Ghosh	2017CS01	Date:23-10-2017

Program to demonstrate the various termination signals and ways to handle them

*/



#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void term(int sig){

	//	ignore the signals so that furthur interruptions does not occur while handling this handler

	signal(SIGINT, SIG_IGN);
	signal(SIGHUP, SIG_IGN);
	signal(SIGTERM, SIG_IGN);

	switch(sig){

		case SIGQUIT:
			printf("\nCaught SIGQUIT signal .... exiting\n");
			exit(0);
			break;
		case SIGINT:
			printf("\nCaught SIGINT signal\n");
			break;
		case SIGHUP:
			printf("\nCaught SIGHUP signal\n");
			break;
		case SIGTERM:
			printf("\nCaught SIGTERM signal\n");
			break;

	}

	
	//	reinstall the signals for furthur usage

	signal(SIGINT, term);
	signal(SIGHUP, term);
	signal(SIGTERM, term);
}


int main(){

	
	//	install the signals
	
	signal(SIGINT, term);
	signal(SIGHUP, term);
	signal(SIGTERM, term);
	signal(SIGQUIT, term);


	while(1){

		sleep(2);
		printf("Still alive\n");
	}

	return 0;
}
