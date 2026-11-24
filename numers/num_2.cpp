#include "num_2.hpp"
#include "helpers.hpp"

#include <iostream>

using namespace std;

// Основная функция второго задания
void task2() {
    long long c;
    long long m;

    cout << "\n===== ЗАДАНИЕ 2 =====\n";
    cout << "Поиск обратного элемента d по модулю m\n";
    cout << "Необходимо найти d из условия:\n";
    cout << "(c * d) mod m = 1\n\n";

    cout << "Введите число c: ";
    cin >> c;

    cout << "Введите модуль m: ";
    cin >> m;

    if (m <= 1) {
        cout << "\nОшибка: модуль m должен быть больше 1.\n";
        return;
    }

    // Для вычислений используем положительный остаток c по модулю m
    long long cNormalized = normalizeModulo(c, m);

    long long u;
    long long v;

    long long gcdValue = extendedEuclidean(
        cNormalized,
        m,
        u,
        v
    );

    cout << "\nРезультат расширенного алгоритма Евклида:\n";
    cout << "НОД(c, m) = " << gcdValue << '\n';
    cout << "u = " << u << '\n';
    cout << "v = " << v << '\n';

// Обратный элемент существует только тогда, когда НОД(c, m) равен 1
    if (gcdValue != 1) {
        cout << "\nОбратного элемента не существует.\n";
        cout << "Числа c и m не являются взаимно простыми.\n";
        return;
    }

// Если: c * u + m * v = 1, то u является обратным элементом к c по модулю m.
    long long d = normalizeModulo(u, m);

    long long verification = (cNormalized * d) % m;

    cout << "\nУравнение Безу:\n";
    cout << cNormalized << " * (" << u << ") + "
         << m << " * (" << v << ") = "
         << gcdValue << '\n';

    cout << "\nОбратный элемент:\n";
    cout << "d = " << d << '\n';

    cout << "\nПроверка:\n";
    cout << "(" << c << " * " << d << ") mod "
         << m << " = " << verification << '\n';

    if (verification == 1) {
        cout << "Проверка пройдена успешно.\n";
    } else {
        cout << "Ошибка проверки.\n";
    }
}