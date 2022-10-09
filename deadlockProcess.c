#include <unistd.h>
#include <pthread.h>
#include <stdio.h>

// This will act as the resources
pthread_mutex_t firstResource, secondResource;

void *fun1()
{
    printf("T1 trying to acquire first resource...\n");
    pthread_mutex_lock(&firstResource);
    printf("T1 acquired first resource!!\n");

    sleep(2);

    printf("T1 trying to acquire second resource...\n");
    pthread_mutex_lock(&secondResource);
    printf("T1 acquired second resource!!\n");
    pthread_mutex_unlock(&secondResource);

    printf("T1 released second resource\n");
    pthread_mutex_unlock(&firstResource);
    printf("T1 released first resource\n");

    pthread_exit(NULL);
}

void *fun2()
{
    printf("T2 trying to acquire second resource...\n");
    pthread_mutex_lock(&secondResource);
    printf("T2 acquired second resource!!\n");

    sleep(2);

    printf("T2 trying to acquire first resource...\n");
    pthread_mutex_lock(&firstResource);
    printf("T2 acquired first resource!!\n");
    pthread_mutex_unlock(&firstResource);

    printf("T2 released first resource\n");
    pthread_mutex_unlock(&secondResource);
    printf("T2 released second resource\n");

    pthread_exit(NULL);
}

int main()
{
    // Initialize mutexes or resources
    pthread_mutex_init(&firstResource, NULL);
    pthread_mutex_init(&secondResource, NULL);

    // Thread available
    pthread_t T1, T2;

    // Thread creation
    pthread_create(&T1, NULL, fun1, NULL);
    pthread_create(&T2, NULL, fun2, NULL);

    // Join the thread and wait to finish
    pthread_join(T1, NULL);
    pthread_join(T2, NULL);

    // Will never arrive here
    printf("Thread joined\n");

    return 0;
}
