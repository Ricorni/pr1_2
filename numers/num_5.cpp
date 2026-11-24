#include "num_5.hpp"

#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>

using namespace std;


// Умножение по модулю
long long multiplyModuloTask5(
    long long a,
    long long b,
    long long modulo
) {
    return static_cast<long long>(
        (static_cast<__int128>(a) * b) % modulo
    );
}


// Быстрое возведение в степень:
//
// base^power mod modulo
long long powerModuloTask5(
    long long base,
    long long power,
    long long modulo
) {
    long long result = 1;

    base %= modulo;

    while (power > 0) {
        if (power % 2 == 1) {
            result = multiplyModuloTask5(
                result,
                base,
                modulo
            );
        }

        base = multiplyModuloTask5(
            base,
            base,
            modulo
        );

        power /= 2;
    }

    return result;
}


// Проверка числа на простоту
bool isPrimeTask5(long long number) {
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


// XOR-преобразование текста.
//
// Одна и та же функция используется
// для шифрования и расшифрования.
string xorTransformTask5(
    const string& text,
    long long sharedSecret
) {
    string result = text;

    for (size_t i = 0; i < text.size(); ++i) {
        int shift = static_cast<int>((i % 8) * 8);

        unsigned char keyByte =
            static_cast<unsigned char>(
                (sharedSecret >> shift) & 0xFF
            );

        keyByte ^= static_cast<unsigned char>(
            (i * 31 + 17) & 0xFF
        );

        result[i] = static_cast<char>(
            static_cast<unsigned char>(text[i]) ^ keyByte
        );
    }

    return result;
}


// Перевод строки в HEX
string bytesToHexTask5(const string& data) {
    stringstream result;

    result << uppercase
           << hex
           << setfill('0');

    for (unsigned char symbol : data) {
        result << setw(2)
               << static_cast<int>(symbol);
    }

    return result.str();
}


// Основная функция задания 5
void task5() {
    long long p;
    long long g;

    long long privateAlice;
    long long privateBob;

    long long privateMalloryAlice;
    long long privateMalloryBob;

    cout << "\n===== ЗАДАНИЕ 5 =====\n";
    cout << "Имитация атаки по середине MITM\n\n";

    cout << "Введите простое число p: ";
    cin >> p;

    cout << "Введите основание g: ";
    cin >> g;

    cout << "Введите закрытый ключ Алисы a: ";
    cin >> privateAlice;

    cout << "Введите закрытый ключ Боба b: ";
    cin >> privateBob;

    cout << "Введите закрытый ключ злоумышленника для Алисы x: ";
    cin >> privateMalloryAlice;

    cout << "Введите закрытый ключ злоумышленника для Боба y: ";
    cin >> privateMalloryBob;

    if (!isPrimeTask5(p)) {
        cout << "\nОшибка: p должно быть простым числом.\n";
        return;
    }

    if (g <= 1 || g >= p) {
        cout << "\nОшибка: должно выполняться условие 1 < g < p.\n";
        return;
    }

    if (privateAlice <= 0 ||
        privateBob <= 0 ||
        privateMalloryAlice <= 0 ||
        privateMalloryBob <= 0) {

        cout << "\nОшибка: все закрытые ключи должны быть положительными.\n";
        return;
    }

    // Настоящие открытые ключи Алисы и Боба
    long long publicAlice = powerModuloTask5(
        g,
        privateAlice,
        p
    );

    long long publicBob = powerModuloTask5(
        g,
        privateBob,
        p
    );

    // Открытые ключи злоумышленника
    long long fakePublicForBob = powerModuloTask5(
        g,
        privateMalloryAlice,
        p
    );

    long long fakePublicForAlice = powerModuloTask5(
        g,
        privateMalloryBob,
        p
    );

    cout << "\nНастоящие открытые ключи:\n";
    cout << "Открытый ключ Алисы A = "
         << publicAlice << '\n';

    cout << "Открытый ключ Боба B = "
         << publicBob << '\n';

    cout << "\nЗлоумышленник перехватывает ключи.\n";

    cout << "Алисе злоумышленник отправляет ключ: "
         << fakePublicForAlice << '\n';

    cout << "Бобу злоумышленник отправляет ключ: "
         << fakePublicForBob << '\n';

    // Секрет, который получает Алиса.
    //
    // Алиса думает, что это общий секрет с Бобом:
    //
    // K_A = fakePublicForAlice^a mod p
    long long secretAlice = powerModuloTask5(
        fakePublicForAlice,
        privateAlice,
        p
    );

    // Секрет, который получает злоумышленник
    // со стороны Алисы:
    //
    // K_MA = A^y mod p
    long long secretMalloryWithAlice = powerModuloTask5(
        publicAlice,
        privateMalloryBob,
        p
    );

    // Секрет, который получает Боб.
    //
    // Боб думает, что это общий секрет с Алисой:
    //
    // K_B = fakePublicForBob^b mod p
    long long secretBob = powerModuloTask5(
        fakePublicForBob,
        privateBob,
        p
    );

    // Секрет, который получает злоумышленник
    // со стороны Боба:
    //
    // K_MB = B^x mod p
    long long secretMalloryWithBob = powerModuloTask5(
        publicBob,
        privateMalloryAlice,
        p
    );

    cout << "\nСекретные ключи:\n";

    cout << "Секрет Алисы: "
         << secretAlice << '\n';

    cout << "Секрет злоумышленника с Алисой: "
         << secretMalloryWithAlice << '\n';

    cout << "Секрет Боба: "
         << secretBob << '\n';

    cout << "Секрет злоумышленника с Бобом: "
         << secretMalloryWithBob << '\n';

    if (secretAlice != secretMalloryWithAlice) {
        cout << "\nОшибка: ключ Алисы и злоумышленника не совпал.\n";
        return;
    }

    if (secretBob != secretMalloryWithBob) {
        cout << "\nОшибка: ключ Боба и злоумышленника не совпал.\n";
        return;
    }

    cout << "\nАтака успешно подготовлена.\n";
    cout << "У злоумышленника есть два разных общих ключа.\n";

    cin.ignore(10000, '\n');

    string sourceText;

    cout << "\nВведите сообщение Алисы: ";
    getline(cin, sourceText);

    if (sourceText.empty()) {
        cout << "Ошибка: сообщение не должно быть пустым.\n";
        return;
    }

    string changedText;

    cout << "Введите изменённое сообщение злоумышленника: ";
    getline(cin, changedText);

    if (changedText.empty()) {
        cout << "Ошибка: изменённое сообщение не должно быть пустым.\n";
        return;
    }

    // Алиса шифрует сообщение своим ключом.
    string encryptedFromAlice = xorTransformTask5(
        sourceText,
        secretAlice
    );

    cout << "\nАлиса отправляет зашифрованное сообщение.\n";
    cout << "Сообщение в HEX:\n";
    cout << bytesToHexTask5(encryptedFromAlice) << '\n';

    // Злоумышленник расшифровывает сообщение,
    // используя общий ключ с Алисой.
    string interceptedText = xorTransformTask5(
        encryptedFromAlice,
        secretMalloryWithAlice
    );

    cout << "\nЗлоумышленник расшифровал сообщение:\n";
    cout << interceptedText << '\n';

    // Злоумышленник шифрует уже изменённое сообщение
    // ключом, который разделяет с Бобом.
    string encryptedForBob = xorTransformTask5(
        changedText,
        secretMalloryWithBob
    );

    cout << "\nЗлоумышленник изменил сообщение на:\n";
    cout << changedText << '\n';

    cout << "\nЗлоумышленник отправляет Бобу новое сообщение в HEX:\n";
    cout << bytesToHexTask5(encryptedForBob) << '\n';

    // Боб расшифровывает сообщение своим ключом.
    string decryptedByBob = xorTransformTask5(
        encryptedForBob,
        secretBob
    );

    cout << "\nБоб получил сообщение:\n";
    cout << decryptedByBob << '\n';

    if (decryptedByBob == changedText) {
        cout << "\nАтака подтверждена.\n";
        cout << "Боб получил изменённое сообщение и не заметил подмену.\n";
    } else {
        cout << "\nОшибка: сообщение Бобу расшифровано неправильно.\n";
    }
}