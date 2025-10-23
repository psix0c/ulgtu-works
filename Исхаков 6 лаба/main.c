#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXN 100

int n;
int a[MAXN];
int b[MAXN];
int min_i, max_i;

static HFONT g_hFont;

void ReadFromFile() {
    FILE *f;
    if (fopen_s(&f, "D:\\dev\\programming\\1.txt", "rt") != 0) {
        MessageBoxW(NULL, L"Не удалось открыть файл D:\\dev\\programming\\1.txt", L"Ошибка", MB_OK | MB_ICONERROR);
        exit(1);
    }

    if (fscanf_s(f, "%d", &n) != 1 || n < 1 || n > MAXN) {
        MessageBoxW(NULL, L"Некорректное значение N в файле", L"Ошибка", MB_OK | MB_ICONERROR);
        fclose(f);
        n = 0;
        return;
    }

    for (int i = 0; i < n; i++)
        if (fscanf_s(f, "%d", &a[i]) != 1) {
             MessageBoxW(NULL, L"Не удалось прочитать все элементы массива", L"Ошибка", MB_OK | MB_ICONERROR);
             n = i;
             break;
        }

    fclose(f);

    if (n > 0) {
        memcpy(b, a, sizeof(int) * n);
    }
}

void FindMinMax() {
    if (n == 0) return;
    int min = b[0], max = b[0];
    min_i = 0; max_i = 0;

    for (int i = 1; i < n; i++) {
        if (b[i] < min) {
            min = b[i];
            min_i = i;
        }
        if (b[i] > max) {
            max = b[i];
            max_i = i;
        }
    }
}

void ProcessArray() {
    if (n < 2) return;
    int start = min_i < max_i ? min_i : max_i;
    int end = min_i > max_i ? min_i : max_i;

    for (int i = start + 1; i < end; i++) {
        if (b[i] % 2 != 0)
            b[i] = 0;
    }
}

void DrawArray(HDC hdc, int x0, int y0, int width, int height, int arr[], int highlight1, int highlight2) {
    if (n == 0) return;

    int barWidth = width / n;

    int maxAbsVal = 0;
    for (int i = 0; i < n; i++)
        if (abs(arr[i]) > maxAbsVal)
            maxAbsVal = abs(arr[i]);

    if (maxAbsVal == 0) maxAbsVal = 1;

    MoveToEx(hdc, x0, y0, NULL);
    LineTo(hdc, x0 + width, y0);


    for (int i = 0; i < n; i++) {
        int barHeight = (abs(arr[i]) * height) / maxAbsVal;

        int top, bottom;
        if (arr[i] >= 0) {
            top = y0 - barHeight;
            bottom = y0;
        } else {
            top = y0;
            bottom = y0 + barHeight;
        }

        int offset = (barWidth > 10) ? 5 : 0;

        RECT rect = {
            x0 + i * barWidth + offset,
            top,
            x0 + (i + 1) * barWidth - offset,
            bottom
        };

        HBRUSH brush;
        if (i == highlight1 && highlight1 != highlight2)
            brush = CreateSolidBrush(RGB(255, 0, 0));
        else if (i == highlight2 && highlight1 != highlight2)
            brush = CreateSolidBrush(RGB(0, 0, 255));
        else
            brush = CreateSolidBrush(RGB(0, 255, 0));

        FillRect(hdc, &rect, brush);
        DeleteObject(brush);

        char txt[10];
        sprintf_s(txt, sizeof(txt), "%d", arr[i]);

        SetBkMode(hdc, TRANSPARENT);

        int text_y = (arr[i] >= 0) ? top - 20 : bottom + 5;

        TextOutA(hdc, rect.left + offset, text_y, txt, strlen(txt));
    }
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    HDC hdc;
    PAINTSTRUCT ps;

    switch (msg) {
        case WM_CREATE:
            g_hFont = CreateFontW(18, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE,
                                  RUSSIAN_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
                                  DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, L"Arial");
            break;

        case WM_PAINT:
            hdc = BeginPaint(hwnd, &ps);

            SelectObject(hdc, g_hFont);

            TextOutW(hdc, 20, 10, L"Исходный массив:", 17);
            DrawArray(hdc, 50, 250, 400, 200, a, min_i, max_i);

            TextOutW(hdc, 500, 10, L"После обработки:", 17);
            DrawArray(hdc, 530, 250, 400, 200, b, min_i, max_i);

            TextOutW(hdc, 20, 480, L"Красный: Min", 12);
            TextOutW(hdc, 20, 500, L"Синий: Max", 10);
            TextOutW(hdc, 20, 520, L"Зеленый: прочие/обработанные", 29);

            EndPaint(hwnd, &ps);
            break;

        case WM_SIZE:
            InvalidateRect(hwnd, NULL, TRUE);
            break;

        case WM_DESTROY:
            DeleteObject(g_hFont);
            PostQuitMessage(0);
            break;
    }
    return DefWindowProc(hwnd, msg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {

    ReadFromFile();
    FindMinMax();
    ProcessArray();

    WNDCLASSW wc = {0};
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = L"Lab5Window";
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    RegisterClassW(&wc);

    HWND hwnd = CreateWindowW(L"Lab5Window", L"Лабораторная №5", WS_OVERLAPPEDWINDOW | WS_VSCROLL | WS_HSCROLL,
                             CW_USEDEFAULT, CW_USEDEFAULT, 1000, 600, NULL, NULL, hInstance, NULL);

    ShowWindow(hwnd, nCmdShow);

    InvalidateRect(hwnd, NULL, TRUE);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}