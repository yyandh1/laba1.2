#include <iostream>

using namespace std;

const int MAX_SIZE = 100; // Максимальный размер массива

// Структура для хранения подмассива
struct Subarray {
    char data[MAX_SIZE]; // Данные подмассива
    int size; // Размер подмассива
};

// Функция для проверки, существует ли подмассив в массиве уникальных подмассивов
bool existsInUnique(Subarray unique[], int uniqueCount, Subarray subarray) {
    for (int i = 0; i < uniqueCount; ++i) {
        if (unique[i].size == subarray.size) {
            bool isSame = true;
            for (int j = 0; j < subarray.size; ++j) {
                if (unique[i].data[j] != subarray.data[j]) {
                    isSame = false;
                    break;
                }
            }
            if (isSame) return true;
        }
    }
    return false;
}

void generateSubarrays(char arr[], int n) {
    Subarray unique[MAX_SIZE]; // Для хранения уникальных подмассивов
    int uniqueCount = 0;

    // Генерация всех подмассивов
    for (int start = 0; start < n; ++start) {
        for (int end = start; end < n; ++end) {
            Subarray subarray; // Временный подмассив
            subarray.size = end - start + 1;
            for (int k = 0; k < subarray.size; ++k) {
                subarray.data[k] = arr[start + k];
            }

            // Проверка на уникальность и добавление подмассива
            if (!existsInUnique(unique, uniqueCount, subarray)) {
                unique[uniqueCount] = subarray;
                uniqueCount++;
            }
        }
    }

    // Вывод уникальных подмассивов
    cout << "Результат работы алгоритма: [";
    for (int i = 0; i < uniqueCount; ++i) {
        cout << "{";
        for (int j = 0; j < unique[i].size; ++j) {
            cout << unique[i].data[j];
            if (j < unique[i].size - 1) cout << ", ";
        }
        cout << "}";
        if (i < uniqueCount - 1) cout << ", ";
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
