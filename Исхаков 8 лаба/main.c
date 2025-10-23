#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

void InputArrayFromFile(int arr[], int n, FILE *f);
void OutputArrayToFile(int arr[], int n, FILE *f);
void ProcessArray(int arr[], int n, FILE *f);

int main() {
    SetConsoleOutputCP(CP_UTF8);

    FILE *in, *out;
    in = fopen("D:\\dev\\programming\\input.txt", "r");   // путь к входному файлу
    out = fopen("D:\\dev\\programming\\output.txt", "w"); // путь к выходному файлу

    if (!in) {
        printf("Ошибка\n");
        return 1;
    }
    if (!out) {
        printf("Ошибка\n");
        fclose(in);
        return 1;
    }

    int n;
    fscanf(in, "%d", &n); // первое число — количество элементов массива
    if (n <= 0) {
        fprintf(out, "Ошибка\n");
        fclose(in);
        fclose(out);
        return 1;
    }

    int *array = (int*)malloc(n * sizeof(int));
    if (array == NULL) {
        fprintf(out, "Ошибка выделения памяти!\n");
        fclose(in);
        fclose(out);
        return 1;
    }

    InputArrayFromFile(array, n, in);

    fprintf(out, "Исходный массив:\n");
    OutputArrayToFile(array, n, out);

    ProcessArray(array, n, out);

    free(array);
    fclose(in);
    fclose(out);

    printf("Обработка завершена. Результат записан в output.txt\n");
    return 0;
}

void InputArrayFromFile(int arr[], int n, FILE *f) {
    for (int i = 0; i < n; i++) {
        fscanf(f, "%d", &arr[i]);
    }
}

void OutputArrayToFile(int arr[], int n, FILE *f) {
    for (int i = 0; i < n; i++) {
        fprintf(f, "%d ", arr[i]);
    }
    fprintf(f, "\n");
}

void ProcessArray(int arr[], int n, FILE *f) {
    if (n < 2) {
        fprintf(f, "В массиве слишком мало элементов\n");
        return;
    }

    int min_index = 0, max_index = 0;
    for (int i = 1; i < n; i++) {
        if (arr[i] < arr[min_index]) min_index = i;
        if (arr[i] > arr[max_index]) max_index = i;
    }

    int start_index = (min_index < max_index) ? min_index : max_index;
    int end_index   = (min_index < max_index) ? max_index : min_index;

    fprintf(f, "\nМинимальный элемент: %d (индекс %d)\n", arr[min_index], min_index);
    fprintf(f, "Максимальный элемент: %d (индекс %d)\n", arr[max_index], max_index);

    fprintf(f, "Чётные элементы между min и max:\n");
    int count = 0;
    for (int i = start_index + 1; i < end_index; i++) {
        if (arr[i] % 2 == 0) {
            fprintf(f, "%d ", arr[i]);
            count++;
        }
    }

    if (count == 0) {
        fprintf(f, "Таких элементов нет.\n");
    } else {
        fprintf(f, "\n");
    }
}
