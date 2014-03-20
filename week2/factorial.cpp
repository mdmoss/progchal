#include <cstdio>

int main() {
  typedef long long ll;

  int lines;
  scanf("%d", &lines);

  for (int i = 0; i < lines; i++) {
    ll in;
    scanf("%lld", &in);

    int res = in;
    int zeros = 0;

    while (res) {
      res = res / 5;
      zeros += res;
    }

    printf ("%d\n", zeros);
  }
}
