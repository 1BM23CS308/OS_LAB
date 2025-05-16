#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>


#define B 5
int buf[B], in = 0, out = 0;
sem_t full, empty, mutex;

void* prod(void* _) {
    for (int i = 0; i < 10; i++) {
        int item = rand() % 100;
        sem_wait(&empty); sem_wait(&mutex);
        buf[in] = item;
        printf("P -> %d\n", item);
        in = (in + 1) % B;
        sem_post(&mutex); sem_post(&full);
        sleep(1);
    } return NULL;
}

void* cons(void* _) {
    for (int i = 0; i < 10; i++) {
        sem_wait(&full); sem_wait(&mutex);
        int item = buf[out];
        printf("C <- %d\n", item);
        out = (out + 1) % B;
        sem_post(&mutex); sem_post(&empty);
        sleep(2);
    } return NULL;
}

#define N 5
sem_t chop[N];

void* phil(void* a) {
    int id = *(int*)a;
    for (int i = 0; i < 3; i++) {
        printf("Philo %d thinking\n", id); sleep(1);
        sem_wait(&chop[id]);
        sem_wait(&chop[(id + 1) % N]);
        printf("Philo %d eating\n", id); sleep(2);
        printf("Philo %d done\n", id);
        sem_post(&chop[id]);
        sem_post(&chop[(id + 1) % N]);
    } return NULL;
}


int main() {
    pthread_t p, c, ph[N]; int id[N];

    sem_init(&mutex, 0, 1);
    sem_init(&empty, 0, B);
    sem_init(&full, 0, 0);
    pthread_create(&p, NULL, prod, NULL);
    pthread_create(&c, NULL, cons, NULL);
    pthread_join(p, NULL);
    pthread_join(c, NULL);

    for (int i = 0; i < N; i++) {
        sem_init(&chop[i], 0, 1);
        id[i] = i;
        pthread_create(&ph[i], NULL, phil, &id[i]);
    }
    for (int i = 0; i < N; i++) pthread_join(ph[i], NULL);
    return 0;
}
