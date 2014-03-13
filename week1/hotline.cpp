#include <cstdio>
#include <string.h>
#include <assert.h>
#include <cstdlib>

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
    //printf("\nmatching %s and %s\n", a, b);
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
    //printf("\nmatching %s and %s\n", a, b);
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

bool match(const char* a, const char* b) {
    //printf("\nmatching %s and %s\n", a, b);
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

const char *subswap(const char *sub) {
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

const char *dword(const char *sub) {
    if (match(sub, "I") || match (sub, "you")) {
        return "don't";
    }
    return "doesn't";
}

char *deplural(char *word) {
    char *ret = (char *)malloc(strlen(word) + 1);
    assert(ret != NULL);
    strcpy(ret, word);
    if (ret[strlen(word)-1] == 's') {
        ret[strlen(word)-1] = '\0';
        return ret;
    } else {
        free(ret);
        return word;
    }
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
                printf("yes, %s %s", subswap(parse[i].subject), parse[j].predicate);
                if (parse[i].object) {
                  printf(" %s.\n", parse[i].object);  
                } else {
                  printf("\n");  
                }
                answered = true;
            }
            else if (match(parse[j].predicate, parse[i].predicate) && match(parse[j].subject, "nobody") && match(parse[j].object, parse[i].object)) {
                printf("no, %s %s %s", subswap(parse[i].subject), dword(parse[i].subject), parse[i].predicate);
                if (parse[i].object) {
                  printf(" %s.\n", parse[i].object);  
                } else {
                  printf("\n");  
                }
                answered = true;
            }
            else if (match(parse[j].predicate, parse[i].predicate) && match(parse[j].subject, parse[i].subject) && match(parse[j].object, parse[i].object)) {
                if (!parse[i].is_negative) {
                    printf("yes, %s %s", subswap(parse[j].subject), parse[j].predicate);
                    if (parse[i].object) {
                      printf(" %s.\n", parse[i].object);  
                    } else {
                      printf("\n");  
                    }
                } else {
                    printf("no, %s %s %s", subswap(parse[j].subject), parse[i].dword, parse[j].predicate);
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

        /* Answer */

        int count = 0;
        bool answered = false;
        for (int j = 0; j < i && !answered; j++) {
            if (parse[j].is_statement && match(parse[j].subject, "everybody") && match(parse[j].predicate, parse[i].predicate) && match(parse[i].object, parse[j].object)) {
                printf ("everybody %s", parse[j].predicate);
                if (parse[i].object) {
                  printf(" %s.\n", parse[i].object);  
                } else {
                  printf("\n");  
                }
                j = i + 1;
                answered = true;
            }
            else if (parse[j].is_statement && match(parse[j].subject, "nobody") && match(parse[j].predicate, parse[i].predicate) && match(parse[i].object, parse[j].object)) {
                printf ("nobody %s", parse[j].predicate);
                if (parse[i].object) {
                  printf(" %s.\n", parse[i].object);  
                } else {
                  printf("\n");  
                }
                answered = true;
            } 
            else if (parse[j].is_statement && match(parse[j].predicate, parse[i].predicate) && match(parse[i].object, parse[j].object)) {
                count++;
            }
        }

        if (!answered && count == 0) {
            printf ("I don't know\n");
        }

        if (count == 1) {
            for (int j = 0; j < i; j++) {
                if (parse[j].is_statement && match(parse[j].predicate, parse[i].predicate) && match(parse[i].object, parse[j].object)) {
                    printf ("%s %s", subswap(parse[j].subject), parse[j].predicate);
                    if (parse[i].object) {
                      printf(" %s.\n", parse[i].object);  
                    } else {
                      printf(".\n");  
                    }
                } 
            }
        }
    
        if (count > 1) {
            int printed = 0;
            for (int j = 0; j < i; j++) {
                if (parse[j].is_statement && match(parse[j].predicate, parse[i].predicate) && match(parse[i].object, parse[j].object)) {
                    if (printed == 0) {
                        printf ("%s", parse[j].subject);
                        printed++;
                    } else if (printed == count - 1) {
                        printf ("and %s", parse[j].subject);
                        printed++;
                    } else {
                        printf (", %s", parse[j].subject);
                        printed++;
                    }
                } 
            }

            printf (" %s", deplural(parse[i].predicate));
            if (parse[i].object) {
              printf(" %s.\n", parse[i].object);  
            } else {
              printf(".\n");  
            }
        }

      } else if (!strcmp(parse[i].qword, "what")) {
        parse[i].dword = second;
        parse[i].subject = third;
        assert(!strcmp(clip(third, ' '), "do"));
        printf ("| dword: %s, sub: %s", parse[i].dword, parse[i].subject);

        /* Answer */
        int count = 0;
        for (int j = 0; j < i; j++) {
            if (match(parse[i].subject, parse[j].subject) || match(parse[j].subject, "everybody") || match(parse[j].subject, "nobody")) {
                printf("%s\n", parse[j].subject);
                /* This j applies - check for uniqueness */     
                bool unique = true;
                for (int k = 0; k < j; k++) {
                    if (match(parse[j].predicate, parse[k].predicate) && match(parse[j].object, parse[k].object)) {
                        unique = false;
                    }
                }
                if (unique) {
                    count++;
                }
            }
        }
        printf ("count: %d\n", count);
        int printed = 0;

        for (int j = 0; j < i; j++) {
            if (match(parse[i].subject, parse[j].subject) || match(parse[j].subject, "everybody") || match(parse[j].subject, "nobody")) {

                if (printed == 0) {
                    printf ("%s", subswap(parse[i].subject));
                    if (parse[j].is_negative || match(parse[j].subject, "nobody")) {
                        printf (" %s", dword(subswap(parse[i].subject)));
                    }
                    printf (" %s", deplural(parse[j].predicate));
                    if (parse[j].object) {
                        printf (" %s", parse[j].object);
                    }
                    printed++;
                    

                } else if (printed == count - 1) {
                    printf (", and");
                    if (parse[j].is_negative || match(parse[j].subject, "nobody")) {
                        printf (" %s", dword(subswap(parse[i].subject)));
                    }
                    printf (" %s", deplural(parse[j].predicate));
                    if (parse[j].object) {
                        printf (" %s", parse[j].object);
                    }
                    printed++;
                    printf (".");

                } else {
                    printf (",");
                    if (parse[j].is_negative || match(parse[j].subject, "nobody")) {
                        printf (" %s", dword(subswap(parse[i].subject)));
                    }
                    printf (" %s", deplural(parse[j].predicate));
                    if (parse[j].object) {
                        printf (" %s", parse[j].object);
                    }
                    printed++;

                }


            }
        }
      } 

      printf ("\n");
    }

  }
  

}
