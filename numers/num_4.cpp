#include "num_4.hpp"

#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>


using namespace std;


// Умножение по модулю без переполнения long long.
// Тип __int128 доступен в g++ и clang++.
long long multiplyModulo(
    long long a,
    long long b,
    long long modulo
) {
    return static_cast<long long>(
        (static_cast<__int128>(a) * b) % modulo
    );
}


// Быстрое возведение в степень по модулю:
//
// base^power mod modulo
//
// Используется для вычисления:
// A = g^a mod p
// B = g^b mod p
// K = B^a mod p или A^b mod p
long long powerModulo(
    long long base,
    long long power,
    long long modulo
) {
    long long result = 1;
    base %= modulo;

    while (power > 0) {
        if (power % 2 == 1) {
            result = multiplyModulo(
                result,
                base,
                modulo
            );
        }

        base = multiplyModulo(
            base,
            base,
            modulo
        );

        power /= 2;
    }

    return result;
}


// Проверка числа на простоту
bool isPrimeTask4(long long number) {
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


// Преобразование зашифрованной строки в hex
string bytesToHex(const string& data) {
    stringstream result;

    result << uppercase << hex << setfill('0');

    for (unsigned char symbol : data) {
        result << setw(2)
               << static_cast<int>(symbol);
    }

    return result.str();
}


// XOR-шифрование.
//
// XOR с одним и тем же ключом выполняет
// и шифрование, и расшифрование:
//
// (text XOR key) XOR key = text
//
// В качестве ключа используются байты
// общего секрета Диффи—Хеллмана.
string xorTransform(
    const string& text,
    long long sharedSecret
) {
    string result = text;

    for (size_t i = 0; i < text.size(); ++i) {
        // Выбираем один из восьми байтов ключа
        int shift = static_cast<int>((i % 8) * 8);

        unsigned char keyByte =
            static_cast<unsigned char>(
                (sharedSecret >> shift) & 0xFF
            );

        // Дополнительное изменение ключевого байта
        // зависит от позиции символа
        keyByte ^= static_cast<unsigned char>(
            (i * 31 + 17) & 0xFF
        );

        result[i] = static_cast<char>(
            static_cast<unsigned char>(text[i]) ^ keyByte
        );
    }

    return result;
}


// Основная функция задания 4
void task4() {
    long long p;
    long long g;
    long long privateA;
    long long privateB;

    cout << "\n===== ЗАДАНИЕ 4 =====\n";
    cout << "Обмен ключами Диффи—Хеллмана\n";
    cout << "После обмена ключами текст будет преобразован XOR-методом.\n\n";

    cout << "Введите простое число p: ";
    cin >> p;

    cout << "Введите основание g: ";
    cin >> g;

    cout << "Введите закрытый ключ первого пользователя a: ";
    cin >> privateA;

    cout << "Введите закрытый ключ второго пользователя b: ";
    cin >> privateB;

    if (!isPrimeTask4(p)) {
        cout << "\nОшибка: p должно быть простым числом.\n";
        return;
    }

    if (g <= 1 || g >= p) {
        cout << "\nОшибка: должно выполняться условие:\n";
        cout << "1 < g < p\n";
        return;
    }

    if (privateA <= 0 || privateB <= 0) {
        cout << "\nОшибка: закрытые ключи должны быть положительными.\n";
        return;
    }

    // Открытый ключ первого пользователя:
    //
    // A = g^a mod p
    long long publicA = powerModulo(
        g,
        privateA,
        p
    );

    // Открытый ключ второго пользователя:
    //
    // B = g^b mod p
    long long publicB = powerModulo(
        g,
        privateB,
        p
    );

    // Общий секрет первого пользователя:
    //
    // K1 = B^a mod p
    long long sharedSecretA = powerModulo(
        publicB,
        privateA,
        p
    );

    // Общий секрет второго пользователя:
    //
    // K2 = A^b mod p
    long long sharedSecretB = powerModulo(
        publicA,
        privateB,
        p
    );

    cout << "\nРезультаты обмена ключами:\n";
    cout << "Открытый ключ первого пользователя A = "
         << publicA << '\n';

    cout << "Открытый ключ второго пользователя B = "
         << publicB << '\n';

    cout << "Общий секрет первого пользователя K1 = "
         << sharedSecretA << '\n';

    cout << "Общий секрет второго пользователя K2 = "
         << sharedSecretB << '\n';

    if (sharedSecretA != sharedSecretB) {
        cout << "\nОшибка: общие секреты не совпадают.\n";
        return;
    }

    cout << "\nОбщий секрет успешно получен.\n";

    cin.ignore(10000, '\n');

    string sourceText;

    cout << "\nВведите исходный текст: ";
    getline(cin, sourceText);

    if (sourceText.empty()) {
        cout << "Ошибка: текст не должен быть пустым.\n";
        return;
    }

    // Шифрование
    string encryptedText = xorTransform(
        sourceText,
        sharedSecretA
    );

    // Расшифрование
    string decryptedText = xorTransform(
        encryptedText,
        sharedSecretA
    );

    cout << "\nИсходный текст:\n";
    cout << sourceText << '\n';

    cout << "\nЗашифрованный текст в HEX-виде:\n";
    cout << bytesToHex(encryptedText) << '\n';

    cout << "\nРасшифрованный текст:\n";
    cout << decryptedText << '\n';

    if (sourceText == decryptedText) {
        cout << "\nПроверка пройдена успешно.\n";
        cout << "Исходный и расшифрованный тексты совпадают.\n";
    } else {
        cout << "\nОшибка: тексты не совпадают.\n";
    }
}