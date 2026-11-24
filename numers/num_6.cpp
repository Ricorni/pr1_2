#include "num_6.hpp"
#include "helpers.hpp"

#include <iostream>
#include <vector>

using namespace std;


// Печать числа в виде цепной дроби.
//
// Например:
//
// 143 / 169 = [0; 1, 5, 2]
//
// Алгоритм основан на последовательном применении
// алгоритма Евклида.
void printContinuedFraction(
    long long numerator,
    long long denominator
) {
    if (denominator == 0) {
        cout << "Цепная дробь не определена.\n";
        return;
    }

    if (denominator < 0) {
        numerator = -numerator;
        denominator = -denominator;
    }

    vector<long long> coefficients;

    while (denominator != 0) {
        long long integerPart = numerator / denominator;

        coefficients.push_back(integerPart);

        long long remainder = numerator % denominator;

        numerator = denominator;
        denominator = remainder;
    }

    cout << "[";

    for (size_t i = 0; i < coefficients.size(); ++i) {
        if (i == 1) {
            cout << "; ";
        } else if (i > 1) {
            cout << ", ";
        }

        cout << coefficients[i];
    }

    cout << "]";
}


// Основная функция задания 6
void task6() {
    // Вариант 1:
    //
    // 143a + 169b = 5
    const long long coefficientA = 143;
    const long long coefficientB = 169;
    const long long rightPart = 5;

    cout << "\n===== ЗАДАНИЕ 6 =====\n";
    cout << "Представление числа в виде цепной дроби\n";
    cout << "Решение уравнения в целых числах\n\n";

    cout << "Уравнение:\n";
    cout << coefficientA << "a + "
         << coefficientB << "b = "
         << rightPart << "\n\n";

    cout << "Цепная дробь для "
         << coefficientA << "/"
         << coefficientB << ":\n";

    printContinuedFraction(
        coefficientA,
        coefficientB
    );

    cout << "\n\n";

    cout << "Цепная дробь для "
         << coefficientB << "/"
         << coefficientA << ":\n";

    printContinuedFraction(
        coefficientB,
        coefficientA
    );

    cout << "\n\n";

    long long u;
    long long v;

    long long gcdValue = extendedEuclidean(
        coefficientA,
        coefficientB,
        u,
        v
    );

    cout << "Расширенный алгоритм Евклида:\n";
    cout << "НОД(" << coefficientA << ", "
         << coefficientB << ") = "
         << gcdValue << "\n";

    cout << "Коэффициент u = " << u << "\n";
    cout << "Коэффициент v = " << v << "\n";

    cout << "\nПроверка уравнения Безу:\n";
    cout << coefficientA << " * (" << u << ") + "
         << coefficientB << " * (" << v << ") = "
         << coefficientA * u + coefficientB * v
         << "\n";

    // Линейное диофантово уравнение
    // A*a + B*b = D имеет решение тогда и только тогда,
    // когда НОД(A, B) делит D.
    if (rightPart % gcdValue != 0) {
        cout << "\nРешений в целых числах нет.\n";

        cout << "Причина:\n";
        cout << "НОД(" << coefficientA << ", "
             << coefficientB << ") = "
             << gcdValue << "\n";

        cout << rightPart << " не делится на "
             << gcdValue << ".\n";

        cout << "\nУсловие существования решения:\n";
        cout << "НОД(A, B) должен делить D.\n";

        return;
    }

    // Если НОД делит правую часть,
    // можно найти частное решение.
    long long multiplier = rightPart / gcdValue;

    long long particularA = u * multiplier;
    long long particularB = v * multiplier;

    cout << "\nЧастное решение:\n";
    cout << "a0 = " << particularA << "\n";
    cout << "b0 = " << particularB << "\n";

    cout << "\nОбщее решение:\n";
    cout << "a = " << particularA
         << " + (" << coefficientB / gcdValue
         << ")t\n";

    cout << "b = " << particularB
         << " - (" << coefficientA / gcdValue
         << ")t\n";

    cout << "где t — любое целое число.\n";
}