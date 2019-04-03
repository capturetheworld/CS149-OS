#include <stdio.h>
#include <stdlib.h>

//malloc uses break

int main(){
	void *ptr = malloc(16);
	free(ptr);
	for (int i=0; i<1000; i++){
		ptr = malloc(1024*1024);
		free(ptr);

	}
	ptr = malloc(1024*1024);
		free(ptr);

	for (int i=0; i<1000; i++){
		ptr = malloc(1024*1024);
		free(ptr);

	return 0;

}