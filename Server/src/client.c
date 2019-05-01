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
    int portnum, sockfd, rtnval;


    struct sockaddr_in serv_addr;
    struct hostent *server;




    char buffer[256];
    if (argc != 2) {
       fprintf(stderr,"USAGE: %s host:port\n", argv[0]);
       exit(1);
    }

    char * port = strtok(argv[1],":");

    port = strtok(NULL,":");

    if(port == NULL){
        fprintf(stderr,"USAGE: %s host:port\n", argv[0]);
        exit(2);

    }


    portnum = atoi(port); //change string to int

    sockfd = socket(AF_INET, SOCK_STREAM, 0);


    if (sockfd < 0) 
        error("ERROR opening socket");

    server = gethostbyname(argv[1]);

    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, 
         (char *)&serv_addr.sin_addr.s_addr,
         server->h_length);
    serv_addr.sin_port = htons(portnum);
    if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) 
        error("ERROR connecting");
    printf("Please enter the message: ");
    bzero(buffer,256);
    fgets(buffer,255,stdin);


    rtnval = write(sockfd,buffer,strlen(buffer));
    if (rtnval < 0) {
         error("Cannot write to socket");
     }


    bzero(buffer,256);


    rtnval = read(sockfd,buffer,255);

    if (rtnval < 0) {
         error("Cannot read from socket");
     }



    printf("%s\n",buffer);
    close(sockfd);
    return 0;
}