void main(){

int i=7;

int pid = fork();
i--;
if(pid==0){

i++;

}

printf("%d\n", i);

}
