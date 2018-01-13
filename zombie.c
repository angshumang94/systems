#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>



int main(){


    pid_t pid;

    int rv;

    printf("PARENT : my id %d\n",getpid());

    pid = fork();

    switch(pid){

        case 0:
            printf("CHILD : my id is %d and parent id is %d\n", getpid(), getppid());
            printf("CHILD : exiting\n");
            exit(0);
            break;
        case -1:
            perror("fork");
            exit(1);
            break;
        default:
            printf("PARENT : spawned child id %d\n", pid);
            printf("PARENT : going to sleep for 5 secs\n");
            sleep(5); // sleep for 5 seconds
            
            printf("=============\n");
            printf("PARENT : showing zombie processes before wait\n");
            system("ps aux | grep 'Z'"); // show zombie child

            wait(&rv);

            printf("=============\n");
            printf("PARENT : showing zombie processes after wait\n");
            system("ps aux | grep 'Z'"); // zombie child removed

            printf("PARENT : child returned %d\n",WEXITSTATUS(rv));
            printf("PARENT : exiting\n");
            exit(0);
            break;
    }
}