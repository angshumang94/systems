#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>


#define FIFO_R "fif0"
#define FIFO_W "fif1"

#define MAX 300

int main(void)
{
    char s[300];
    int num, fd0 , fd1;

    mknod(FIFO_R, S_IFIFO | 0666, 0);
    mknod(FIFO_W, S_IFIFO | 0666, 0);

    printf("waiting for readers...\n");
    
    fd1 = open(FIFO_W, O_WRONLY);	//	open fif1 for writing
    fd0 = open(FIFO_R, O_RDONLY);	//	open fif0 for reading
    
    printf("got a reader--type some stuff\n");

    while (fgets(s,MAX,stdin)) {
    
    
        if ((num = write(fd1, s, strlen(s)-1)) == -1)
            perror("write");
        else
            printf("speak: wrote %d bytes\n", num);
            
        
        
        if ((num = read(fd0, s, 300)) == -1)
            perror("read");
        else {
            s[num] = '\0';
            
            printf("speak: got reversed string \"%s\"\n", s);
        }
    }

    return 0;
}
