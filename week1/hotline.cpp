#include <cstdio>
#include <string.h>
#include <assert.h>

#define MAX 100

void handle();

int main() {
  int dialogues;
  scanf("%d\n", &dialogues);

  while (dialogues) {
    handle();
    dialogues--;
  }
}

struct Line {
  bool is_statement;
  /* statement */
  bool is_negative;
  char* subject;
  char* dword;
  char* predicate;
  char* object;
  /* question */
  char *qword;
};

char *clip(char *s, char end) {
  while (*s != end && *s != '\0') {
    s++;
  }

  if (*s == '\0') {
    return NULL;
  }

  *s = '\0';
  s++;
  if (*s == '\0') {
    s = NULL;
  }
  return s;
}

bool match(char* a, char* b) {
    if (a == NULL && b == NULL) return true;
    if (a == NULL || b == NULL) return false;

    int alen = strlen(a);
    int blen = strlen(b);

    if (alen == blen+1 && a[alen-1] == 's') {
        return strncmp(a, b, blen) == 0;
    } else if (blen == alen+1 && b[blen-1] == 's') {
        return strncmp(a, b, alen) == 0;
    }

    return strcmp(a, b) == 0;
}

bool match(char* a, const char* b) {
    if (a == NULL && b == NULL) return true;
    if (a == NULL || b == NULL) return false;

    int alen = strlen(a);
    int blen = strlen(b);

    if (alen == blen+1 && a[alen-1] == 's') {
        return strncmp(a, b, blen) == 0;
    } else if (blen == alen+1 && b[blen-1] == 's') {
        return strncmp(a, b, alen) == 0;
    }

    return strcmp(a, b) == 0;
}

const char *subswap(char *sub) {
    if (match(sub, "I")) {
        return "you";
    }
    if (match(sub, "you")) {
        return "I";
    }
    return sub;
}

const char *dword(char *sub) {
    if (match(sub, "I") || match (sub, "you")) {
        return "don't";
    }
    return "doesn't";
}

void handle () {

  char input[MAX][MAX + 1];
  Line parse[MAX];
  int lines = 0;
  do {
    fgets(input[lines], MAX + 1, stdin);
    strtok(input[lines], "\n");
    lines++;
  } while (input[lines-1][strlen(input[lines-1])-1] != '!');

  /* Parse the lines */   
  for (int i = 0; i < lines; i++) {

    printf ("%s", input[i]);

    if (strchr(input[i], '!')) continue; // This is malformed - probably the end

    if (strchr(input[i], '.')) {
      clip(input[i], '.');
      parse[i].is_statement = true;
      parse[i].subject = input[i];
      printf (" - statement");

      char *second = clip(input[i], ' ');
      char *third = clip(second, ' ');

      if (strcmp(second, "don't") &&
          strcmp(second, "doesn't")) {
        parse[i].is_negative = false;
        printf (" - positive");
        parse[i].dword = NULL;
        parse[i].predicate = second;
        parse[i].object = third;
        printf (" | sub: %s, pred: %s", parse[i].subject, parse[i].predicate);

      } else {
        parse[i].is_negative = true;         
        printf (" - negative");
        parse[i].dword = second;
        char *fourth = clip(third, ' ');
        parse[i].dword = second;
        parse[i].predicate = third;
        parse[i].object = fourth;
        printf (" | sub: %s, dword: %s, pred: %s", parse[i].subject, parse[i].dword, parse[i].predicate);
      }

      if (parse[i].object) {
        printf(", obj: %s", parse[i].object);  
      }
      printf ("\n");


    } else {
      clip(input[i], '?');
      char *second = clip(input[i], ' ');
      char *third = clip(second, ' ');
      parse[i].is_statement = false;
      printf (" - question");
      parse[i].qword = input[i];
      printf ("| qword: %s", parse[i].qword);
      
      if (!strcmp(parse[i].qword, "do") || 
          !strcmp(parse[i].qword, "does")) {
        parse[i].subject = second;
        parse[i].predicate = third;
        parse[i].object = clip(third, ' ');

        printf (" | sub: %s, pred: %s", parse[i].subject, parse[i].predicate);
        if (parse[i].object) {
          printf(", obj: %s", parse[i].object);  
        }

        /* Actually answer it */
        bool answered = false;
        for (int j = 0; j < i; j++) {
            if (match(parse[j].predicate, parse[i].predicate) && match(parse[j].subject, "everybody") && match(parse[j].object, parse[i].object)) {
                printf("yes, %s %s", subswap(parse[j].subject), parse[j].predicate);
                if (parse[i].object) {
                  printf(" %s.\n", parse[i].object);  
                } else {
                  printf("\n");  
                }
                answered = true;
            }
            else if (match(parse[j].predicate, parse[i].predicate) && match(parse[j].subject, "nobody") && match(parse[j].object, parse[i].object)) {
                printf("no, %s %s %s", parse[i].subject, dword(parse[i].subject), parse[i].predicate);
                if (parse[i].object) {
                  printf(" %s.\n", parse[i].object);  
                } else {
                  printf("\n");  
                }
                answered = true;
            }
            else if (match(parse[j].predicate, parse[i].predicate) && match(parse[j].subject, parse[i].subject) && match(parse[j].object, parse[i].object)) {
                if (!parse[i].is_negative) {
                    printf("yes, %s %s", parse[j].subject, parse[j].predicate);
                    if (parse[i].object) {
                      printf(" %s.\n", parse[i].object);  
                    } else {
                      printf("\n");  
                    }
                } else {
                    printf("no, %s %s %s", parse[j].subject, parse[i].dword, parse[j].predicate);
                    if (parse[i].object) {
                      printf(" %s.\n", parse[i].object);  
                    } else {
                      printf("\n");  
                    }
                }
                answered = true;
            }
        }
        if (!answered) {
          printf("maybe\n");  
        }

      } else if (!strcmp(parse[i].qword, "who")) {
        parse[i].predicate = second;
        parse[i].object = third;
        printf (" | pred: %s", parse[i].predicate);
        if (parse[i].object) {
          printf(", obj: %s", parse[i].object);  
        }

      } else if (!strcmp(parse[i].qword, "what")) {
        parse[i].dword = second;
        parse[i].subject = third;
        assert(!strcmp(clip(third, ' '), "do"));
        printf ("| dword: %s, sub: %s", parse[i].dword, parse[i].subject);
      } 

      printf ("\n");
    }

  }

}
