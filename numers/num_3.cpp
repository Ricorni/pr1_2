#include "num_3.hpp"
#include "helpers.hpp"

#include <iostream>

using namespace std;


void task3() {
    long long c;
    long long m;

    cout << "\n===== ЗАДАНИЕ 3 =====\n";
    cout << "Вычисление обратного числа c^(-1) mod m = d\n\n";

    cout << "Введите число c: ";
    cin >> c;

    cout << "Введите модуль m: ";
    cin >> m;

    if (m <= 1) {
        cout << "\nОшибка: модуль m должен быть больше 1.\n";
        return;
    }

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

    if (gcdValue != 1) {
        cout << "\nОбратное число не существует.\n";
        cout << "Числа c и m не являются взаимно простыми.\n";
        return;
    }

    //После работы алгоритма Евклида выполняется: c * u + m * v = 1
    //По модулю m: c * u ≡ 1 (mod m)
    //Значит: c^(-1) mod m = u mod m

    long long d = normalizeModulo(u, m);

    cout << "\nУравнение Безу:\n";
    cout << cNormalized << " * (" << u << ") + "
         << m << " * (" << v << ") = "
         << gcdValue << '\n';

    cout << "\nОбратное число:\n";
    cout << "c^(-1) mod m = " << d << '\n';

    long long verification =
        (cNormalized * d) % m;

    cout << "\nПроверка:\n";
    cout << "(" << c << " * " << d << ") mod "
         << m << " = " << verification << '\n';

    if (verification == 1) {
        cout << "Проверка пройдена успешно.\n";
    } else {
        cout << "Ошибка проверки.\n";
    }
}
