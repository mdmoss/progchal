#include <cstdio>
#include <stdlib.h>
#include <limits.h>
#include <math.h>

int congcheck(unsigned long long n, unsigned int *pieces, unsigned long long count) {
    int amodx = pieces[0] % n;
    for (int i = 1; i < count; i++) {
        if (pieces[i] % n != amodx) {
            return 0;
        }
    }
    return 1;
}

int main() {
    while (1) {
        unsigned long long flavours;
        scanf("%llu", &flavours);

        if (flavours == 0) return 0;

        unsigned int pieces[100010];
        unsigned long long sum = 0;
        unsigned long long min = 100000000000;
        for (unsigned long long i = 0; i < flavours; i++) {
            scanf("%llu", &pieces[i]);
            sum += pieces[i];
            if (pieces[i] < min) {
                min = pieces[i];
            }
        }

        if (sum % flavours != 0) {
            printf("0\n");
            continue;
        }

        unsigned long long bags = 0;
        unsigned long long limit = sqrt(sum);
        for (unsigned long long x = 2; x <= limit; x++) {
            if (x >= flavours && x < min && x % flavours == 0 && sum % x == 0 && congcheck(x, pieces, flavours)) {
                bags += min / x;
                if (min % x == 0) {
                    bags--;
                }
            }
            unsigned long long y = sum / x;
            if (y >= flavours && y < min && y % flavours == 0 && sum % y == 0 && x != y && congcheck(y, pieces, flavours)) {
                bags += min / y;
                if (min % y == 0) {
                    bags--;
                }
            }
        }
        printf ("%llu\n", bags);
    }
}

