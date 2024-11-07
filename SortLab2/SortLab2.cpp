#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <locale>
#include "SortLab1.h"

void inputStringUsingMalloc(char*& str) {
    int len = 0;
    char ch;

    std::cout << "Введите строку (по одному символу, завершите нажатием Enter):\n";

    while (std::cin.get(ch) && ch != '\n') {
        char* new_str = (char*)malloc(len + 2);
        if (!new_str) {
            std::cerr << "Ошибка выделения памяти!\n";
            free(str);
            return;
        }

        for (int i = 0; i < len; i++) {
            new_str[i] = str[i];
        }
        new_str[len++] = ch;
        new_str[len] = '\0';

        free(str);
        str = new_str;
    }

    processString(str, len);
    std::cout << "Результат (malloc): " << str << std::endl;
}

void inputStringUsingCallocRealloc(char*& str) {
    int size = 5;
    int len = 0;
    str = (char*)calloc(size, sizeof(char));
    if (!str) {
        std::cerr << "Ошибка выделения памяти!\n";
        return;
    }

    std::cout << "Введите строку (по несколько символов, завершите нажатием Enter):\n";
    char ch;
    while (std::cin.get(ch) && ch != '\n') {
        if (len >= size - 1) {
            size += 5;
            char* new_str = (char*)realloc(str, size * sizeof(char));
            if (!new_str) {
                std::cerr << "Ошибка перераспределения памяти!\n";
                free(str);
                return;
            }
            str = new_str;
        }
        str[len++] = ch;
        str[len] = '\0';
    }

    processString(str, len);
    std::cout << "Результат (calloc/realloc): " << str << std::endl;
}

void processStringFromFile() {
    FILE* file = fopen("input.txt", "r");
    if (!file) {
        std::cerr << "Ошибка открытия файла input.txt!\n";
        return;
    }

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    rewind(file);

    char* str = (char*)malloc(file_size + 1);
    if (!str) {
        std::cerr << "Ошибка выделения памяти!\n";
        fclose(file);
        return;
    }

    fread(str, 1, file_size, file);
    str[file_size] = '\0'; 
    fclose(file);

    std::cout << "Прочитанная строка до обработки: " << str << std::endl;

    processString(str, strlen(str));

    std::cout << "Строка после обработки: " << str << std::endl;

    file = fopen("output.txt", "w");
    if (!file) {
        std::cerr << "Ошибка открытия файла output.txt для записи!\n";
        free(str);
        return;
    }
    fputs(str, file);
    fclose(file);

    std::cout << "Результат обработанной строки записан в output.txt\n";
    free(str);
}

int main() {
    char* str = nullptr;
    int choice;

    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "Russian");

    std::cout << "Выберите вариант:\n";
    std::cout << "1. Ввод строки с использованием malloc\n";
    std::cout << "2. Ввод строки с использованием calloc и realloc\n";
    std::cout << "3. Чтение и обработка строки из файла\n";
    std::cout << "Введите ваш выбор (1, 2 или 3): ";
    std::cin >> choice;
    std::cin.ignore();

    switch (choice) {
    case 1:
        inputStringUsingMalloc(str);
        break;
    case 2:
        inputStringUsingCallocRealloc(str);
        break;
    case 3:
        processStringFromFile();
        break;
    default:
        std::cout << "Неверный выбор!\n";
        break;
    }

    return 0;
}