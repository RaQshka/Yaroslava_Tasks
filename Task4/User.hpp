#include <string>
#include <regex>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <algorithm>

using namespace std;

class User {
public:
    // Конструктор класса User, инициализирующий все поля
    User(const string& lastName, const string& firstName, const string& middleName,
        const string& phoneNumber, const string& email, const string& login, const string& password);

    // Геттеры для получения значений полей
    string getLastName() const;
    string getFirstName() const;
    string getMiddleName() const;
    string getPhoneNumber() const;
    string getEmail() const;
    string getLogin() const;
    string getPasswordHash() const;
    string getFullName() const;

    // Сеттеры для установки значений полей
    void setLastName(const string& lastName);
    void setFirstName(const string& firstName);
    void setMiddleName(const string& middleName);
    void setPhoneNumber(const string& phoneNumber);
    void setEmail(const string& email);
    void setLogin(const string& login);
    void setPassword(const string& password);

    // Проверка валидности данных пользователя
    static bool isValidPhoneNumber(const string& phoneNumber);
    static bool isValidEmail(const string& email);
    static bool isValidPassword(const string& password);
    static bool isValidName(const string& name);

    // Переопределение оператора ==
    bool operator==(const User& other) const;

private:
    string lastName;
    string firstName;
    string middleName;
    string phoneNumber;
    string email;
    string login;
    string passwordHash;

    // Вспомогательные методы
    string hashPassword(const string& password) const; // Хэширование пароля
    bool hasDigits(const string& str) const; // Проверка наличия цифр в строке
    void capitalize(string& str) const; // Приведение первой буквы к верхнему регистру
    static bool isCorrectPasswordFormat(const string& password); // Проверка формата пароля
};

// Переопределение оператора == для сравнения пользователей по логину
bool User::operator==(const User& other) const {
    return this->login == other.login;
}

// Конструктор класса User, инициализирующий поля и хэширующий пароль
User::User(const string& lastName, const string& firstName, const string& middleName,
    const string& phoneNumber, const string& email, const string& login, const string& password)
    : lastName(lastName), firstName(firstName), middleName(middleName), phoneNumber(phoneNumber),
    email(email), login(login), passwordHash(hashPassword(password)) {
    capitalize(this->lastName);
    capitalize(this->firstName);
    capitalize(this->middleName);
}

// Геттеры для получения значений полей
string User::getLastName() const {
    return lastName;
}

string User::getFirstName() const {
    return firstName;
}

string User::getMiddleName() const {
    return middleName;
}

string User::getPhoneNumber() const {
    return phoneNumber;
}

string User::getEmail() const {
    return email;
}

string User::getLogin() const {
    return login;
}

string User::getPasswordHash() const {
    return passwordHash;
}

// Метод для получения полного имени пользователя
string User::getFullName() const {
    return lastName + " " + firstName + " " + middleName;
}

// Сеттеры для установки значений полей
void User::setLastName(const string& lastName) {
    this->lastName = lastName;
    capitalize(this->lastName);
}

void User::setFirstName(const string& firstName) {
    this->firstName = firstName;
    capitalize(this->firstName);
}

void User::setMiddleName(const string& middleName) {
    this->middleName = middleName;
    capitalize(this->middleName);
}

void User::setPhoneNumber(const string& phoneNumber) {
    if (isValidPhoneNumber(phoneNumber)) {
        this->phoneNumber = phoneNumber;
    }
    else {
        cerr << "Некорректный формат номера телефона.\n";
    }
}

void User::setEmail(const string& email) {
    if (isValidEmail(email)) {
        this->email = email;
    }
    else {
        cerr << "Некорректный формат e-mail.\n";
    }
}

void User::setLogin(const string& login) {
    this->login = login;
}

void User::setPassword(const string& password) {
    if (isValidPassword(password)) {
        this->passwordHash = hashPassword(password);
    }
    else {
        cerr << "Некорректный формат пароля.\n";
    }
}

// Проверка валидности номера телефона
bool User::isValidPhoneNumber(const string& phoneNumber) {
    // Формат +7-(222)-222-22-22
    regex pattern(R"(^\+\d{1,2}-\(\d{3}\)-\d{3}-\d{2}-\d{2}$)");
    return regex_match(phoneNumber, pattern);
}

// Проверка валидности e-mail
bool User::isValidEmail(const string& email) {
    // Простая проверка на формат
    regex pattern(R"(^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$)");
    return regex_match(email, pattern);
}

// Проверка валидности пароля
bool User::isValidPassword(const string& password) {
    return isCorrectPasswordFormat(password);
}

// Проверка валидности имени (фамилии или отчества)
bool User::isValidName(const string& name) {
    regex pattern(R"(^[a-zA-ZА-Яа-яЁё]{2,}$)");
    return regex_match(name, pattern);
}

// Метод для хэширования пароля
string User::hashPassword(const string& password) const {
    // Пример простейшего хэширования (не для реального применения!)
    // В реальной программе следует использовать более безопасные алгоритмы хэширования
    hash<string> hasher;
    return to_string(hasher(password));
}

// Проверка наличия цифр в строке
bool User::hasDigits(const string& str) const {
    return any_of(str.begin(), str.end(), ::isdigit);
}

// Приведение первой буквы к верхнему регистру
void User::capitalize(string& str) const {
    if (!str.empty()) {
        str[0] = toupper(str[0]);
        for (size_t i = 1; i < str.size(); ++i) {
            str[i] = tolower(str[i]);
        }
    }
}

// Проверка формата пароля (минимум 8 символов, одна заглавная, одна строчная, одна цифра, один специальный символ)
bool User::isCorrectPasswordFormat(const string& password) {
    if (password.length() < 8) {
        return false;
    }

    bool hasUpper = any_of(password.begin(), password.end(), ::isupper);
    bool hasLower = any_of(password.begin(), password.end(), ::islower);
    bool hasDigit = any_of(password.begin(), password.end(), ::isdigit);
    bool hasSpecial = any_of(password.begin(), password.end(), [](char c) {
        return !::isalnum(c);
        });

    return hasUpper && hasLower && hasDigit && hasSpecial;
}