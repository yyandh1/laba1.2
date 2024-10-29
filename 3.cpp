#include <iostream>
#include <numeric>

using namespace std;

const int MAX_SIZE = 100; // Максимальный размер множества

// Структура для хранения множества
struct Set {
    int elements[MAX_SIZE]; // Элементы множества
    int size; // Размер множества
};

// Функция для проверки возможности разбивки множества на подмножества с равной суммой
bool canPartition(int nums[], int size, int target, int currentSum, int index, bool included[]) {
    if (currentSum == target) {
        return true; // Найдено подмножество с нужной суммой
    }
    if (currentSum > target || index >= size) {
        return false; // Превышена сумма или достигнут конец массива
    }

    // Включаем текущий элемент
    included[index] = true;
    if (canPartition(nums, size, target, currentSum + nums[index], index + 1, included)) {
        return true;
    }

    // Исключаем текущий элемент
    included[index] = false;
    return canPartition(nums, size, target, currentSum, index + 1, included);
}

void printSubsets(int nums[], int size, bool included[]) {
    cout << "Подмножества с равной суммой:" << endl;
    cout << "{ ";
    for (int i = 0; i < size; ++i) {
        if (included[i]) {
            cout << nums[i] << " ";
        }
    }
    cout << "}" << endl;
    
    cout << "{ ";
    for (int i = 0; i < size; ++i) {
        if (!included[i]) {
            cout << nums[i] << " ";
        }
    }
    cout << "}" << endl;
}

int main() {
    system("chcp 65001");

    Set mySet; // Создаем экземпляр структуры Set
    cout << "Введите количество элементов в множестве: ";
    cin >> mySet.size;

    if (mySet.size > MAX_SIZE) {
        cout << "Количество элементов превышает максимальный размер." << endl;
        return 1;
    }

    cout << "Введите элементы множества (натуральные числа):" << endl;
    for (int i = 0; i < mySet.size; ++i) {
        cin >> mySet.elements[i];
    }

    int sum = accumulate(mySet.elements, mySet.elements + mySet.size, 0);

    if (sum % 2 != 0) {
        cout << "Невозможно разбить множество на подмножества с равной суммой." << endl;
        return 0;
    }

    int target = sum / 2;
    bool included[MAX_SIZE] = {false}; // Массив для отслеживания включенных элементов

    if (canPartition(mySet.elements, mySet.size, target, 0, 0, included)) {
        printSubsets(mySet.elements, mySet.size, included);
    } else {
        cout << "Невозможно разбить множество на подмножества с равной суммой." << endl;
    }

    return 0;
}
