#include <stdio.h>
#include <stdlib.h>
int main() {
    system("chcp 65001 > nul");
    int n;
    printf("Введите количество чисел: ");
    scanf("%d", &n);

    if (n < 2) {
        printf("Мало чисел.\n");
        return 0;
    }

    int a[n];
    printf("Введите числа: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }

    int min = a[0], max = a[0];
    int i_min = 0, i_max = 0;

    for (int i = 1; i < n; i++) {
        if (a[i] < min) {
            min = a[i];
            i_min = i;
        }
        if (a[i] > max) {
            max = a[i];
            i_max = i;
        }
    }

    if (i_min > i_max) {
        int t = i_min;
        i_min = i_max;
        i_max = t;
    }

    printf("Четные числа между %d и %d:\n", min, max);
    int ok = 0;
    for (int i = i_min + 1; i < i_max; i++) {
        if (a[i] % 2 == 0) {
            printf("%d ", a[i]);
            ok = 1;
        }
    }

    if (!ok)
        printf("Нет четных чисел.\n");

    return 0;
}
