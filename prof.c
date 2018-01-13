/*	Angshuman Ghosh 2017CS01

Professor answers question asked by student, professor sleeps when no question is there
*/
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>


pthread_mutex_t lock;				// Mutex Variable.
pthread_cond_t sLock, pLock;	// Variable Lock.
pthread_t threads[2];				
bool profAns = false, studQues = true;	
													 
void questionStart() {
											
	if(profAns)						
		pthread_cond_wait(&pLock, &lock);
	
	printf("STUDENT : 'Question' is being Asked.\n");
}



void questionDone() {							// Function to end the question by Student.


	if(profAns)
		pthread_cond_wait(&pLock, &lock);	
	printf("STUDENT : Question Ends.\n");
	pthread_cond_signal(&sLock);		
	
}





void answerStart() {						// Function to start the Answer by Professor.


	if(studQues)							// Checking if there is any question 
		pthread_cond_wait(&sLock, &lock);
	printf("PROFESSOR : Started 'ANSWERING' the Question\n");

}


void answerDone() {							// Function to end the Answer by Professor.
	printf("PROFESSOR : Ends 'ANSWERING' the Question\n");
	pthread_cond_signal(&pLock);		// Unlocking professor, so student can ask next Question.
}



void* studentFunc(void* arg) {					// Student Function.
	while(1) {
		pthread_mutex_lock(&lock);				// Locking.
		questionStart();						// Calling function to start asking question.
		studQues = true;						// Setting the bool variable.
		printf("Question\n");					// Real Question is placed here.
		questionDone();
		studQues = false;
		profAns = true;
		pthread_mutex_unlock(&lock);			// Unlocking.
	}
	pthread_exit(NULL);
}



void* professorFunc(void* arg) {				// Professor Function.
	while(1) {
		pthread_mutex_lock(&lock);				// Locking.
		answerStart();							// Calling function to start answering question.
		profAns = true;							// Setting the bool variable.
		printf("Answer\n");					// Real Answer of the asked Question is placed here.
		answerDone();
		profAns = false;
		studQues = true;
		pthread_mutex_unlock(&lock);			// Unlocking.
	}
	pthread_exit(NULL);
}



int main() {															// Main Function.
	pthread_create(&(threads[0]), NULL, &studentFunc, NULL); 			// Creating threads for Studnets.
	pthread_create(&(threads[1]), NULL, &professorFunc, NULL);  		// Creating threads for Professor.
	pthread_join(threads[0], NULL); 				// Joining Studnet threads.
	pthread_join(threads[1], NULL); 				// Joining Professor threads.
	pthread_mutex_destroy(&lock);  										// Destroying lock.
	pthread_cond_destroy(&sLock);									// Destroying condition lock.
	pthread_cond_destroy(&pLock);								// Destroying condition lock.
	return 0;
}
