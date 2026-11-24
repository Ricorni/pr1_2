#include "num_1.hpp"
#include "helpers.hpp"

#include <iostream>
#include <numeric>

using namespace std;


// Проверка числа на простоту
bool isPrime(long long number) {
    if (number < 2) {
        return false;
    }

    if (number == 2) {
        return true;
    }

    if (number % 2 == 0) {
        return false;
    }

    for (long long divisor = 3;
         divisor <= number / divisor;
         divisor += 2) {

        if (number % divisor == 0) {
            return false;
        }
    }

    return true;
}


// Первый алгоритм:
// Теорема Ферма: g^(p - 1) ≡ 1 (mod p)   =>    g^x mod p = g^(x mod (p - 1)) mod p
long long powerByFermat(
    long long g,
    long long x,
    long long p
) {
    g = normalizeModulo(g, p);
    long long reducedPower = x % (p - 1);
    long long result = 1;

    for (long long i = 0; i < reducedPower; ++i) {
        result = (result * g) % p;
    }

    return result;
}


// Второй алгоритм:
// 1) Быстрое возведение в степень.
// 2) Показатель степени рассматривается в двоичном виде.
// На каждом шаге:  =>
// - если текущий бит степени равен 1,
//   умножаем результат на текущее основание;
// - основание возводим в квадрат;
// - степень делим на 2.
long long powerByBinary(
    long long g,
    long long x,
    long long p
) {
    g = normalizeModulo(g, p);

    long long result = 1;

    while (x > 0) {
        if (x % 2 == 1) {
            result = (result * g) % p;
        }

        g = (g * g) % p;
        x /= 2;
    }

    return result;
}

void task1() {
    long long g;
    long long x;
    long long p;

    cout << "\n===== ЗАДАНИЕ 1 =====\n";
    cout << "Вычисление g^x mod p\n\n";

    cout << "Введите основание g: ";
    cin >> g;

    cout << "Введите показатель степени x: ";
    cin >> x;

    cout << "Введите модуль p: ";
    cin >> p;

    // Проверяем корректность модуля
    if (p <= 1) {
        cout << "\nОшибка: модуль p должен быть больше 1.\n";
        return;
    }

    // Проверяем показатель степени
    if (x < 0) {
        cout << "\nОшибка: показатель степени x не может быть отрицательным.\n";
        return;
    }

    // Проверяем простоту p
    if (!isPrime(p)) {
        cout << "\nОшибка: число p = " << p
             << " не является простым.\n";
        cout << "Теорема Ферма в данном случае неприменима.\n";
        return;
    }

    // Проверяем условие взаимной простоты g и p, типо по НОДУ и если он 1, то числа взаимопрросты
    long long gcdValue = gcd(g, p);

    if (gcdValue != 1) {
        cout << "\nОшибка: числа g и p не являются взаимно простыми.\n";
        cout << "НОД(g, p) = " << gcdValue << '\n';
        cout << "Условие теоремы Ферма не выполнено.\n";
        return;
    }

    cout << "\nУсловия теоремы Ферма выполнены:\n";
    cout << "- p = " << p << " является простым числом;\n";
    cout << "- НОД(g, p) = 1.\n";

    long long resultFermat = powerByFermat(g, x, p);
    long long resultBinary = powerByBinary(g, x, p);

    cout << "\nРезультаты вычислений:\n";

    cout << "1. Метод теоремы Ферма: "
         << resultFermat << '\n';

    cout << "2. Двоичное возведение в степень: "
         << resultBinary << '\n';

    if (resultFermat == resultBinary) {
        cout << "\nРезультаты совпадают.\n";
    } else {
        cout << "\nОшибка: результаты не совпадают.\n";
    }

    cout << "\nПояснение:\n";
    cout << "По малой теореме Ферма:\n";
    cout << "g^(p - 1) ≡ 1 mod p\n";
    cout << "Поэтому показатель степени можно заменить на x mod (p - 1).\n";
}