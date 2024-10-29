#include <iostream>
#include <iomanip>
#include <windows.h>
using namespace std;

struct TreeNode {
    int value;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int val) : value(val), left(nullptr), right(nullptr) {}
};

// Функция для вставки узла в бинарное дерево поиска
TreeNode* insert(TreeNode* root, int value) {
    if (!root) {
        return new TreeNode(value);
    }
    if (value < root->value) {
        root->left = insert(root->left, value);
    } else {
        root->right = insert(root->right, value);
    }
    return root;
}

// Функция для поиска минимального узла в правом поддереве
TreeNode* findMin(TreeNode* node) {
    while (node && node->left) {
        node = node->left;
    }
    return node;
}

// Функция для удаления узла с заданным значением
TreeNode* deleteNode(TreeNode* root, int value) {
    if (!root) {
        return root; // Узел не найден
    }

    if (value < root->value) {
        root->left = deleteNode(root->left, value);
    } else if (value > root->value) {
        root->right = deleteNode(root->right, value);
    } else {
        // Узел найден
        if (!root->left) {
            TreeNode* temp = root->right;
            delete root;
            return temp;
        } else if (!root->right) {
            TreeNode* temp = root->left;
            delete root;
            return temp;
        }

        TreeNode* temp = findMin(root->right);
        root->value = temp->value;
        root->right = deleteNode(root->right, temp->value);
    }
    return root;
}

// Функция для обхода дерева в симметричном порядке (ин-ордер)
void inOrder(TreeNode* root) {
    if (root) {
        inOrder(root->left);
        cout << root->value << " ";
        inOrder(root->right);
    }
}

int main() {
    system("chcp 65001");
    TreeNode* root = nullptr;
    int value;

    // Ввод значений для вставки в дерево
    cout << "Введите значения для вставки в дерево (введите -1 для завершения):" << endl;
    while (true) {
        cin >> value;
        if (value == -1) break; // Завершение ввода
        root = insert(root, value);
    }

    // Вывод дерева
    cout << "Дерево после вставки узлов: ";
    inOrder(root);
    cout << endl;

    // Ввод значений для удаления из дерева
    cout << "Введите значения для удаления из дерева (введите -1 для завершения):" << endl;
    while (true) {
        cin >> value;
        if (value == -1) break; // Завершение ввода
        root = deleteNode(root, value);
        cout << "Удалено: " << value << endl;
    }

    // Вывод дерева после удаления
    cout << "Дерево после удаления узлов: ";
    inOrder(root);
    cout << endl;

    return 0;
}
