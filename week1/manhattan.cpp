#include <cstdio>
#include <stdlib.h>

int main() {

  int scns, range;
  scanf("%d", &scns);

  for (int i = 0; i < scns; i++) {
    printf("Scenario #%d:\n", i+1);

    scanf("%d", &range);
    int edge = range * 2 + 1;

    for (int z = 0; z < edge; z++) {
      printf("slice #%d:\n", z+1);
      for (int y = 0; y < edge; y++) {
        for (int x = 0; x < edge; x++) {
          int cost = abs(range - x) + abs(range - y) + abs(range - z);
          if (cost > range) {
            printf(".");
          } else {
            printf("%d", cost);
          }
        }
        printf("\n");
      }
    }

    printf("\n");
  }
  return 0;
}
