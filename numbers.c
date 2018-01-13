/*	Angshuman Ghosh 2017CS01

*/


#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
pthread_mutex_t mlock;								// Mutex Lock Variable.
pthread_cond_t vlock;								// Contion Lock Variable.
int counter = 1;



void* func(void *arg) {								// Function prints the value of counter when it is even
	while(1) {
		pthread_mutex_lock(&mlock);				// Locking.
		printf("Second Thread : %d\n",counter);
		counter++;
		pthread_cond_signal(&vlock);
		if(counter < 2001 && counter%2 != 0)
			pthread_cond_wait(&vlock, &mlock);
		
		pthread_mutex_unlock(&mlock);				// Unlocking
		if(counter >= 2001) {
			pthread_cond_signal(&vlock);
			break;
		}
	}
	pthread_exit(NULL);
}




int main() {
	pthread_t tid;											// To hold the thread id.
	pthread_create(&tid, NULL, &func, NULL);   				// Creating thread. 
	while(1) {
		pthread_mutex_lock(&mlock);							// Locking
		pthread_cond_signal(&vlock);
		if(counter%2 == 0)
			pthread_cond_wait(&vlock, &mlock);				// Waiting for Second Thread to print
		
		printf("Main Thread : %d\n",counter);
		counter++;
		pthread_mutex_unlock(&mlock);						// Unlocking
		if(counter >= 2000) {
			pthread_cond_signal(&vlock);					// Signalling based on a condition	
			break;
		}
	}
	pthread_join(tid, NULL); 								// Joining of thread.
	pthread_mutex_destroy(&mlock);   						// Destroying mutex lock.
	pthread_cond_destroy(&vlock);							// Destroying condition lock.
	return 0;
}
