#include <cstdio>
#include <stdlib.h>
#include <string.h>

int main() {
  int forks;
  scanf("%d", &forks);

  int *parents = (int *)malloc(sizeof(int) * forks);
  int *apples = (int *)malloc(sizeof(int) * forks);
  int *sums = (int *)malloc(sizeof(int) * forks);

  memset(parents, 0, sizeof(int) * forks);
  for(int i = 0; i < forks; i++) {
    apples[i] = 1;
    sums[i] = 1;
  }

  int u, v, cur;
  for(int i = 0; i < forks-1; i++) {
    scanf("%d %d", &u, &v);
    parents[v-1] = u;
    cur = u;
    while (cur) {
      sums[cur-1]++;
      cur = parents[cur-1];
    }
  }

  int queries;
  scanf("%d", &queries);

  char command;
  int x;
  int diff;
  for (int i = 0; i < queries; i++) {
    scanf(" %c %d", &command, &x); 
    
    if (command == 'C') {
      if (apples[x-1] == 1) {
        apples[x-1] = 0;
        diff = -1;
      } else {
        apples[x-1] = 1;
        diff = 1;
      }
      cur = x;
      while (cur) {
        sums[cur-1] += diff;
        cur = parents[cur-1];
      }
    } else {
      printf("%d\n", sums[x-1]);
    }
  }
}
