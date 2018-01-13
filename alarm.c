/*	Angshuman Ghosh		2017CS01	Date:23-10-2017

Program to catch alarm signals a predetermined number of counts


*/


#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

int count = 0;

void term(int sig){

	signal(SIGALRM, SIG_IGN);	// ignore alarm signal interrupts for this handler

	if(sig == SIGALRM){

		printf("\nCaught alarm signal\n");
		count++;
		if(count == 5){					// keep count
			printf("\nCount is 5 exiting\n");
			exit(0);
		}
	}

	signal(SIGALRM, term);		// reinstall the signal 
}


int main(){

	signal(SIGALRM, term);


	while(1){

		sleep(2);
		printf("!!!!	Generating alarm	!!!!\n");
		alarm(2);						// generate alarm
	}

	return 0;
}
