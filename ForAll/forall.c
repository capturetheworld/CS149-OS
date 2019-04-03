#include <stdio.h>
#include <stdlib.h>
#include <zconf.h>
#include <fcntl.h>
#include <signal.h>
#include <errno.h>

int saved_stdout;
char fileCounter[10];
int fd1out;

 void userHandler(int sig)
{

    if(sig == 2){
        exit(0);
    }
}

int main(int argc, char * argv[]) {



    struct sigaction sa;
    sa.sa_handler = &userHandler;
    sa.sa_flags = SA_SIGINFO;
    sigemptyset(&sa.sa_mask);

    if (sigaction(SIGINT,&sa,NULL) == -1){
        printf("Error: cannot handle SIGINT\n");
    }
    if (sigaction(SIGQUIT,&sa,NULL) == -1){
        printf("Error: cannot handle SIGQUIT\n");
    }


    if(argc<=1){
        printf("error invalid input");
        exit(-1);
    }



    else{
        int argumentIndex = 2;
       while (argv[argumentIndex] != NULL){


           int fileCount = argumentIndex-1;
           sprintf(fileCounter, "%d.out", fileCount);




           int pid = fork();


           if (pid < 0) {
               printf("error forking");
           }


           else if (pid == 0) {
               sa.sa_handler = &userHandler;

                fd1out = open(fileCounter, O_WRONLY | O_CREAT | O_APPEND);



               fflush(stdout);

               close(1);

               close(2);

               dup(fd1out);

               if (fd1out < 1) {
                   printf("file wasn't created");
               }
               printf("Executing %s %s \n", argv[1], argv[argumentIndex]);
               fflush(stdout);



              //sigaction(SIGUSR1, &sa, NULL);
              // perror("printing error here");



               //child
               execlp(argv[1], argv[1], argv[argumentIndex], NULL);


               exit(0);




           } else {//parent


               if(sigaction(SIGINT, &sa, NULL) == -1){
                   perror("sigaction SIGINT");
                   exit(errno);
               }

               if(sigaction(SIGQUIT, &sa, NULL) == -1){
                   perror("sigaction SIGQUIT");
                   exit(errno);
               }







                   FILE *writeTo = fopen(fileCounter, "a");
                   int stat;
                waitpid(pid, &stat, 0);
                kill(pid, SIGINT);


               printf("STAT IS: %d WEXITSTATUS: %d \n", stat, WEXITSTATUS(stat));




               if(WEXITSTATUS(stat)==0) {

                      fprintf(writeTo, "Finished executing %s %s exit code = %d", argv[1], argv[argumentIndex], stat);
                      fflush(stdout);
                  }

                  else {


                      fprintf(writeTo, "Stopped executing %s %s signal = %d", argv[1], argv[argumentIndex],
                              WTERMSIG(stat));
                      fflush(stdout);
                  }









          // exit(0);



           }

           argumentIndex++;


       }





























    }
}