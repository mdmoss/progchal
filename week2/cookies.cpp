#include <utility>
#include <vector>
#include <cstdio>

#define x first
#define y second

using namespace std;

typedef pair<double, double> pt;

int main() {
    vector<pt> cookies;

    pt in;
    while (scanf("%lf %lf", &in.x, &in.y) == 2) {
        cookies.push_back(in);
    }

    for (unsigned int i = 0; i < cookies.size(); i++) {
        for (unsigned int j = 0; j < cookies.size(); j++) {
            if (i != j) {
                /* For each pair of points */
                midX = j.x - i.x;
                midY = j.y - i.y;

                 

            }
        }
    }


   
   return 0;
}
