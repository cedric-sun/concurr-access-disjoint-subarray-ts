// cesun, 11/29/20 8:44 PM.

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define N_TEST 3000
#define MAXN 100000


static int arr[MAXN];

struct Arg {
    int start, end, step, val;
};

void *modify(void *p) {
    struct Arg *arg = p;
    for (int i = arg->start; i < arg->end; i += arg->step) {
        arr[i] = arg->val;
    }
    return NULL;
}

int main() {
    pthread_t t0, t1;
    unsigned int seed;
    getentropy(&seed, sizeof(seed));
    srand(seed);
    for (int i = 0; i < N_TEST; ++i) {
        struct Arg *t0arg = malloc(sizeof(*t0arg));
        *t0arg = (struct Arg) {.start=0, .end=MAXN, .step=2, .val=rand()};
        struct Arg *t1arg = malloc(sizeof(*t1arg));
        *t1arg = (struct Arg) {.start=1, .end=MAXN, .step=2, .val=rand()};
        //printf("val=%d,%d | cut = %d\n", t0arg->val, t1arg->val, cut);
        pthread_create(&t0, NULL, modify, t0arg);
        pthread_create(&t1, NULL, modify, t1arg);

        pthread_join(t0, NULL);
        pthread_join(t1, NULL);

        for (int j = t0arg->start; j < t0arg->end; j += t0arg->step) {
            if (arr[j] != t0arg->val) {
                puts("PANIC!");
                return -1;
            }
        }
        for (int j = t1arg->start; j < t1arg->end; j += t1arg->step) {
            if (arr[j] != t1arg->val) {
                puts("PANIC!");
                return -1;
            }
        }
//        for (int j = 0; j < MAXN; ++j) {
//            printf("%d\t", arr[j]);
//        }
//        putchar('\n');
        free(t0arg);
        free(t1arg);
    }
    return 0;
}

