#include <iostream>
#include <cstdlib>
#include <vector>
#include <pthread.h>
#include <unistd.h>

using namespace std;

///----- Initialize balance and declare lock------///

long balance = 0;
pthread_mutex_t acc;


///------Define struct for transaction -----///

struct transact{

	char op;
	long amount;
};



///------Thread handler function---------///

void * account_op(void * v){


	sleep(rand()%7);			// Wait a random time to simulate delay

	transact * t = (transact *)v;


	pthread_mutex_lock(&acc);	// aquire lock for deposit or withdraw

	if(t->op == 'd')
		balance += t->amount;
	else
		balance -= t->amount;

	cout << "Current balance is " << balance << endl;

	pthread_mutex_unlock(&acc);	// release lock

	delete t;

	return 0;

}


///---------Main-----------///

int main(){


	pthread_t thread;	
	vector<pthread_t> thread_vec;	// list of thread spawned
	transact * t;

	long amount;
	char op = 's';


	pthread_mutex_init(&acc, NULL);	// initialize mutex


	cout << "Enter 'd' to deposit or 'w' to withdraw <space> amount involved and 'q' to quit" << endl;

	while(op != 'q'){

		cout << ">>  ";

		cin >> op;

		switch(op){

			case 'd': case'w':		// deposit or withdraw

				cin >> amount;

				t = new transact;
				t->op = op;
				t->amount = amount;

				pthread_create(&thread, NULL, account_op, (void *)t);	// create thread
				thread_vec.push_back(thread);	// maintain list
				break;
			default:
				break;

		}
	}

	for(vector<pthread_t>::iterator iter = thread_vec.begin(); iter != thread_vec.end(); iter++){		// wait for all thread to finish

		pthread_join(*iter,NULL);
	}

	pthread_mutex_destroy(&acc);	// destroy lock

	return 0;

}
