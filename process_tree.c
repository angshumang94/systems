#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>



int main(){
        
        pid_t pid;
        int rv;
        int count = 3,    height=0;
        
        
        printf("===============\n");
        printf("Starter Process id = %d at height 0\n",getpid());
        
        while(count > 0){
        
                pid = fork(); // spawn

                if(pid == -1){
                    perror("fork");
                    exit(1);
                }
                
                if(pid == 0){
                        height++;
                        printf("Child process id = %d, Parent process id = %d at height = %d\n",getpid(),getppid(), height);
                }
                
                count--;
        
        }
        
        wait(&rv);
        
        exit(0);    
        
}
