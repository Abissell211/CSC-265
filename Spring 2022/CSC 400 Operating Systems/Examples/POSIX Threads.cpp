// Example program using threads.

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define NUMBER_OF_THREADS 10

void *print_hello_world(void *tid){
	// this function prints the thread's identifier and then exits.
	for(int i=0;i<100;i++){
		printf("Hello World. Greetings from thread %d\n",tid);
	}
	pthread_exit(NULL);
}

int main(int argc, char *argv[]){
	// the main program creates 10 threads and then exits
	pthread_t threads[NUMBER_OF_THREADS];
	int status, i, e;

	for(i=0;i<NUMBER_OF_THREADS;i++){
		printf("Main here. Creating thread %d\n",i);
		status = pthread_create(&threads[i],NULL,print_hello_world,(void *)i);
		
		if(status != 0){
			printf("Oops. pthread_create returned error code %d\n",status);
			exit(-1);
		}
	}
	for(i=0;i<NUMBER_OF_THREADS;i++){
		e = pthread_join(threads[i], NULL);
		if(e != 0){
			printf("Oops. pthread_join returned error code %d\n",status);
			exit(-1);
		}
	}
	printf("//--------------------------------------SUCCESS--------------------------------------\\");
	exit(NULL);
}
