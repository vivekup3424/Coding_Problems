#include <stdio.h>
#include <assert.h>
#include <pthread.h>

void *mythread(void *arg){
	printf("%s\n",(char *)arg);
	return NULL;
}

int main(int argc, char *argv[])
{
	pthread p1,p2;

	return EXIT_SUCCESS;
}
