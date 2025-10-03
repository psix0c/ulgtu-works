#include <stdio.h>
#include <stdlib.h>

int main() {
    system("chcp 65001 > nul");

    int n;
    printf("Введите количество элементов массива: ");
    scanf("%d", &n);

    if (n <= 1) {
        printf("Недостаточно элементов для поиска.\n");
        return 0;
    }

    int arr[n];

    printf("Введите элементы массива через пробел: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    int min_val = arr[0];
    int max_val = arr[0];
    int min_index = 0;
    int max_index = 0;

    for (int i = 1; i < n; i++) {
        if (arr[i] < min_val) {
            min_val = arr[i];
            min_index = i;
        }
        if (arr[i] > max_val) {
            max_val = arr[i];
            max_index = i;
        }
    }

    if (min_index > max_index) {
        int temp = min_index;
        min_index = max_index;
        max_index = temp;
    }

    printf("Четные элементы между минимальным (%d) и максимальным (%d):\n", min_val, max_val);

    int found = 0;
    for (int i = min_index + 1; i < max_index; i++) {
        if (arr[i] % 2 == 0) {
            printf("%d ", arr[i]);
            found = 1;
        }
    }

    if (!found) {
        printf("Таких элементов нет.\n");
    }

    printf("\n");

    return 0;
}