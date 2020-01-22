#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *thread_first(void *args)
{
    int *id = (int *) args;
    printf("\nThread number %d \n", *id);
}

int main(int argc, char *argv[])
{

    int number_of_threads = 10;
    pthread_t threads[number_of_threads];
    int t_args[number_of_threads];

    printf("Before create threads\n");
    for (int i = 0; i < number_of_threads; ++i) {
        t_args[i] = i;
        pthread_create(&threads[i], NULL, thread_first, (void *) &t_args[i]);
    }

    for (int j = 0; j < number_of_threads; ++j) {
        pthread_join(threads[j], NULL);
    }
    printf("After threads joined\n");
    pthread_exit(NULL);

    return 0;
}
