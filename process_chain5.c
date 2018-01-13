
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>


int main(){
        
        pid_t pid,exit_child;
        int pcount =1;
        int rv;
        
        printf("===============\n");
        printf("Starter Process id = %d\n ",getpid());
        printf("Starter process parent id = %d\n" , getppid());
        printf("Process count = %d\n" , pcount);
        
        
        while(pcount < 5){
        
        pid = fork();

        if(pid == -1){
            perror("fork");  
            exit(1);
        }
        
        if(pid == 0){
        
                pcount++;
                
                printf("===============\n");
                printf("Process id = %d\n ",getpid());
                printf("Parent process id = %d\n" , getppid());
                printf("Process count = %d\n" , pcount);  
                
        }
        
        else
                break;
        
        
        
        }
        
        exit_child = wait(&rv);
        
        printf("Parent about to exit = %d The child process that returned = %d, with exit status %d\n",getpid(),exit_child,WEXITSTATUS(rv));
        
        exit(0);
        


}