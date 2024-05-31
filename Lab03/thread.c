#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

void *thread_function(void *arg)
{
	int a;
	for(a=0;a<10; a++)
	{
	printf("Thread says hi!\n");
	sleep(2);
	}
	return NULL;
}

int main(void)
{
	pthread_t mythread;
	if ( pthread_create( &mythread, NULL, thread_function, NULL) )
	{
		printf("error creating thread.");
		abort();
	}
	if ( pthread_join ( mythread, NULL ) )
	{
	printf("error joining thread.");
	abort();
	}
	printf("Main thread says hi!\n");
	exit(0);
}
