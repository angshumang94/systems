#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <semaphore.h>
#include <sys/mman.h>

using namespace std;


int * total = (int *) mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, 0 , 0);	// initialize shared memory

sem_t *lock;


void handlerA(){

	int curr;

	for(int i = 0; i < 5 ;  i++){

		sem_wait(lock);

		cout << "Child A count " << i+1 << " : Current value is " << *total << endl;

		curr = *total;

		sleep(rand() % 7);

		*total = curr + 200;

		cout << "Child A count " << i+1 << " : After updating value is " << *total << endl;

		sem_post(lock);

	}
}




void handlerB(){

	int curr;

	for(int i = 0; i < 5 ;  i++){

		sem_wait(lock);

		cout << "Child B count " << i+1 << " : Current value is " << *total << endl;

		curr = *total;

		sleep(rand() % 7);

		*total = curr + 100;

		cout << "Child B count " << i+1 << " : After updating value is " << *total << endl;

		sem_post(lock);

	}
}





int main(){

	int rv;

	*total = 1000;		// store 1000 as starting value

	pid_t ppid = getpid();	// get pid of the parent process

	lock = sem_open("lock", O_CREAT | O_EXCL, 0666 , 1);	// initialize lock


	cout << "Parent : Current value is " << *total << endl;

	for(int i = 0; i < 2 && ppid == getpid() ; i++){	// spawn two children


		switch(fork()){									// create a child

			case 0:
				if(i == 0)
					handlerA();							// handler for process A
				else
					handlerB();							// handler for process B
				break;
			default:
				break;
		}

	}


	for(int i = 0; i < 2 && ppid == getpid() ; i++){
		wait(&rv);
	}

	sem_unlink("lock");

}