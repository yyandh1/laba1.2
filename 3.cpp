#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <numeric>

using namespace std;

const int MAX_SIZE = 100; // Максимальный размер множества

// Структура для хранения узлов хеш-таблицы
struct Node {
    int data; // Данные узла
    Node* next;  // Указатель на следующий узел
};

// Структура для хеш-таблицы
struct HashSet {
    Node** table; // Указатель на массив указателей на узлы
    int size;     // Размер хеш-таблицы

    // Конструктор
    HashSet(int tableSize) : size(tableSize) {
        table = new Node*[size];
        for (int i = 0; i < size; ++i) {
            table[i] = nullptr; // Инициализация указателей
        }
    }

    // Деструктор
    ~HashSet() {
        clear(); // Освобождение памяти в деструкторе
        delete[] table; // Освобождение массива указателей
    }

    void clear() {
        for (int i = 0; i < size; ++i) {
            Node* current = table[i];
            while (current) {
                Node* temp = current;
                current = current->next;
                delete temp; // Освобождаем память текущего узла
            }
            table[i] = nullptr; // Обнуляем указатель
        }
    }

    bool contains(int value) const {
        int index = hash(value);
        Node* current = table[index];
        while (current) {
            if (current->data == value) {
                return true; // Элемент найден
            }
            current = current->next;
        }
        return false; // Элемент не найден
    }

    void add(int value) {
        if (contains(value)) {
            return; // Если элемент уже существует, ничего не делаем
        }

        int index = hash(value);
        Node* newNode = new Node{value, nullptr};

        // Вставка в начало цепочки
        if (table[index] == nullptr) {
            table[index] = newNode; 
        } else {
            newNode->next = table[index];
            table[index] = newNode;
        }
    }

private:
    int hash(int value) const {
        return value % size; // Простая хеш-функция
    }
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
    HashSet mySet(100); // Создаем экземпляр хеш-таблицы
    cout << "Введите количество элементов в множестве (максимум " << MAX_SIZE << "): ";
    
    int size;
    cin >> size;

    if (size > MAX_SIZE) {
        cout << "Количество элементов превышает максимальный размер." << endl;
        return 1;
    }

    cout << "Введите элементы множества (натуральные числа):" << endl;
    int elements[MAX_SIZE]; // Массив для хранения элементов
    for (int i = 0; i < size; ++i) {
        int value;
        cin >> value;

        // Добавляем значение в хеш-таблицу и в массив
        mySet.add(value);
        elements[i] = value; // Сохраняем элемент в массив
    }

    int sum = accumulate(elements, elements + size, 0);

    if (sum % 2 != 0) {
        cout << "Невозможно разбить множество на подмножества с равной суммой." << endl;
        return 0;
    }

    int target = sum / 2;
    bool included[MAX_SIZE] = {false}; // Массив для отслеживания включенных элементов

    if (canPartition(elements, size, target, 0, 0, included)) {
        printSubsets(elements, size, included);
    } else {
        cout << "Невозможно разбить множество на подмножества с равной суммой." << endl;
    }

    return 0;
}
