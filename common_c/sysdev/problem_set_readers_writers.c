#include <stdio.h>
#include <pthread.h>

#define NUM_THREADS 5

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond_reader = PTHREAD_COND_INITIALIZER;
pthread_cond_t cond_writer = PTHREAD_COND_INITIALIZER;

void *reader(void *param);
void *writer(void *param);


int main(int argc, char *argv[])
{
    pthread_t reader_id, writer_id;
    int thread_ids[NUM_THREADS];
    for (int i=0; i < NUM_THREADS; ++i) {
        thread_ids[i] = i;
        pthread_create(&reader_id, NULL, reader, &thread_ids[i]);

    }

    for (int i=0; i < NUM_THREADS; ++i) {
        thread_ids[i] = i;
        pthread_create(&writer_id, NULL, writer, &thread_ids[i]);
    }

    for (int i = 0; i < NUM_THREADS; ++i) {
        pthread_join(reader_id, NULL);

    }

    for (int i=0; i < NUM_THREADS; ++i) {
        pthread_join(writer_id, NULL);
    }

    return 0;
}


void *reader(void *param)
{
    int _id = *((int*) param);
    // enter critical block
    pthread_mutex_lock(&mutex);
    if (_id == NUM_THREADS-1)
        pthread_cond_wait(&cond_reader, &mutex);

    fprintf(stdout, "reader: reading id %d\n", _id);

    // exit critical block
    pthread_mutex_unlock(&mutex);

    return 0;
}


void *writer(void *param)
{
    int _id = *((int*) param);
    // enter critical block
    pthread_mutex_lock(&mutex);
    if (_id == 0) {
        pthread_cond_wait(&cond_reader, &mutex);
    }
    fprintf(stdout, "writer: writing id %d\n", _id);
    if (_id > 0) {
        pthread_cond_broadcast(&cond_reader);
    } else {
        pthread_cond_signal(&cond_writer);
    }

    // exit critical block
    pthread_mutex_unlock(&mutex);
    return 0;
}
