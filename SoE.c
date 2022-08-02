#include <math.h>
#include <stdio.h>
#include <time.h>

#define MAX 200000
#define SOE_LOOPS 25

void SoE(int runs) {
    /* Create an array of values, where '1' indicates that a number is prime.
     * Start by assuming all numbers are prime by setting them to 1.
     */
    for (int i = 0; i < runs; i++){
        char primes[MAX];
        for (int i = 0; i < MAX; i++) {
            primes[i] = 1;
        }

        /* Loop through a portion of the array (up to the square root of MAX). If
         * it's a prime, ensure all multiples of it are set to zero (false), as they
         * clearly cannot be prime.
         */
        int limit = sqrt(MAX) + 1;
        for (int i = 2; i < limit; i++) {
            if (primes[i - 1]) {
                for (int j = i * i; j <= MAX; j += i) {
                    primes[j - 1] = 0;
                }
            }
        }
    }
}

int main(){
    int msg_count = 1;
    while (true) {
        unsigned long int elapsed;
        struct timeval t0, t1, dt;
        gettimeofday(&t0, NULL)
        SoE(SOE_LOOPS);
        gettimeofday(&t1, NULL)
        timeval_subtract(&dt, &t1, &t0);
        elapsed = (dt.tv_sec*1e6 + dt.tv_usec);
        printf("PI_1_B_MEANTIME_US:%i:MSG_COUNT:%i:\n\r", int elapsed/SOE_LOOPS, msg_count)
        msg_count += 1;
        sleep_ms(500)
    }
}