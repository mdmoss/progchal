#include <cstdio>
#include <algorithm>
#include <math.h>

#define MAX 100

char grid[MAX][MAX+1];
int result = 0;

int max_square(int x, int y, int size) {
    int max = 0;

    for (int i = x + 1; i < size; i++) {
        for (int j = 0; j <= y; j++) {

            /* Early escapes - Above the first point, or not valid for inclusion */
            if (x == i && i <= y) continue;
            if (grid[i][j] == 'B') continue;

            /* i >= x */
            int dx = i - x;
            int dy = j - y;

            /* No point continuing if the area is smaller */
            int area = dx * dx + dy * dy;
            if (area <= max || area <= result) continue;

            /* Check it it's actually valid */
            int jcount = 0;
            if (grid[x][y] == 'J') jcount++;
            if (grid[i][j] == 'J') jcount++;

            /* Bounds checks */
            if (i - dy < 0) continue;
            if (i - dy >= size) continue;
            /* Remebering dx >= 0 */
            if (j + dx >= size) continue;
            if (grid[i - dy][j + dx] == 'B') continue;
            if (grid[i - dy][j + dx] == 'J') jcount++;

            /* Bounds checks */
            if (i - dy - dx < 0) continue;
            if (i - dy - dx >= size) continue;
            /* Remebering dx >= 0 */
            if (j + dx - dy < 0) continue;
            if (j + dx - dy >= size) continue;
            if (grid[i - dy - dx][j + dx - dy] == 'B') continue;
            if (grid[i - dy - dx][j + dx - dy] == 'J') jcount++;

            if (jcount >= 3) {
                max = area;
            }
        }
    }
    return max; 
}

int main() {
    int size;

    scanf("%d", &size);
    for (int i = 0; i < size; i++) {
        scanf("%s", grid[i]);
    }

    /* This is small enough to brute force */
    /* This sqaure will always be the topmost-left square, so no point checking the final row */
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - 1; j++) {
            if (grid[i][j] != 'B') {
                /* Pretend it's part of a complete square and evaluate */
                result = std::max(max_square(i, j, size), result);
            }
        }
    }
    printf("%d\n", result);
}

