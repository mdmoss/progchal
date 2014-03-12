#include <cstdio>

int main() {
  
  int goal;
  scanf("%d", &goal);

  int l = 0, r = 0;

  int sum = 0;
  int ways = 0;

  while (1) {
    if (l > r) {
      /* We're done. Result time */
      printf("%d\n", ways);
      return 0;
    } else if (sum <= goal) {
      /* Add a right cow */
      r++;
      sum += r;
    } else if (sum > goal){
      /* Remove a left cow */
      sum -= l;
      l++;
    }

    if (sum == goal) {
      ways++;
    }
  }
}
