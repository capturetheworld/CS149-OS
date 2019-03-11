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
    const char * sig_name;
    switch(sig){


        case  SIGINT:
            close(1);
            dup(saved_stdout);
            printf("Signalling %d\n",getpid());
            int pid2 = getpid();
            fflush(stdout);
            close(1);
            fd1out =open(fileCounter,O_WRONLY | O_CREAT | O_APPEND);
            return;

        case  SIGQUIT:
            close(1);
            dup(saved_stdout);
            printf("Signalling %d\n",getpid());
            fflush(stdout);
            close(1);
            kill(getpid(),SIGQUIT);
            fd1out =open(fileCounter,O_WRONLY | O_CREAT | O_APPEND);
            return;
        default:
            printf("No signal\n");

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
           } else if (pid == 0) {

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


              // sa.sa_handler = SIG_IGN;
              // sigaction(SIGUSR1, &sa, NULL);
              // perror("printing error here");



               //child
               execlp(argv[1], argv[1], argv[argumentIndex], NULL);


               exit(0);




           } else {//parent







                   FILE *writeTo = fopen(fileCounter, "a");
                   int stat;
               pid_t childPID = waitpid(pid, &stat, 0);


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




       \

               if(sigaction(SIGINT, &sa, NULL) == -1){
                   perror("sigaction SIGINT");
                   exit(errno);
               }

               if(sigaction(SIGQUIT, &sa, NULL) == -1){
                   perror("sigaction SIGQUIT");
                   exit(errno);
               }



          // exit(0);



           }

           argumentIndex++;


       }





























    }
}