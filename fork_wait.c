#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

 void signal_handler(int status){


        printf("\nParent exiting with ");

        if(WIFEXITED(status))   // check if exited normally
                printf("Child return code %d\n",WEXITSTATUS(status));   // print exit status
        else if(WIFSIGNALED(status))    // check if there was signalled interrupt
                printf("Child terminated abnormally by signal number %d\n",WTERMSIG(status));
        else
                printf("not known\n");

        exit(1);
} 


int main(int argc, char *argv[]){


        pid_t pid;
        int rv; // exit return value o child
        
        printf("Parent pid %d\n",getpid());
        
        
        printf("Parent executing\n");
        
        pid = fork();   // fork process

        if(pid == -1){
                perror("fork");
                exit(1);
        }
        
        if(pid == 0){
                printf("Child executing with pid %d and parent %d\n",getpid(),getppid());
                printf("Child : Enter exit code of child\n");
                scanf("%d",&rv);
                exit(rv);
        
        }

        signal(SIGINT,signal_handler);  // define the signal handler function in case of signalled interrupts
        
        wait(&rv);

        printf("\nParent exiting with ");

        if(WIFEXITED(rv))   // check if exited normally
                printf("Child return code %d\n",WEXITSTATUS(rv));   // print exit status
        

        exit(0);


}
