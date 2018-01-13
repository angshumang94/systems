#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>


int main(){

	pid_t pid;

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

		close(1);	// close stdout
		dup(fd[1]); // duplicate writing end of pipe as stdout
		close(fd[0]);
		execlp("ls","ls","-l",NULL);

	}
	else{				// parent
		
		close(0);	// close stdin
		dup(fd[0]);	// duplicate reading end of pipe as stdin

		close(fd[1]);	// close writing end of created pipe in parent
		execlp("sort","sort",NULL);
		

	}
}
