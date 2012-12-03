#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>


#define MAXLINE 1024


int main(void){
    char buf[MAXLINE];
    pid_t pid;
    int status;

    printf(">>>>> "); /* print prompt (printf requires %% to print %) */
    while (fgets(buf, MAXLINE, stdin) != NULL) {
        buf[strlen(buf) - 1] = 0; /* replace newline with null */

        if ( (pid = fork()) < 0)
            printf("fork error");
        else if (pid == 0) { /* child */
            execlp(buf, buf, (char *) 0);
            printf("couldn't execute: %s", buf);
            return(127);
        }

        /* parent */
        if ( (pid = waitpid(pid, &status, 0)) < 0)
            printf("waitpid error");
        printf(">>>> ");
    }
    return(0);
}

