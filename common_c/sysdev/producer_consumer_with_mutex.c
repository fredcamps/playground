#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#define BUFFER_SIZE 3

pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond_consumer = PTHREAD_COND_INITIALIZER;
pthread_cond_t cond_producer = PTHREAD_COND_INITIALIZER;

int buffer[BUFFER_SIZE];
int add = 0;
int rem = 0;
int num = 0;

void *producer (void *param);
void *consumer (void *param);

void *producer(void *param)
{
    for (int i = 0; i < 20; i++) {
      pthread_mutex_lock(&m);
      // critical section
      if (num > BUFFER_SIZE) {
          exit(1);
      }
      while (num == BUFFER_SIZE) {
          pthread_cond_wait(&cond_producer, &m);
      }
      buffer[add] = i;
      add = (add+1) % BUFFER_SIZE;
      num++;
      // end critical section
      pthread_mutex_unlock(&m);
      pthread_cond_signal(&cond_consumer);
      printf("producer: inserted %d\n", i);
      fflush(stdout);
    }
    return 0;
}

void *consumer(void *param)
{
    int i;
    while (1) {
        pthread_mutex_lock(&m);
        // critical section
        if (num < 0) {
            exit(1);
        }
        while (num==0) {
            pthread_cond_wait(&cond_consumer, &m);
        }
        i = buffer[rem];
        rem = (rem + 1) % BUFFER_SIZE;
        num--;
        // end critical section
        pthread_mutex_unlock(&m);
        pthread_cond_signal(&cond_producer);
        printf("consumer: value %d\n", i);
        fflush(stdout);
    }
    return 0;
}

int main(int argc, char *argv[])
{
    pthread_t tid1, tid2;

    pthread_create(&tid1, NULL, producer, NULL);
    pthread_create(&tid2, NULL, consumer, NULL);

    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);

    return 0;
}
