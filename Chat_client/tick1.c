#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#define FIFO_W "fif0"
#define FIFO_R "fif1"


void reverse(char * s, int length){
        
        char temp;
        int i;
        
        for( i=0 ; i< length/2 ; i++){
             temp = s[i];
             s[i] = s[length - i -1];
             s[length - i -1] = temp;   
        
        }

}

int main(void)
{
    char s[300];
    int num, fd0, fd1;

    mknod(FIFO_R, S_IFIFO | 0666, 0);
    mknod(FIFO_W, S_IFIFO | 0666, 0);

    printf("waiting for writers...\n");
    
    fd0 = open(FIFO_R, O_RDONLY);	//	open fif1 for reading
    fd1 = open(FIFO_W, O_WRONLY);	//	open fif0 for writing
    
    printf("got a writer\n");

    do {
        if ((num = read(fd0, s, 300)) == -1)
            perror("read");
        else {
                
            s[num] = '\0';
            printf("tick: read %d bytes: \"%s\"\n", num, s);
            reverse(s, num);
            
        }
        
        
        if ((num = write(fd1, s, strlen(s))) == -1)
            perror("write");
        else
            printf("tick: wrote reversed string \"%s\" of %d bytes\n",s, num);
            
            
    } while (num > 0);

    return 0;
}
