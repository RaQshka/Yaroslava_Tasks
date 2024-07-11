#pragma once 
#include <vector> 
#include <string>  
#include <fstream>  
#include <iomanip>  // Для форматирования вывода
#include <algorithm>  // Для использования алгоритмов стандартной библиотеки
#include "User.hpp"  // Включение заголовочного файла User

// Класс для управления пользователями
class UserManager {
public:
    UserManager(const string& filename);  // Конструктор, принимающий имя файла
    void showUserList() const;  // Метод для отображения списка пользователей
    void addUser();  // Метод для добавления пользователя
    void deleteUser();  // Метод для удаления пользователя
    void editUser();  // Метод для редактирования пользователя
    void saveChangesToFile();  // Метод для сохранения изменений в файл
    void sendEmailToUser();  // Метод для отправки сообщения пользователю на e-mail
    void sortUsers();  // Метод для сортировки пользователей по выбранному полю
    User* findUserByFullName(string& fullName);  // Метод для поиска пользователя по полному имени
    User* findUserByLogin(string& login);  // Метод для поиска пользователя по логину
    User* findUserByPhoneNumber(string& phoneNumber);  // Метод для поиска пользователя по номеру телефона

private:
    vector<User> users;  // Вектор для хранения пользователей
    string filename;  // Имя файла для сохранения пользователей

    void loadUsersFromFile();  // Метод для загрузки пользователей из файла
    void writeUsersToFile() const;  // Метод для записи пользователей в файл
    bool isUserExist(const User& user) const;  // Метод для проверки существования пользователя
    bool authenticateUser(const User& user) const;  // Метод для аутентификации пользователя
    bool isPasswordCorrect(const User& user, const string& password) const;  // Метод для проверки корректности пароля
};

// Реализация методов класса UserManager

UserManager::UserManager(const string& filename)
    : filename(filename) {
    loadUsersFromFile();  // Загрузка пользователей из файла при создании экземпляра UserManager
}

User* UserManager::findUserByFullName(string& fullName) {
    for (auto& user : users) {
        if (user.getFullName() == fullName) {
            return &user;  // Возврат указателя на пользователя, если найден
        }
    }
    return nullptr;  // Возврат nullptr, если пользователь не найден
}

User* UserManager::findUserByLogin(string& login) {
    for (auto& user : users) {
        if (user.getLogin() == login) {
            return &user;  // Возврат указателя на пользователя, если найден
        }
    }
    return nullptr;  // Возврат nullptr, если пользователь не найден
}

User* UserManager::findUserByPhoneNumber(string& phoneNumber) {
    for (auto& user : users) {
        if (user.getPhoneNumber() == phoneNumber) {
            return &user;  // Возврат указателя на пользователя, если найден
        }
    }
    return nullptr;  // Возврат nullptr, если пользователь не найден
}

bool UserManager::isUserExist(const User& user) const {
    for (const auto& u : users) {
        if (u.getLogin() == user.getLogin()) {
            return true;  // Возврат true, если пользователь с таким логином существует
        }
    }
    return false;  // Возврат false, если пользователь не найден
}

void UserManager::loadUsersFromFile() {
    ifstream file(filename);  // Открытие файла для чтения

    if (!file.is_open()) {
        cerr << "Ошибка открытия файла для чтения: " << filename << "\n";
        return;
    }

    users.clear();  // Очистка текущего списка пользователей

    string line;
    while (getline(file, line)) {
        istringstream iss(line);
        string lastName, firstName, middleName, phoneNumber, email, login, passwordHash;

        // Чтение данных пользователя из строки
        if (getline(iss, lastName, '|') &&
            getline(iss, firstName, '|') &&
            getline(iss, middleName, '|') &&
            getline(iss, phoneNumber, '|') &&
            getline(iss, email, '|') &&
            getline(iss, login, '|') &&
            getline(iss, passwordHash, '|')) {
            User user(lastName, firstName, middleName, phoneNumber, email, login, passwordHash);
            users.push_back(user);  // Добавление пользователя в вектор users
        }
        else {
            cerr << "Ошибка чтения строки из файла: " << filename << "\n";
        }
    }

    file.close();  // Закрытие файла
}

void UserManager::writeUsersToFile() const {
    ofstream file(filename);  // Открытие файла для записи

    if (!file.is_open()) {
        cerr << "Ошибка открытия файла для записи: " << filename << "\n";
        return;
    }

    // Запись данных пользователей в файл
    for (const auto& user : users) {
        file << user.getLastName() << '|' << user.getFirstName() << '|' << user.getMiddleName() << '|'
            << user.getPhoneNumber() << '|' << user.getEmail() << '|' << user.getLogin() << '|' << user.getPasswordHash() << '\n';
    }

    file.close();  // Закрытие файла
}

void UserManager::showUserList() const {
    if (users.empty()) {
        cout << "Список пользователей пуст.\n";
        return;
    }

    cout << "Список пользователей:\n";
    // Вывод данных каждого пользователя
    for (const auto& user : users) {
        cout << "ФИО: " << user.getLastName() << " " << user.getFirstName() << " " << user.getMiddleName() << "\n"
            << "Телефон: " << user.getPhoneNumber() << "\n"
            << "E-mail: " << user.getEmail() << "\n"
            << "Логин: " << user.getLogin() << "\n\n";
    }
}

void UserManager::addUser() {
    string lastName, firstName, middleName, phoneNumber, email, login, password;

    // Ввод данных нового пользователя с валидацией
    do {
        cout << "Введите фамилию: ";
        getline(cin, lastName);
    } while (!User::isValidName(lastName));

    do {
        cout << "Введите имя: ";
        getline(cin, firstName);
    } while (!User::isValidName(firstName));

    do {
        cout << "Введите отчество: ";
        getline(cin, middleName);
    } while (!User::isValidName(middleName));

    do {
        cout << "Введите номер телефона в формате +7-(222)-222-22-22: ";
        getline(cin, phoneNumber);
    } while (!User::isValidPhoneNumber(phoneNumber));

    do {
        cout << "Введите e-mail: ";
        getline(cin, email);
    } while (!User::isValidEmail(email));

    cout << "Введите логин: ";
    getline(cin, login);

    do {
        cout << "Введите пароль (минимум 8 символов, должен содержать хотя бы одну заглавную букву, одну строчную, одну цифру и один специальный символ): ";
        getline(cin, password);
    } while (!User::isValidPassword(password));

    // Создание нового пользователя и добавление его в список
    User newUser(lastName, firstName, middleName, phoneNumber, email, login, password);
    users.push_back(newUser);

    cout << "Пользователь успешно добавлен.\n";
}

void UserManager::deleteUser() {
    string choice;
    cout << "Выберите способ удаления пользователя:\n"
        << "1. По фамилии-имени\n"
        << "2. По логину\n"
        << "3. По номеру телефона\n";

    getline(cin, choice);
    User* user = nullptr;

    // Выбор метода поиска пользователя
    if (choice == "1") {
        string fullName;
        cout << "Введите ФИО пользователя (в формате Фамилия Имя Отчество): ";
        getline(cin, fullName);

        user = findUserByFullName(fullName);
        if (!user) {
            cerr << "Пользователь не найден.\n";
            return;
        }
    }
    else if (choice == "2") {
        string login;
        cout << "Введите логин пользователя: ";
        getline(cin, login);

        user = findUserByLogin(login);

        if (!user) {
            cerr << "Пользователь не найден.\n";
            return;
        }
    }
    else if (choice == "3") {
        string phoneNumber;
        cout << "Введите номер телефона пользователя: ";
        getline(cin, phoneNumber);

        user = findUserByPhoneNumber(phoneNumber);
        if (!user) {
            cerr << "Пользователь не найден.\n";
            return;
        }
    }
    else {
        cerr << "Неверный выбор.\n";
        return;
    }

    // Проверка пароля и удаление пользователя
    if (user != nullptr) {
        string password;
        cout << "Введите пароль: ";
        getline(cin, password);
        hash<string> hasher;
        string passwordHash = to_string(hasher(password));

        if (passwordHash == user->getPasswordHash()) {
            users.erase(remove(users.begin(), users.end(), *user), users.end());
            cout << "Пользователь успешно удален.\n";
        }
        else {
            cerr << "Пароль неверный.\n";
            return;
        }
    }
}

void UserManager::editUser() {
    string choice;
    cout << "Выберите способ редактирования пользователя:\n"
        << "1. По фамилии-имени\n"
        << "2. По логину\n"
        << "3. По номеру телефона\n";

    getline(cin, choice);

    User* user = nullptr;

    // Выбор метода поиска пользователя
    if (choice == "1") {
        string fullName;
        cout << "Введите ФИО пользователя (в формате Фамилия Имя Отчество): ";
        getline(cin, fullName);

        user = findUserByFullName(fullName);
        if (!user) {
            cerr << "Пользователь не найден.\n";
        }
    }
    else if (choice == "2") {
        string login;
        cout << "Введите логин пользователя: ";
        getline(cin, login);

        user = findUserByLogin(login);
        if (!user) {
            cerr << "Пользователь не найден.\n";
        }
    }
    else if (choice == "3") {
        string phoneNumber;
        cout << "Введите номер телефона пользователя: ";
        getline(cin, phoneNumber);

        user = findUserByPhoneNumber(phoneNumber);
        if (!user) {
            cerr << "Пользователь не найден.\n";
        }
    }
    else {
        cerr << "Неверный выбор.\n";
        return;
    }

    // Проверка пароля и редактирование пользователя
    if (user != nullptr) {
        string password;
        cout << "Введите пароль: ";
        getline(cin, password);
        hash<string> hasher;
        string passwordHash = to_string(hasher(password));

        if (passwordHash == user->getPasswordHash()) {
            cout << "Введите новые данные:\n";
            string lastName, firstName, middleName, newPhoneNumber, email, login, password;

            // Ввод новых данных с валидацией
            do {
                cout << "Введите новую фамилию: ";
                getline(cin, lastName);
            } while (!User::isValidName(lastName));

            do {
                cout << "Введите новое имя: ";
                getline(cin, firstName);
            } while (!User::isValidName(firstName));

            do {
                cout << "Введите новое отчество: ";
                getline(cin, middleName);
            } while (!User::isValidName(middleName));

            do {
                cout << "Введите новый номер телефона в формате +7-(222)-222-22-22: ";
                getline(cin, newPhoneNumber);
            } while (!User::isValidPhoneNumber(newPhoneNumber));

            do {
                cout << "Введите новый e-mail: ";
                getline(cin, email);
            } while (!User::isValidEmail(email));

            cout << "Введите новый логин: ";
            getline(cin, login);

            do {
                cout << "Введите новый пароль (минимум 8 символов, должен содержать хотя бы одну заглавную букву, одну строчную, одну цифру и один специальный символ): ";
                getline(cin, password);
            } while (!User::isValidPassword(password));

            // Обновление данных пользователя
            user->setLastName(lastName);
            user->setFirstName(firstName);
            user->setMiddleName(middleName);
            user->setPhoneNumber(newPhoneNumber);
            user->setEmail(email);
            user->setLogin(login);
            user->setPassword(password);

            cout << "Данные пользователя успешно обновлены.\n";
        }
        else {
            cerr << "Пароль неверный.\n";
            return;
        }
    }
}

void UserManager::saveChangesToFile() {
    writeUsersToFile();  // Запись изменений в файл
    cout << "Изменения сохранены в файл.\n";
}

void UserManager::sendEmailToUser() {
    string choice;
    cout << "Выберите способ отправки сообщения пользователю:\n"
        << "1. По фамилии-имени\n"
        << "2. По логину\n"
        << "3. По номеру телефона\n";

    getline(cin, choice);

    // Выбор метода поиска пользователя для отправки сообщения
    if (choice == "1") {
        string fullName;
        cout << "Введите ФИО пользователя (в формате Фамилия Имя Отчество): ";
        getline(cin, fullName);

        User* user = findUserByFullName(fullName);
        if (user) {
            string message;
            cout << "Введите сообщение для отправки на e-mail " << user->getEmail() << ": ";
            getline(cin, message, '\n');

            cout << "Сообщение успешно отправлено на e-mail " << user->getEmail() << ".\n";
        }
        else {
            cerr << "Пользователь не найден.\n";
        }
    }
    else if (choice == "2") {
        string login;
        cout << "Введите логин пользователя: ";
        getline(cin, login);

        User* user = findUserByLogin(login);
        if (user) {
            string message;
            cout << "Введите сообщение для отправки на e-mail " << user->getEmail() << ": ";
            getline(cin, message, '\n');

            cout << "Сообщение успешно отправлено на e-mail " << user->getEmail() << ".\n";
        }
        else {
            cerr << "Пользователь не найден.\n";
        }
    }
    else if (choice == "3") {
        string phoneNumber;
        cout << "Введите номер телефона пользователя: ";
        getline(cin, phoneNumber);

        User* user = findUserByPhoneNumber(phoneNumber);
        if (user) {
            string message;
            cout << "Введите сообщение для отправки на e-mail " << user->getEmail() << ": ";
            getline(cin, message, '\n');

            cout << "Сообщение успешно отправлено на e-mail " << user->getEmail() << ".\n";
        }
        else {
            cerr << "Пользователь не найден.\n";
        }
    }
    else {
        cerr << "Неверный выбор.\n";
    }
}

void UserManager::sortUsers() {
    string choice;
    cout << "Выберите поле для сортировки:\n"
        << "1. Фамилия\n"
        << "2. Имя\n"
        << "3. Отчество\n"
        << "4. Номер телефона\n"
        << "5. E-mail\n"
        << "6. Логин\n";

    getline(cin, choice);

    // Выбор метода сортировки пользователей
    if (choice == "1") {
        sort(users.begin(), users.end(), [](const User& u1, const User& u2) {
            return u1.getLastName() > u2.getLastName();
            });
    }
    else if (choice == "2") {
        sort(users.begin(), users.end(), [](const User& u1, const User& u2) {
            return u1.getFirstName() > u2.getFirstName();
            });
    }
    else if (choice == "3") {
        sort(users.begin(), users.end(), [](const User& u1, const User& u2) {
            return u1.getMiddleName() > u2.getMiddleName();
            });
    }
    else if (choice == "4") {
        sort(users.begin(), users.end(), [](const User& u1, const User& u2) {
            return u1.getPhoneNumber() > u2.getPhoneNumber();
            });
    }
    else if (choice == "5") {
        sort(users.begin(), users.end(), [](const User& u1, const User& u2) {
            return u1.getEmail() > u2.getEmail();
            });
    }
    else if (choice == "6") {
        sort(users.begin(), users.end(), [](const User& u1, const User& u2) {
            return u1.getLogin() > u2.getLogin();
            });
    }
    else {
        cerr << "Неверный выбор.\n";
    }

    cout << "Список пользователей отсортирован.\n";
}

bool UserManager::authenticateUser(const User& user) const {
    for (const auto& u : users) {
        if (u.getLogin() == user.getLogin() && u.getPasswordHash() == user.getPasswordHash()) {
            return true;  // Возврат true, если аутентификация прошла успешно
        }
    }
    return false;  // Возврат false, если аутентификация не удалась
}

bool UserManager::isPasswordCorrect(const User& user, const string& password) const {
    hash<string> passwordHash;
    // Проверка корректности пароля
    return user.getPasswordHash() == to_string(passwordHash(password));
}