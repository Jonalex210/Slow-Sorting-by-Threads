#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h> 

#define NUM_ELMTS 10

/*Global Variable*/
int sortedArr[NUM_ELMTS];
int pos = 0;

void *runner (void *arg) {
	int *val = arg;
	usleep(*val*100000); //Sleeps the thread for one tenth of the value pointed by val.
	/*DEBUG*/ printf("-> From Thread: %d \n", *val);
	sortedArr[pos] = *val;
	pos++;
	pthread_exit(0);
}

int main () {
	int testArr[NUM_ELMTS] = {6, 4, 1, 2, 5, 1, 2, 1, 1, 0}; //test array to be sorted using sleep function in different threads.
	pthread_t tid[NUM_ELMTS]; // The thread identifiers.
	pthread_attr_t tattr; //A set of thread attributes.
		
	pthread_attr_init(&tattr); //Sets the default attribute of the thread.
	
	for (int idx = 0; idx < NUM_ELMTS; idx++) {
		///*DEBUG*/printf("%d \n", testArr[idx]);
		pthread_create(&tid[idx], &tattr, runner, &testArr[idx]); //Create a new thread.
	}
	
	for (int idx = 0; idx < NUM_ELMTS; idx++) {
		pthread_join(tid[idx], NULL); //Wait for the threat to exit.
	}

	printf("-> From sorted array: ");
	for (int idx = 0; idx < NUM_ELMTS; idx++) {
		printf("%d, ", sortedArr[idx]);	
	}
	printf("\b\b \n");

	return 0;
}
