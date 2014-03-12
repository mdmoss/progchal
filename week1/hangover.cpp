#include <cstdio>
int main() {
  double goal;
  while (1) {
    scanf("%lf", &goal);
    if (goal == 0) {
      return 0;
    }

    int count = 0;
    double value = 0;

    while (value < goal) {
        count++;
        value += (1.0 / (count + 1) * 1.0);
    }
    printf("%d card(s)\n", count); 
  }
}
