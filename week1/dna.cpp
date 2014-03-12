#include <cstdio>

/* Max string array size: 51 * 100 == ~5kb. Stackable
 * This approach is lazy and inefficient, but works thanks to the input limits */

int main (){
  int num_seqs, seq_len;
  char seqs[100][51];
  scanf("%d %d\n", &seq_len, &num_seqs);

  for (int i = 0; i < num_seqs; i++) {
    scanf("%s", seqs[i]);
  }

  int unsortedness[100] = {};

  for (int i = 0; i < num_seqs; i++) {
    for (int j = 0; j < seq_len; j++) {
      for (int k = j+1; k < seq_len; k++) {
        if (seqs[i][j] > seqs[i][k]) {
          unsortedness[i]++;
        }
      }
    }
  }

  // (seq_len * seq_len) is an upper bound of unsortedness
  for (int i = 0; i < (seq_len * seq_len); i++) {
    for (int j = 0; j < num_seqs; j++) {
      if (i == unsortedness[j]) {
        printf("%s\n", seqs[j]);
      }
    }
  }

  return 0;
}
