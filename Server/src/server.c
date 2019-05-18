/* Server creates a local messaging system */
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

    int sock;
     int newsock;
     int port;





     socklen_t clilen;
     char buffer[256];
     struct sockaddr_in serv_addr, cli_addr;
     int rtnval;
     int pid;
     if (argc < 2) {
         fprintf(stderr,"Error, please enter a port\n");
         exit(-2);
     }

     // geeks for geeks AF_INET
     sock = socket(AF_INET, SOCK_STREAM, 0);

     if (sock < 0) 
        error("Cannot open socket");

     bzero((char *) &serv_addr, sizeof(serv_addr));

     port = atoi(argv[1]);

     
// geeksforgeeks 
     serv_addr.sin_family = AF_INET;
    

     serv_addr.sin_addr.s_addr = INADDR_ANY;
     
     serv_addr.sin_port = htons(port);

// geeksforgeeks
     if (bind(sock, (struct sockaddr *) &serv_addr,
              sizeof(serv_addr)) < 0) 
              error("Cannot bind socket to server");

     listen(sock,5);
     clilen = sizeof(cli_addr);

    while(1){ //concurrency
        
     

      // geeksforgeeks

     newsock = accept(sock, (struct sockaddr *) &cli_addr,  &clilen);

     if (newsock < 0) 
          error("Can't accept the incoming data");

      pid = fork();

      if(pid <0){
        error("Error for forking");
      }

else if(pid==0){

   while(1){ //every process gets string



     bzero(buffer,256);

     rtnval = read(newsock,buffer,255);

     if (rtnval< 0) 
         error("Can't read from socket");

     printf("broadcasting: %s",buffer);

     rtnval = write(newsock,buffer,18);

     if (rtnval < 0) error("Can't write to socket");
   }
}

else{
     close(newsock);
 }
 }
     close(sock);
     return 0; 
}
