#include <cstdio>
#include <math.h>

#define PI 3.14159265358979323846

int main() {
  int runs;
  scanf("%d", &runs);
  for (int i = 0; i < runs; i++) {
    printf ("Scenario #%d:\n", i+1);
    double radius;
    int bullets;
    scanf("%lf %d", &radius, &bullets);

    double a = sin(PI / bullets);
    printf ("%.3f\n\n", (a * radius) / (a + 1));
  }
}
