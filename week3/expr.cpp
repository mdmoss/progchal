#include <cstdio>
#include <stack>
#include <queue>
#include <stdlib.h>

using namespace std;

struct expr {
  char val;
  char op;
  struct expr *lc;
  struct expr *rc;
};

int main() {
  stack<struct expr*> parse;
  queue<struct expr*> print;
  char *out =(char *) malloc(10001);
  out[10000] = '\0';

  int cases;
  scanf ("%d\n", &cases);
  for (int i = 0; i < cases; i++) {
    char in;
    while (scanf("%c", &in) != 0) {
      if (!((in>= 'a' && in <= 'z') || (in >= 'A' && in <= 'Z'))) break;
      struct expr *e = (struct expr *) malloc(sizeof(expr));
      if (in >= 'a' && in <= 'z') {
        e->val = in;
        parse.push(e);
      } else {
        e->val = 0;
        e->op = in; 
        e->lc = parse.top(); 
        parse.pop();
        e->rc = parse.top(); 
        parse.pop();
        parse.push(e);
      }
    }
    print.push(parse.top());
    char *end = out + 10000;
    while (print.size()) {
      struct expr *e = print.front();
      print.pop();

      if (e->val) {
        end--;
        *end = e->val;
      } else {
        end--;
        *end = e->op;
        print.push(e->rc);
        print.push(e->lc);
      }
    }
    printf ("%s\n", end);
  }
}

