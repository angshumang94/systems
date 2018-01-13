/* Angshuman Ghosh 2017CS01 Date- 09/10/2017

Creates thread which calculates roots of integers from 0 to 99 , displays the results from main function */



#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <pthread.h>


void * find_roots(void * n){	// function modifies double array whose reference is passed as argument

	int i;

	double * roots = (double *)n;	// cast void pointer to double

	for(i=0 ; i<100 ; i++){	

		roots[i] = sqrt(i);	// store root values
	}

	return NULL;
}


int main(){

	int i;
	double * roots = (double *)malloc(sizeof(double) * 100);

	pthread_t thread;	// array of pthread_t thread IDs

	printf("Main : Starting calculating roots\n");

	pthread_create(&thread, NULL, find_roots, (void *)roots);	// create thread

	pthread_join(thread, NULL);	// join thread , get result array

	for(i=0 ; i< 100 ; i++){

		printf("Root of %d = %f\n",i,roots[i]);	// Print result array
	}

	printf("Main exiting\n");	// Exit messege


}