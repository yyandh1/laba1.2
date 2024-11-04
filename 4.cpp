#include <iostream>
#include <vector>
#include <Windows.h>
using namespace std;

const int MAX_SIZE = 100; // Максимальный размер массива

// Структура для хранения подмассива
struct Subarray {
    vector<char> data; // Данные подмассива
};

// Функция для проверки, существует ли подмассив в массиве уникальных подмассивов
bool existsInUnique(const vector<Subarray>& unique, const Subarray& subarray) {
    for (const auto& uniqueSubarray : unique) {
        if (uniqueSubarray.data == subarray.data) {
            return true;
        }
    }
    return false;
}

void generateSubarrays(char arr[], int n) {
    vector<Subarray> unique; // Для хранения уникальных подмассивов

    // Генерация всех подмассивов с использованием битовых масок
    int totalSubarrays = 1 << n; // 2^n подмассивов
    for (int mask = 0; mask < totalSubarrays; ++mask) {
        Subarray subarray;
        for (int i = 0; i < n; ++i) {
            // Если i-й бит установлен в 1, добавляем элемент в подмассив
            if (mask & (1 << i)) {
                subarray.data.push_back(arr[i]);
            }
        }

        // Проверка на уникальность и добавление подмассива
        if (!existsInUnique(unique, subarray)) {
            unique.push_back(subarray);
        }
    }

    // Вывод уникальных подмассивов
    cout << "Результат работы алгоритма: [";
    for (size_t i = 0; i < unique.size(); ++i) {
        cout << "{";
        for (size_t j = 0; j < unique[i].data.size(); ++j) {
            cout << unique[i].data[j];
            if (j < unique[i].data.size() - 1) cout << ", ";
        }
        cout << "}";
        if (i < unique.size() - 1) cout << ", ";
    }
    cout << "]" << endl;
}

int main() {
    system("chcp 65001");
    
    int n;
    cout << "Введите количество элементов в массиве: ";
    cin >> n;

    if (n > MAX_SIZE) {
        cout << "Количество элементов превышает максимальный размер." << endl;
        return 1;
    }

    char S[MAX_SIZE]; // Массив для хранения символов
    cout << "Введите элементы массива (по одному символу):" << endl;
    for (int i = 0; i < n; ++i) {
        cin >> S[i];
    }

    generateSubarrays(S, n);

    return 0;
}