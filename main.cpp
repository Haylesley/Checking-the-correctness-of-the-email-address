#include <iostream>
#include <string>
#include <cctype> // библиотека для работы с символами

using namespace std;

// Функция для проверки корректности символов в первой части email
bool isValidLocalCharacter(char c) {
    // Допустимые символы в первой части email
    const string validChars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!#$%&'*+-/=?^_{|}~`.";
    return validChars.find(c) != string::npos; // npos отсутствие найденного элемента
}

// Функция для проверки корректности символов во второй части email
bool isValidDomainCharacter(char c) {
    const string validDomainChars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789-.";
    return validDomainChars.find(c) != string::npos;
}

// Функция для получения первой части email
string getLocalPart(const string& email) {
    string localPart;
    for (char c : email) {
        if (c == '@') {
            break; // Остановимся, если нашли '@'
        }
        localPart += c; // Добавляем символ в локальную часть
    }
    return localPart;
}

// Функция для получения второй части email
string getDomainPart(const string& email) {
    size_t atPos = email.find('@'); // size_t беззнаковый тип для хранения индексов 
    if (atPos != string::npos && atPos + 1 < email.length()) {
        return email.substr(atPos + 1); // substr() возвращает все символы после '@'
    }
    return ""; // Если нет '@', возвращаем пустую строку
}

// Функция для проверки корректности email
bool isValidEmail(const string& email) {
    // Проверяем наличие '@'
    size_t atPos = email.find('@');
    if (atPos == string::npos || atPos == 0 || atPos == email.length() - 1) {
        return false; // '@' отсутствует или находится в некорректной позиции
    }

    // Получаем локальную и доменную части
    string localPart = getLocalPart(email);
    string domainPart = getDomainPart(email);

    // Проверяем длину частей
    if (localPart.length() < 1 || localPart.length() > 64 || 
        domainPart.length() < 1 || domainPart.length() > 63) {
        return false; // Длина частей некорректна
    }

    // Проверяем корректность символов в локальной части
    bool lastWasDot = false;
    for (size_t i = 0; i < localPart.length(); ++i) {
        char c = localPart[i];
        if (!isValidLocalCharacter(c)) {
            return false; // Неправильный символ
        }
        if (c == '.') {
            if (lastWasDot) {
                return false; // Две точки подряд
            }
            lastWasDot = true; // Запоминаем, что последним был символ '.'
        } else {
            lastWasDot = false; // Сброс, если текущий символ не точка
        }
    }

    // Проверяем корректность символов в доменной части
    lastWasDot = false; // Сброс для доменной части
    for (size_t i = 0; i < domainPart.length(); ++i) {
        char c = domainPart[i];
        if (!isValidDomainCharacter(c)) {
            return false; // Неправильный символ
        }
        if (c == '.') {
            if (lastWasDot) {
                return false; // Две точки подряд
            }
            lastWasDot = true; // Запоминаем, что последним был символ '.'
        } else {
            lastWasDot = false; // Сброс, если текущий символ не точка
        }
    }

    // Если все проверки пройдены, адрес корректен
    return true;
}

int main() {
    string email;
    cout << "Enter email address: ";
    cin >> email;

    if (isValidEmail(email)) {
        cout << "Yes" << endl;
    } else {
        cout << "No" << endl;
    }

    return 0;
}
