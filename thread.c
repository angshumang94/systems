/* Angshuman Ghosh 2017CS01 Date- 09/10/2017

Creates 10 concurrent threads, main program waits for threads to complete before exiting */



#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define THREAD_NUM 10



void * mythread(void * n){

	int i,num = *(int *) n;	//cast void pointer argument to int


	for(i=0 ; i<5 ; i++){	// print hello world five times

		printf("Hello World , Thread ID = %lu and Thread Number = %d\n", pthread_self(), num);
		sleep(1);
	}

	return NULL;
}

int main(){

	int i;

	int * num;	// pointer storing address of location containing thread number

	pthread_t thread[THREAD_NUM];	// array of pthread_t thread IDs

	for(i=0 ; i < THREAD_NUM ; i++){	// create 10 concurrent threads

		num = (int *)malloc(sizeof(int));	// allocate memory for thread number
		*num = i;

		pthread_create(&thread[i], NULL, mythread, num);	// create thread

		//sleep(1);
	}


	for(i=0 ; i < THREAD_NUM ; i++){	// join all the 10 threads created before exiting

		pthread_join(thread[i], NULL);
	}

	printf("Main exiting\n");	// Exit messege


}