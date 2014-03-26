#include <vector>
#include <cstdio>
#include <math.h>

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

    int maxchips = 0;

    for (unsigned int i = 0; i < cookies.size(); i++) {
        for (unsigned int j = i + 1; j < cookies.size(); j++) {
              /* For each pair of points */
              /* Find the midpoint */
              pt mid = make_pair((cookies[j].x + cookies[i].x) / 2.0, (cookies[j].y + cookies[i].y) / 2.0);

              /* Make a normalized vector from midpoint to point */
              pt vec = make_pair(mid.x - cookies[i].x, mid.y - cookies[i].y);
              double len = sqrt(vec.x * vec.x + vec.y * vec.y);
              vec.x = vec.x / len; vec.y = vec.y / len;
              
              /* Find the distance from midpoint to circle centre */ 
              double distsq = (cookies[i].x - cookies[j].x) * (cookies[i].x - cookies[j].x);
              distsq += (cookies[i].y - cookies[j].y) * (cookies[i].y - cookies[j].y);

              double scale = sqrt(2.5 * 2.5 - 0.25 * distsq);

              /* Rotate and scale */ 
              pt upvec = make_pair(vec.y * -1 * scale, vec.x * scale);
              pt downvec = make_pair(vec.y * scale, vec.x * -1 * scale);

              pt up = make_pair(mid.x + upvec.x, mid.y + upvec.y);
              pt down = make_pair(mid.x + downvec.x, mid.y + downvec.y);

              int chips = 0;
              for (int k = 0; k < cookies.size(); k++) {
                if ((cookies[k].x - up.x) * (cookies[k].x - up.x) + (cookies[k].y - up.y) * (cookies[k].y - up.y) <= 2.5 * 2.5 + 0.001) {
                  chips++; 
                }
              }
              if (chips > maxchips) {
                maxchips = chips;
              }
              chips = 0;
              for (int k = 0; k < cookies.size(); k++) {
                if ((cookies[k].x - down.x) * (cookies[k].x - down.x) + (cookies[k].y - down.y) * (cookies[k].y - down.y) <= 2.5 * 2.5 + 0.001) {
                  chips++; 
                }
              }
              if (chips > maxchips) {
                maxchips = chips;
              }
        }
    }

   if (maxchips == 0 && cookies.size()) {
    maxchips++;
   }

   printf ("%d\n", maxchips);   
   return 0;
}
