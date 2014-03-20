#include <cstdio>
#include <cstdlib>

#define MAX 1048576

typedef long long int ll;

ll *bigarray;

int main() {
  int in;
  bigarray = (ll *)malloc(sizeof(ll) * MAX);
  while (1) {
    scanf ("%d", &in);
    if (in == 0) return 0;
 
    int check = 0;
    int end = 0;
    int width = 1;
    bigarray[0] = 1;
    int done = 0;
   
    while (!done) {
      for (int i = 0; i < width; i++) {
        end++; 
        bigarray[end] = bigarray[check] * 10;
        end++;
        bigarray[end] = bigarray[check] * 10 + 1;
        check++;
      }

      for (int i = check; i < end; i++) {
        if (bigarray[i] % in == 0) {
          printf("%lld\n", bigarray[i]);
          done = 1;
          break;
        }
      }
      width *= 2;
    }
  }
}
