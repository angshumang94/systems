/* Angshuman Ghosh 2017CS01			Date: 14/10/2017


Creates a new thread with Round Robin scheduler and least priority 
and change the priority to maximum from the thread itself

*/




#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sched.h>


void * myfunc(void * v){





	int policy, ret;

	struct sched_param param;

	pthread_getschedparam(pthread_self(), &policy, &param);	// get the current scheduler settings for thread

	printf("  Existing settings :  policy= %s, priority= %d\n", (policy == SCHED_FIFO)  ? "SCHED_FIFO" : (policy == SCHED_RR) ? "SCHED_RR" : (policy == SCHED_OTHER) ? "SCHED_OTHER" : "UNKNOWN", param.sched_priority);
	


	printf("  Max priority of %s is %d\n", policy == SCHED_OTHER ? "SCHED_OTHER" : policy == SCHED_FIFO ? "SCHED_FIFO" : "SCHED_RR", sched_get_priority_max(policy));

	param.sched_priority = sched_get_priority_max(policy);	// Get the maximum possible priority value for the corresponding policy

	pthread_setschedparam(pthread_self(), policy, &param);	// Set the new priority value for the policy

	printf("After changing ... policy = %s    priority = %d \n", (policy == SCHED_FIFO)  ? "SCHED_FIFO" : (policy == SCHED_RR) ? "SCHED_RR" : (policy == SCHED_OTHER) ? "SCHED_OTHER" : "UNKNOWN", param.sched_priority);


	return 0;

}


int main(){
	int r,policy;

	pthread_t thread;	// thread
	pthread_attr_t attr;	// thread attribute
	struct sched_param param;	// struct to store priority value


	pthread_attr_init(&attr);	// initialize the attributes


	pthread_attr_setinheritsched(&attr, PTHREAD_EXPLICIT_SCHED);	// set scheduling to explicit so that it does not invoke SCHED_OTHER as default


	param.sched_priority = sched_get_priority_min(SCHED_RR);	// set scheduling priority of thread as minimum for RR

	pthread_attr_setschedpolicy(&attr, SCHED_RR);	// set the Round Robin scheduler

	pthread_attr_setschedparam(&attr, &param);	// set the parameters -> priority


	

	pthread_create(&thread, &attr, &myfunc, NULL);	// create thead


	pthread_join(thread,NULL);


}

