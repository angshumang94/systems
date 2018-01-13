/*	Angshuman Ghosh		2017CS01


This program tries to simulate a producer/consumer problem using semaphores. You will use
the pthread package to create 4 producer threads and 4 consumer threads. Each producer thread
attempts to insert character ’X’ into a circular buffer of size 3,000,000 characters. Each consumer
thread tries to removes a character from the buffer.

*/


#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <semaphore.h>
#include <sys/mman.h>

#define MAX 300000
#define ITERATIONS 3

using namespace std;

char sbuff[MAX + 1];	// create character buffer
int count = 0;


sem_t lock;				// lock to change the buffer
sem_t empty_buff;		// semaphore to track number of empty slots
sem_t full_buff;		// semaphore to track number of full slots


void * producer(void * v){

	sleep(rand() % 3);

	for(int i = 0 ; i < ITERATIONS ; i++){

		cout << "Producer " << pthread_self() << " waiting to put content" << endl;

		sem_wait(&empty_buff);	// producer waiting for empty space
		sem_wait(&lock); 		// gets lock for changing buffer

		sleep(rand() % 5);

		sbuff[count] = 'X';
		sbuff[++count] = '\0';

		cout << "Producer " << pthread_self() << " has put content " << "Current buffer " << sbuff << endl;

		sem_post(&lock);		// releases lock for buffer
		sem_post(&full_buff);	// signal any consumer waiting for item


	}

}


void * consumer(void * v){

	for(int i = 0 ; i < ITERATIONS ; i++){

		sleep(rand() % 3);

		cout << "Consumer " << pthread_self() << " waiting to get content" << endl;

		sem_wait(&full_buff);	// consumer waiting for item
		sem_wait(&lock); 		// gets lock for changing buffer

		count--;
		sbuff[count] = '\0';

		cout << "Consumer " << pthread_self() << " has got content " << "Current buffer " << sbuff << endl;

		sem_post(&lock);		// releases lock for buffer
		sem_post(&empty_buff);	// signal any producer waiting to put data


	}

}


int main(){

	pthread_t prod[4], cons[4];

	sem_init(&lock, 0 ,1);				// binary semaphore
	sem_init(&empty_buff, 0 , MAX);		// all slots are empty
	sem_init(&full_buff, 0 , 0);		// no full slots

	for(int i = 0 ; i < 4 ; i++){
		pthread_create(&prod[i], NULL, producer, NULL);
		pthread_create(&cons[i], NULL, consumer, NULL);
	}

	for(int i = 0 ; i < 4 ; i++){
		pthread_join(prod[i], NULL);
		pthread_join(cons[i], NULL);
	}

	cout << "Char buffer : " << sbuff << endl;

	sem_destroy(&lock);
	sem_destroy(&empty_buff);
	sem_destroy(&full_buff);

}