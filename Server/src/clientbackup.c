#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include <fcntl.h>
#include <poll.h>



void error(const char *errmsg)
{
    printf("%s", errmsg);
    exit(-1);
}

int main(int argc, char *argv[])
{
    int portnum;
    int sockfd;
    int rtnval;


    struct sockaddr_in servaddress;

    struct hostent *server;




    char buffer[256];
    if (argc != 2) {
       fprintf(stderr,"USAGE: %s host:port\n", argv[0]);
       exit(1);
    }

    char * port = strtok(argv[1],":");

    port = strtok(NULL,":"); // String parts[] = args[0].split(":")

    if(port == NULL){
        fprintf(stderr,"USAGE: %s host:port\n", argv[0]);
        exit(2);

    }


    portnum = atoi(port); //change string to int

    sockfd = socket(AF_INET, SOCK_STREAM, 0); //setup internet TCP


    if (sockfd < 0) 
        error("ERROR opening socket");

    server = gethostbyname(argv[1]);

    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }
    bzero((char *) &servaddress, sizeof(servaddress)); //initialize with zero

// geeks for geeks
    servaddress.sin_family = AF_INET; //sets internet address


    bcopy((char *)server->h_addr,  (char *)&servaddress.sin_addr.s_addr,  server->h_length);
    //copies the bypes from server address to structure server address
   

    servaddress.sin_port = htons(portnum); //change port number to internet type //https://linux.die.net/man/3/htons


    if (connect(sockfd,(struct sockaddr *) &servaddress,sizeof(servaddress)) < 0) 
        error("can't connect to server");


    bzero(buffer,256);
    while(fgets(buffer,255,stdin) !=0){


    rtnval = write(sockfd,buffer,strlen(buffer));
    if (rtnval < 0) {
         error("Cannot write to socket");
     }


    bzero(buffer,256);


    rtnval = read(sockfd,buffer,255);

    if (rtnval < 0) {
         error("Cannot read from socket");
     }



    printf("received: %s\n",buffer);

}
    close(sockfd);
    return 0;
}