/* Angshuman Ghosh 2017CS01	Date- 09/10/2017

Calculates product of a matrix by creating threads to perform dot product of row and column

Pass arguments m, n, l

*/



#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

struct compute{
	int ** A;
	int ** B;
	int ** M;
	int row;
	int column;
	int n;
};


void * dot_product(void * v){	

	struct compute * c = (struct compute *)v;	// cast void pointer to struct pointer

	int i;
	int row,column, n;
	int ** A; 
	int ** B;
	int ** M;


	//	Read all values from structure	//

	A = c->A;
	B = c->B;
	M = c->M;

	row = c->row;
	column = c->column;
	n = c->n;

	printf("Thread ID = %lu computing ,row = %d column = %d\n",pthread_self(),row,column);

	M[row][column] = 0;

	//	Compute dot product	//

	for(i =0 ; i<n ; i++){
		M[row][column] += A[row][i] * B[i][column];
	}

	return NULL;
}


int main(int argc, char ** argv){

	int i,j;

	int m,n,l;

	// Take matrix dimensions A(m x n) and B(n x l)//

	m = atoi(argv[1]);
	n = atoi(argv[2]);
	l = atoi(argv[3]);

	// Allocate memory for matrix A, B and the product matrix M //

	int ** A = (int **)malloc(sizeof(int *) * m);

	int ** B = (int **)malloc(sizeof(int *) * n);

	int ** M = (int **)malloc(sizeof(int *) * m);

	for(i =0 ; i<m ; i++){

		A[i] = (int *)malloc(sizeof(int) * n);
	}

	for(i =0 ; i<n ; i++){

		B[i] = (int *)malloc(sizeof(int) * l);
	}

	for(i =0 ; i<m ; i++){

		M[i] = (int *)malloc(sizeof(int) * l);
	}


	//	Fill matrices with user input	//

	printf("Enter values of matrix A\n");

	for(i=0 ; i < m ;i++){
		for(j=0 ; j< n ;j++){

			scanf("%d",&A[i][j]);
		}
	}


	printf("Enter values of matrix B\n");

	for(i=0 ; i < n ;i++){
		for(j=0 ; j< l ;j++){

			scanf("%d",&B[i][j]);
		}
	}


	// Allocate memory for threads (m x l)	// 

	pthread_t ** thread = (pthread_t **)malloc(sizeof(pthread_t *) * m);

	for(i =0 ; i<m ; i++){

		thread[i] = (pthread_t *)malloc(sizeof(pthread_t) * l);
	}


	// Start dispatching threads //


	printf("Main : Starting multipling matrix\n");

	for(i =0 ; i<m ; i++){

		for(j =0 ; j<l ; j++){

			// Prepare structure to be passed to threads//

			struct compute * c = malloc(sizeof(struct compute));
			c->A = A;
			c->B = B;
			c->M = M;

			c->row = i;
			c->column = j;
			c->n = n;

			pthread_create(&thread[i][j], NULL, dot_product, (void *)c);	// create thread
			
		}
	}



	//	Wait for all the threads to finish executing	//

	for(i =0 ; i<m ; i++){

		for(j =0 ; j<l ; j++){

			pthread_join(thread[i][j], NULL);	// join thread , get result array
		}
	}



	//	Print the product matrix	//

	printf("Printing Matrix product\n");

	for(i =0 ; i<m ; i++){

		for(j =0 ; j<l ; j++){

			printf("%d ",M[i][j]);
		}
		printf("\n");
	}



	//	Free the allocated memory	//

	for(i =0 ; i<m ; i++){

		free(A[i]);
		free(M[i]);
		free(thread[i]);
	}

	for(i =0 ; i<n ; i++){

		free(B[i]);
	}

	free(A);
	free(B);
	free(M);
	free(thread);



	printf("Main exiting\n");	// Exit messege


}
