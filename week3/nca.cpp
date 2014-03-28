#include <cstdio>
#include <stdlib.h>
#include <string.h>

int main() {
  int cases;
  scanf ("%d\n", &cases);

  for (int i = 0; i < cases; i++) {
    int nnodes;
    scanf ("%d\n", &nnodes);
    int *nodes = (int *)malloc(sizeof(int) * nnodes);
    memset(nodes, -1, sizeof(int) * nnodes);
    for (int j = 0; j < nnodes - 1; j++) {
      int p, c;
      scanf ("%d %d", &p, &c);
      nodes[c-1] = p;
    }
    int finda, findb;
    scanf ("%d %d", &finda, &findb);
  
    int *seen = (int *)malloc(sizeof(int) * nnodes);
    memset(seen, 0, sizeof(int) * nnodes);
    int cur = finda;
    while (cur != -1) {
      seen[cur - 1] = true;
      cur = nodes[cur - 1];
    }

    int res = -1;
    cur = findb;
    while (res == -1) {
      if (seen[cur - 1]) {
        res = cur;
      }
      cur = nodes[cur - 1];
    }
    printf ("%d\n", res); 
  }
}
