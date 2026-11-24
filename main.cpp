#include <iostream>
#include <clocale>
#include <limits>

#include "numers/num_1.hpp"
#include "numers/num_2.hpp"
#include "numers/num_3.hpp"
#include "numers/num_4.hpp"
#include "numers/num_5.hpp"
#include "numers/num_6.hpp"

using namespace std;

void menu() {
    cout << "\n===== МЕНЮ =====\n";

    cout << "1) Реализация сравнения по модулю простого числа "
            "через теорему Ферма и свойства степеней\n";

    cout << "2) Реализация расширенного алгоритма Евклида "
            "c * d mod m = 1\n";

    cout << "3) Реализация расширенного алгоритма Евклида "
            "для взаимно обратного числа 1/c mod m = d\n";

    cout << "4) Реализация программы шифрования данных "
            "для преобразованного исходного текста\n";

    cout << "5) Реализация атаки по середине MITM "
            "на протокол Диффи—Хеллмана\n";

    cout << "6) Реализация решения уравнения "
            "143a + 169b = 5\n";

    cout << "0) Выход\n";
}

int main() {
    setlocale(LC_ALL, "Russian");

    int choice;

    while (true) {
        menu();

        cout << "\nВведите номер задачи: ";
        cin >> choice;

        if (cin.fail()) {
            cout << "Ошибка: необходимо ввести число.\n";

            cin.clear();
            cin.ignore(
                numeric_limits<streamsize>::max(),
                '\n'
            );

            continue;
        }

        switch (choice) {
            case 1:
                task1();
                break;

            case 2:
                task2();
                break;

            case 3:
                task3();
                break;

            case 4:
                task4();
                break;

            case 5:
                task5();
                break;

            case 6:
                task6();
                break;

            case 0:
                cout << "Программа завершена.\n";
                return 0;

            default:
                cout << "Такого пункта меню нет.\n";
                break;
        }

        cout << "\nНажмите Enter, чтобы продолжить...";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.get();
    }
}