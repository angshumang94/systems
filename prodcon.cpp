/*	Angshuman Ghosh		2017CS01

Classic problem of producer and consumer with bounded buffer

*/



#include <iostream>
#include <cstdlib>
#include <list>
#include <pthread.h>
#include <unistd.h>

using namespace std;



class ProdConsLL{

	pthread_t * prod_thread;	// producer threads
	pthread_t * con_thread;		// consumer threads

	pthread_mutex_t lock;
	pthread_cond_t qempty;		//queue empty condition
	pthread_cond_t qfull;		//queue full condition


	int producers;
	int consumers;
	bool flag = false;
	int full = 10;



	list<int> dataQ;


	long factorial(int);

	static void * prod_wrapper(void *);
	static void * con_wrapper(void *);


	void prod_routine();
	void con_routine();



public:

	ProdConsLL(int, int);
	
	void setflag();
	void cleanup();


};

ProdConsLL::ProdConsLL(int p, int c){		// constructor to spawn threads

	producers = p;
	consumers = c;

	prod_thread = new pthread_t[p];
	con_thread = new pthread_t[c];

	pthread_mutex_init(&lock, NULL);
	pthread_cond_init(&qempty, NULL);
	pthread_cond_init(&qfull, NULL);


	for(int i = 0 ; i < p ; i++){

		pthread_create(&prod_thread[i], NULL, prod_wrapper, this);
	}

	for(int i = 0 ; i < c ; i++){

		pthread_create(&con_thread[i], NULL, con_wrapper, this);
	}

	

}


long ProdConsLL::factorial(int i){

	return (i == 0) || (i == 1) ? 1 : i * factorial(i-1);
}



void ProdConsLL::prod_routine(){		// producer routine

	while(!flag){

		sleep(rand()%3);

		int data = rand()%11;


		pthread_mutex_lock(&lock);


		while(dataQ.size() == full && !flag){		// wait till queue is not full

			cout << "Queue full " << endl;
			pthread_cond_wait(&qfull, &lock);
		}

		if(!flag){

			dataQ.push_back(data);

			cout << "Number put " << data << " queue size " << dataQ.size() << endl;

			pthread_cond_signal(&qempty);
		}	

		pthread_mutex_unlock(&lock);

	}

}

void ProdConsLL::con_routine(){

	while(!flag){

		usleep(rand()%1000);


		pthread_mutex_lock(&lock);

		

		while(dataQ.size() == 0 && !flag)			// wait till queue has some items
			pthread_cond_wait(&qempty, &lock);



		if(!flag){

			int data = dataQ.front();
			dataQ.pop_front();

			cout << "Number picked " << " factorial " << factorial(data) << " queue size "  << dataQ.size() << endl;

			pthread_cond_signal(&qfull);
		}

		pthread_mutex_unlock(&lock);

	}

	
}


//	Thread wrapper routines

void * ProdConsLL::prod_wrapper(void * v){

	ProdConsLL * pc = (ProdConsLL *) v;

	pc->prod_routine();
}


void * ProdConsLL::con_wrapper(void * v){

	ProdConsLL * pc = (ProdConsLL *) v;

	pc->con_routine();
}






void ProdConsLL::setflag(){

	flag = true;
}


void ProdConsLL::cleanup(){		// signal all prods and consumers

	for(int i =0 ; i<consumers ; i++)
		pthread_cond_signal(&qempty);

	for(int i =0 ; i<producers ; i++)
		pthread_cond_signal(&qfull);

	

	for(int i = 0 ; i < producers ; i++)
		pthread_join(prod_thread[i], NULL);

	for(int i = 0 ; i < consumers ; i++)
		pthread_join(con_thread[i], NULL);

	delete prod_thread;
	delete con_thread;
}








int main(int argc, char ** argv){

	int p,c;

	p = atoi(argv[1]);
	c = atoi(argv[2]);


	ProdConsLL pc(p,c);	// initialize object

	sleep(10);

	pc.setflag();

	pc.cleanup();


	cout << "Exiting main" << endl;

	
}
