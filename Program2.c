#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main()
{
    int pts[5] = {2, 3, 6, 7, 8};
    char *pts_desc[5] = {"Safety", "3pt FG", "TD", "TD+EP", "TD+2pt"};
    int score = 25;
    int combo_max[5] = {0, 0, 0, 0, 0};
    int i, j, n = 200000;
    //srand(time(NULL));
    for (i = 0; i < 5; i++) {
        combo_max[i] = score / pts[i];
    }
    int combos[n][5];
    int num_combos = 0;
    for (i = 0; i < n; i++) {
        int combo[5] = {0, 0, 0, 0, 0};
        int combo_sum = 0;
        for (j = 0; j < 5; j++) {
            combo[j] = rand() % (combo_max[j] + 1);
            combo_sum += combo[j] * pts[j];
        }
        if (combo_sum == score) {
            int not_in_list = 1;
            for (j = 0; j < num_combos; j++) {
                int k;
                for (k = 0; k < 5; k++) {
                    if (combos[j][k] != combo[k]) {
                        break;
                    }
                }
                if (k == 5) {
                    not_in_list = 0;
                    break;
                }
            }
            if (not_in_list) {
                for (j = 0; j < 5; j++) {
                    combos[num_combos][j] = combo[j];
                }
                num_combos++;
                char comboStr[100] = "";
                for (j = 0; j < 5; j++) {
                    if (j == 0) {
                        sprintf(comboStr, "%d %s", combo[j], pts_desc[j]);
                    } else {
                        char tempStr[100];
                        sprintf(tempStr, ", %d %s", combo[j], pts_desc[j]);
                        strcat(comboStr, tempStr);
                    }
                }
                printf("%s\n", comboStr);
            }
        }
    }
    return 0;
}