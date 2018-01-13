#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

#define MAX 101


void read_pipe(int * fd, char * buff, int buff_size){

	int char_count;

	while((char_count = read(fd[0], buff, buff_size)) != 0){	// read data when available

		if(strcmp(buff,"q\n") == 0){
			printf("Child Exiting\n");
			break;
		}

		printf("Child read : %s",buff);	// print read data
	}
}


void write_pipe(int * fd, char * buff, int buff_size){
	
	while(fgets(buff, buff_size, stdin)){	// read user input from stdin
		

		write(fd[1], buff, buff_size);	// write user input to pipe

		if(strcmp(buff,"q\n") == 0){
			printf("Parent Exiting\n");
			break;
		}


		printf("Parent : enter new line(100 chars max) : q to quit\n");
	}

}






int main(){


	pid_t pid;
	char buffer[MAX];

	int fd[2]; // file descriptors to be used as pipe I/O


	printf("Parent : started execution\n");

	pipe(fd); // create pipe

	pid = fork(); // fork child

	if(pid == -1){

		perror("fork");
		exit(1);
	}
	else if(pid == 0){	// child

		printf("Child : started execution\n");

		close(fd[1]);

		read_pipe(fd, buffer, sizeof(buffer));	// read from pipe as data is available

		exit(0);
	}
	else{				// parent

		close(fd[0]);

		printf("Parent : Input string (100 chars max)\n");

		write_pipe(fd, buffer, sizeof(buffer));	// write to pipe as data is entered

		exit(0);
	}



}
