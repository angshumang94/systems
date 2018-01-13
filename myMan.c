#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX 100


int main(int argc, char * argv[]){

	pid_t pid;
	int rv;

	int fd[2]; // file descriptors to be used as pipe I/O


	pipe(fd); // create pipe

	pid = fork(); // fork child

	if(pid == -1){

		perror("fork");
		exit(1);
	}
	else if(pid == 0){	// child


		close(0); 	// close stdin
		dup(fd[0]); 	// duplicate read end of pipe by stdin
		close(fd[1]); 	// close write end of pipe
		
		char arg[MAX];

		read(fd[0],arg,MAX);

		execlp("xterm", "xterm", "-hold", "-e", "man", arg, NULL);

		exit(0);
	}
	else{				// parent
		
		close(1);	// close stdout
		dup(fd[1]);	// duplicate write end of pipe by stdout
		close(fd[0]);	// close read end of pipe

		char * arg = argv[1];

		write(fd[1], arg, strlen(arg));
		

		wait(&rv);

		exit(0);
	}
}
