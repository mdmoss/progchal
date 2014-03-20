#include <cstdio>
#include <math.h>

int near_root(int node) {
  return pow(2, floor(log2(node)));
}

int child_diff(int node) {
  if (node % 2 != 0) {
    return 0;
  }
  int root = near_root(node);
  if (root == node) {
    return node / 2;
  }
  
  int diff = root / 2;

  while (root != node) {
    if (node > root) {
      root += diff;
    } else {
      root -= diff;
    }
    diff /= 2;
  }

  return diff; 
}

int lhs(int node) {
  int diff = child_diff(node);
  while (node % 2 == 0) {
    node = node - diff;
    diff /= 2;
  }
  return node;
}

int rhs(int node) {
  int diff = child_diff(node);
  while (node % 2 == 0) {
    node = node + diff;
    diff /= 2;
  }
  return node;
}

int main() {
  int queries;
  scanf("%d", &queries);

  for (int i = 0; i < queries; i++) {
    int node;
    scanf("%d", &node);
    printf("%d %d\n", lhs(node), rhs(node));
  }
}
