#include <cstdio>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

using namespace std;

int main() {
  int ops;
  scanf("%d\n", &ops);

  int *parent = (int *)malloc(30005 * sizeof(int));
  int *blocks_above = (int *)malloc(30005 * sizeof(int));
  int *blocks_below = (int *)malloc(30005 * sizeof(int));

  memset(parent, 0, 30005 * sizeof(int));
  memset(blocks_above, 0, 30005 * sizeof(int));
  memset(blocks_below, 0, 30005 * sizeof(int));

  for (int i = 0; i < ops; i++) {
    char op;
    scanf ("%c", &op);
    assert(op == 'M' || op == 'C');

    if (op == 'M') {

      int stack, to;
      scanf ("%d %d\n", &stack, &to);

      int base = stack;
      /* Find the base */
      while (parent[base] != 0) {
        base = parent[base];
        blocks_below[stack] += blocks_below[base];
      }
      parent[stack] = base;

      /* Add path compression here */

      /* Find the destination rep */
      int dest = to;
      while (parent[to] != 0) {
        to = parent[to];
      }

      parent[base] = to;

      blocks_below[base] = blocks_above[to] + 1;
      blocks_above[to] += blocks_above[base] + 1;
      blocks_above[base] = 0;

    } else {
      int stack;
      scanf ("%d\n", &stack);

      int rep = stack;
      int below = 0;
      while (parent[rep] != 0) {
        below += blocks_below[rep];
        rep = parent[rep];
      }

      printf ("%d\n", below);
    }
  }
}
