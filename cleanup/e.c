#include <stdio.h>
#include <unistd.h>



int main(){
	execlp("sleep","sle","1000", NULL); //need a null at the end of exec lp
	//argv0 shows up in main
	printf("ran sleep\n");


	//write(filedescpt, information , # of bytes )
	//write(1, "hi\n", 3);
	//syscall (4,1, "hi", 3);
}

//creating file descriptors