/*	Angshuman Ghosh		2017CS01

Write a program to simulate an orchestra conductor and a group of musicians. The musicians play independently but
are coordinated by the conductor. For each measure of music indicated by the conductor’s baton,
the musicians play a set of notes. The musicians do not move onto the next measure until indicated
by the conductor’s baton. The Orchestra is called the Narcolepsy Symphony Orchestra because
occasionally a musician falls asleep. When this happens the rest of the musicians continue playing.
When the sleeping musician wakes up, the musician begins playing again with the orchestra.


The solution is done similar to that of a classical readers writers problem

*/



#include <iostream>
#include <fcntl.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define MUSICIANS 6

using namespace std;




sem_t m;		// semaphore to allow a certain number of readers in the system at once
sem_t lock;		// semaphore to allow atomic reading and writing of a particular variable
sem_t mlock;	// semaphore to atomically modify the number of readers currently in system


int m_count = 0;
int measure;	// the current measure



void * musician(void * v){

	int * id = (int *)v;
	int last = -1;


	while(measure != 20){

		sleep(rand() % 5);	// sleep a randoma mount of time

		sem_wait(&m);		// wait on the number of max allowed readers

		sem_wait(&mlock);	// wait on the lock to register the arrival of a reader

		m_count++;

		if(m_count == 1)
			sem_wait(&lock);	// lock the measure variable when first reader arrives

		sem_post(&mlock);		// unlock the reader registering lock

		if(measure != last){
			cout << "Thread " << *id << " playing measure " << measure << endl;	// read the measure value
			last = measure;
		}

		sleep(1);

		sem_wait(&mlock);	// reacquire the register lock to decrement the number of readers currently in system

		m_count--;

		if(m_count == 0)
			sem_post(&lock);	// release the lock for accessing file so that a writer waiting can start writing

		sem_post(&mlock);

		sem_post(&m);		// signal any other waiting readers

	}


}


int main(){

	pthread_t musicians[MUSICIANS];

	sem_init(&m, 0, (MUSICIANS * 3) / 4);	// allow only 75% of readers at a time
	sem_init(&lock, 0 , 1);
	sem_init(&mlock, 0 , 1);

	for(int i = 0; i < MUSICIANS ; i++){

		pthread_create(&musicians[i], NULL, musician, (void *) new int(i));
	}

	for(int i = 0 ; i <= 20 ; i++){

		sem_wait(&lock);	// acquire lock to change the shared measure variable

		measure = i;

		sem_post(&lock);	// release the lock

		sleep(1);
	}


	for(int i = 0; i < MUSICIANS ; i++){

		pthread_join(musicians[i], NULL);
	}

	sem_destroy(&lock);
	sem_destroy(&mlock);
	sem_destroy(&m);


}