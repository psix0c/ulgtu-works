#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

void InputArray(int arr[], int n);
void OutputArray(int arr[], int n);
void UpdateArray(int arr[], int n);

int main() {
    SetConsoleOutputCP(CP_UTF8);

    int n;
    int *array;

    printf("Введите количество элементов массива: ");
    scanf("%d", &n);

    if (n <= 0) {
        printf("Ошибка: количество элементов должно быть больше нуля.\n");
        return 1;
    }

    array = (int*)malloc(n * sizeof(int));

    if (array == NULL) {
        printf("Ошибка выделения памяти!\n");
        return 1;
    }

    printf("Введите %d элементов массива:\n", n);
    InputArray(array, n);

    printf("\nВаш массив:\n");
    OutputArray(array, n);
    UpdateArray(array, n);
    free(array);

    return 0;
}

void InputArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("Элемент [%d]: ", i);
        scanf("%d", &arr[i]);
    }
}

void OutputArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void UpdateArray(int arr[], int n) {
    if (n < 2) {
        printf("\nВ массиве слишком мало элементов для поиска.\n");
        return;
    }

    int min_index = 0;
    int max_index = 0;
    for (int i = 1; i < n; i++) {
        if (arr[i] < arr[min_index]) {
            min_index = i;
        }
        if (arr[i] > arr[max_index]) {
            max_index = i;
        }
    }

    int start_index, end_index;
    if (min_index < max_index) {
        start_index = min_index;
        end_index = max_index;
    } else {
        start_index = max_index;
        end_index = min_index;
    }

    printf("\nМинимальный элемент: %d (индекс %d)\n", arr[min_index], min_index);
    printf("Максимальный элемент: %d (индекс %d)\n", arr[max_index], max_index);

    printf("Четные элементы между min и max:\n");
    int count = 0;
    for (int i = start_index + 1; i < end_index; i++) {
        if (arr[i] % 2 == 0) {
            printf("%d ", arr[i]);
            count++;
        }
    }

    if (count == 0) {
        printf("Таких элементов нет.\n");
    } else {
        printf("\n");
    }
}