#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

void signal_handler(int status){

        printf("\nParent exiting with ");

        if(WIFEXITED(status))
                printf("Child return code %d\n",WEXITSTATUS(status));
        else if(WIFSIGNALED(status))
                printf("Child terminated abnormally by signal number %d\n",WTERMSIG(status));
        else
                printf("not known\n");

        exit(1);
}


int main(int argc, char *argv[]){


        pid_t pid;
        int rv; // exit return value o child


	char * arg[] = {"ls", "-l", NULL};

        signal(SIGINT,signal_handler);  // define the signal handler function in case of signalled interrupts
        
        printf("Parent pid %d\n",getpid());
        
        
        printf("Parent executing\n");
        
        pid = fork();   // fork process
        
        if(pid == 0){
                printf("Child executing\n");
                execvp(arg[0], arg);    // execute ls command with -ls flag
        
        }
        
        wait(&rv);

        printf("\nParent exiting with ");

        if(WIFEXITED(rv))   // check if exited normally
                printf("Child return code %d\n",WEXITSTATUS(rv));   // print exit status

        exit(0);


}
