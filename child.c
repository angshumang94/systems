#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void)
{
    pid_t pid;
    int rv;

    switch(pid = fork()) {
    case -1:
        perror("fork");  
        exit(1);

    case 0:
        printf(" Child process created with PID = %d and parent PID = %d\n",getpid(), getppid());
        printf(" Enter exit status of child = ");
        scanf(" %d", &rv);
        printf(" Child exiting\n");
        exit(rv);

    default:
        printf("Parent process executing with PID = %d with PID of child = %d\n",getpid(), pid);
        
        wait(&rv);
        printf("In parent: exit status of child is: %d\n", WEXITSTATUS(rv));
        printf("Parent exiting\n");
    }

    return 0;
}