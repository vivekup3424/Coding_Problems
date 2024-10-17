#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]){
	printf("hello (pid:%d)\n",(int)getpid());
	int rc = fork();
	if(rc<0){
		fprintf(stderr, "fork failed\n");
		exit(EXIT_FAILURE);
	}else if(rc==EXIT_SUCCESS){
		//new process 
		printf("child (pid:%d)\n",(int)getpid());
	}else{

		printf("parent of %d: (pid:%d)\n",rc,(int)getpid());
	}
	return EXIT_SUCCESS;
}
