#include <map>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <iostream>
#include <cstdio>

using namespace std;

int main() {
  std::map<string, int> counts;
  int total = 0;

  string in;

  while (getline(cin, in)) {
    total++;

    if (counts.count(in) == 0) {
      counts[in] = 1;
    } else {
      counts[in]++;
    }
  }

  for (std::map<string, int>::iterator it = counts.begin(); it != counts.end(); ++it) {
    printf ("%s %.4f\n", it->first.c_str(), it->second * 100.0 / total * 1.0);
  }
}
