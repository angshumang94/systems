/*	Angshuman Ghosh		2017CS01

Program for atomic incrementing and decrementing of race variable and stooping the program when race becomes 100

*/


#include <iostream>
#include <cstdlib>
#include <list>
#include <pthread.h>
#include <unistd.h>

using namespace std;

int race = 0;
bool flag = false;

pthread_t thread[3];
pthread_mutex_t lock;	// lock variable
pthread_cond_t done;	// condition variable



void * inc(void * v){

	int ret = 0;

	while(flag != true){

		sleep(1);

		pthread_mutex_lock(&lock);	// acquire lock

		race += 3;

		cout << "Increment thread : race = " << race << endl;

		if(race == 100){
			flag = true;
			pthread_cond_signal(&done);	// signal the waiter thread
			pthread_mutex_unlock(&lock);	// release lock
			pthread_exit(&ret);		// exit
		}
		else if(race >= 100){
			pthread_mutex_unlock(&lock);	// release lock
			pthread_exit(&ret);
		}


		pthread_mutex_unlock(&lock);		// release lock

	}

	pthread_exit(&ret);

	
}

void * dec(void * v){

	int ret = 0;

	while(flag != true){

		sleep(1);

		pthread_mutex_lock(&lock);	// acquire lock

		if(flag != true)
			race -= 1;

		cout << "Decrement thread : race = " << race << endl;

		if(race == 100){
			flag = true;
			pthread_cond_signal(&done);
			pthread_mutex_unlock(&lock);	// release lock
			pthread_exit(&ret);

		}


		pthread_mutex_unlock(&lock);		// release lock

	}

	pthread_exit(&ret);

	
}

void * waiter(void * v){

	int ret = 0;

	pthread_mutex_lock(&lock);		// acquire lock

	while(race < 100){				// kept for spurious wakeup calls
		pthread_cond_wait(&done, &lock);	// wait on condition varible(release lock) for race to become 100 
	}

	cout << "Waiting thread : Race is finally = " << race << endl;

	pthread_mutex_unlock(&lock);		// release lock

	pthread_exit(&ret);
}


int main(){

	pthread_mutex_init(&lock, NULL);
	pthread_cond_init(&done, NULL);

	// create threads

	pthread_create(&thread[2], NULL, waiter, NULL);
	pthread_create(&thread[0], NULL, inc, NULL);
	pthread_create(&thread[1], NULL, dec, NULL);

	
	// join threads

	pthread_join(thread[0], NULL);
	pthread_join(thread[1], NULL);
	pthread_join(thread[2], NULL);

	pthread_cond_destroy(&done);
	pthread_mutex_destroy(&lock);

}
