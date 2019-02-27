#include <stdio.h>
#include <unistd.h>



main(){
	execlp("slep","sleep","1000"); //need a null at the end of exec lp
	printf("ran sleep");
}