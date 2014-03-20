#include <cstdio>
#include <math.h>

#define PI 3.141592653589793

int main() {
  double ax, ay, bx, by, cx, cy;
  while (scanf("%lf %lf %lf %lf %lf %lf", &ax, &ay, &bx, &by, &cx, &cy) == 6) {
    double ab = sqrt((ax - bx) * (ax - bx) + (ay - by) * (ay - by));
    double bc = sqrt((bx - cx) * (bx - cx) + (by - cy) * (by - cy));
    double ac = sqrt((ax - cx) * (ax - cx) + (ay - cy) * (ay - cy));

    double area = fabs(0.5 * (ax * (by - cy) + bx * (cy - ay) + cx * (ay - by)));

    double radius = (ab * bc * ac) / (4 * area);

    printf("%.2f\n", 2 * radius * PI);
  }
}
