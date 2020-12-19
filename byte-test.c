// cesun, 11/29/20 8:44 PM.

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define N_TEST 3000
#define MAXN 100000

static unsigned char arr[MAXN];

struct Arg {
    int start, end, step;
    unsigned char val;
};

void *modify(void *p) {
    struct Arg *arg = p;
    for (int i = arg->start; i < arg->end; i += arg->step) {
        arr[i] = arg->val;
    }
    return NULL;
}

#include <limits.h>

int main() {
    pthread_t t0, t1;
    unsigned int seed;
    getentropy(&seed, sizeof(seed));
    srand(seed);
    for (int i = 0; i < N_TEST; ++i) {
        struct Arg args[2] = {
            {.start=0, .end=MAXN, .step=2, .val=(rand() % UCHAR_MAX)},
            {.start=1, .end=MAXN, .step=2, .val=(rand() % UCHAR_MAX)}
        };

        pthread_create(&t0, NULL, modify, args);
        pthread_create(&t1, NULL, modify, args+1);

        pthread_join(t0, NULL);
        pthread_join(t1, NULL);

        for (int j=0;j<2;j++) {
            for (int k = args[j].start; k<args[j].end; k += args[j].step) {
                if (arr[k] != args[j].val) {
                    puts("thread unsafe!");
                    return -1;
                }
            }
        }
        //for (int j = 0; j < MAXN; ++j) {
        //    printf("%d\t", arr[j]);
        //}
        //putchar('\n');
    }
    return 0;
}

