#include <unistd.h>
#include <pthread.h>
#include <stdio.h>

// This will act as the resources
pthread_mutex_t firstMutex, secondMutex;

void *fun1()
{
    printf("T1 trying to acquire first mutex\n");
    pthread_mutex_lock(&firstMutex);
    printf("T1 acquired first mutex\n");

    sleep(2);

    printf("T1 trying to acquire second mutex\n");
    pthread_mutex_lock(&secondMutex);
    printf("T1 acquired second mutex\n");
    pthread_mutex_unlock(&secondMutex);
    
    printf("T1 released second mutex\n");
    pthread_mutex_unlock(&firstMutex);
    printf("T1 released first mutex\n");

    pthread_exit(NULL);
}

void *fun2()
{
    printf("T2 trying to acquire second mutex\n");
    pthread_mutex_lock(&secondMutex);
    printf("T2 acquired second mutex\n");

    sleep(2);

    printf("T2 trying to acquire first mutex\n");
    pthread_mutex_lock(&firstMutex);
    printf("T2 acquired first mutex\n");
    pthread_mutex_unlock(&firstMutex);

    printf("T2 released first mutex\n");
    pthread_mutex_unlock(&secondMutex);
    printf("T2 released second mutex\n");

    pthread_exit(NULL);
}

int main()
{
    // Initialize mutexes
    pthread_mutex_init(&firstMutex, NULL);
    pthread_mutex_init(&secondMutex, NULL);

    // Thread available
    pthread_t T1, T2;

    // Thread creation
    pthread_create(&T1, NULL, fun1 ,NULL);
    pthread_create(&T2, NULL, fun2 ,NULL);

    // Join the thread and wait to finish
    pthread_join(T1, NULL);
    pthread_join(T2, NULL);

    printf("Thread joined\n");

    return 0;
}