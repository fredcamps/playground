#include <stdio.h>
#include <pthread.h>
#define NUM_THREADS 4

void *example_thread(void *arg)
{
    printf("Hello thread %d\n", *((int*) arg));
    return 0;
}

int main(int argc, char *argv[])
{
    int i;
    int t_ids[NUM_THREADS];
    pthread_t tid[NUM_THREADS];
    for (i = 0; i < NUM_THREADS; i++) {
        t_ids[i] = i;
        pthread_create(&tid[i], NULL, example_thread, &t_ids[i]);
    }
    for (i = 0; i < NUM_THREADS; i++) {
        pthread_join(tid[i], NULL);
    }
    return 0;
}
