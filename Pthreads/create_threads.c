#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// Compile and link with -pthread.

// API to create a pthread
// -----------------------
// API : int pthread_create(pthread_t * thread, const pthread_attr_t * attr,void * (*start_routine)(void *), void *arg);
//
// Arguments to the API:
//
// a. Argument 1 : A pointer to a pthread_t structure, which pthread_create will fill out with information on the thread it creates.
// b. Argument 2 : A pointer to a pthread_attr_t with parameters for the thread. You can safely just pass NULL most of the time.
// c. Argument 3 : A function to run in the thread. The function must return void * and take a void * argument, which you may use however you see fit. (For instance, if you're starting multiple threads with the same function, you can use this parameter to distinguish them.)
// d. Argument 4 : The void * that you want to start up the thread with. Pass NULL if you don't need it.
// Return Argument : 0 if thread was created sucessfully


// API : int pthread_join(thread_t tid, void **status);
//-----------------------------------------------------
// a. Argument 1 : Thread ID
// b. Argument 2: Status to collect exit code

// pthread_create() expects a pointer to a function that takes a void* as input 
// and returns a void* as output

// API :  int pthread_attr_init(pthread_attr_t *attr);   
// ---------------------------------------------------
// The pthread_attr_init() function initializes a thread attributes object to the default thread attributes. The thread attributes object can be used in a call to pthread_create() to specify attributes of the new thread.
// Arguments : attr (Input/Output) The address of the thread attributes object to be initialized
// Return Value :  0 pthread_attr_init() was successful. pthread_attr_init() was not successful. 

void* start_routine(void *arg);
void  error_handler(char* msg);

int main(){

  pthread_t tid_1,tid_2;
  pthread_attr_t tattr;
  int arg = 55,i =0,ret;

  // API : int pthread_create(pthread_t * thread, const pthread_attr_t * attr,void * (*start_routine)(void *), void *arg);
  // Launch thread by passing default thread attribuutes -- NULL
  ret = pthread_create(&tid_1, NULL, start_routine, (void*)arg);
  if(ret){
    error_handler("Unable to create a thread");
  }

  /* initialized with default attributes */
  ret = pthread_attr_init(&tattr);
  if(ret){
    error_handler("Unable to initalize thread attributes");
  }

  /* default thread attributes behavior specified*/
  ret = pthread_create(&tid_2, &tattr, start_routine, arg);
  if(ret){
    error_handler("Unable to create a thread with attributes");
  }

  pthread_join( tid_1, NULL);
  pthread_join( tid_2, NULL);

}

void* start_routine(void *arg){
  printf("Thread launched %d with thread id -- %u\n",(int*) arg, pthread_self());
}

void error_handler(char* msg){
  perror(msg);
}
