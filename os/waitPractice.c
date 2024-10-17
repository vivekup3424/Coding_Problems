#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
	printf("hello: (pid: %d)", getpid());
	int rc = fork();
	if(rc <0){
		fprintf(stderr, "failed to create new process");
	}else{
		int rc_wait = wait(NULL);
		printf("parent of %d (rc_wait:%d) (pid:%d)\n",
		rc, rc_wait,(int)getpid);
	}
	return EXIT_SUCCESS;
}
