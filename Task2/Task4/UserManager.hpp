#pragma once 
#include <vector> 
#include <string>  
#include <fstream>  
#include <iomanip>  // ��� �������������� ������
#include <algorithm>  // ��� ������������� ���������� ����������� ����������
#include "User.hpp"  // ��������� ������������� ����� User

// ����� ��� ���������� ��������������
class UserManager {
public:
    UserManager(const string& filename);  // �����������, ����������� ��� �����
    void showUserList() const;  // ����� ��� ����������� ������ �������������
    void addUser();  // ����� ��� ���������� ������������
    void deleteUser();  // ����� ��� �������� ������������
    void editUser();  // ����� ��� �������������� ������������
    void saveChangesToFile();  // ����� ��� ���������� ��������� � ����
    void sendEmailToUser();  // ����� ��� �������� ��������� ������������ �� e-mail
    void sortUsers();  // ����� ��� ���������� ������������� �� ���������� ����
    User* findUserByFullName(string& fullName);  // ����� ��� ������ ������������ �� ������� �����
    User* findUserByLogin(string& login);  // ����� ��� ������ ������������ �� ������
    User* findUserByPhoneNumber(string& phoneNumber);  // ����� ��� ������ ������������ �� ������ ��������

private:
    vector<User> users;  // ������ ��� �������� �������������
    string filename;  // ��� ����� ��� ���������� �������������

    void loadUsersFromFile();  // ����� ��� �������� ������������� �� �����
    void writeUsersToFile() const;  // ����� ��� ������ ������������� � ����
    bool isUserExist(const User& user) const;  // ����� ��� �������� ������������� ������������
    bool authenticateUser(const User& user) const;  // ����� ��� �������������� ������������
    bool isPasswordCorrect(const User& user, const string& password) const;  // ����� ��� �������� ������������ ������
};

// ���������� ������� ������ UserManager

UserManager::UserManager(const string& filename)
    : filename(filename) {
    loadUsersFromFile();  // �������� ������������� �� ����� ��� �������� ���������� UserManager
}

User* UserManager::findUserByFullName(string& fullName) {
    for (auto& user : users) {
        if (user.getFullName() == fullName) {
            return &user;  // ������� ��������� �� ������������, ���� ������
        }
    }
    return nullptr;  // ������� nullptr, ���� ������������ �� ������
}

User* UserManager::findUserByLogin(string& login) {
    for (auto& user : users) {
        if (user.getLogin() == login) {
            return &user;  // ������� ��������� �� ������������, ���� ������
        }
    }
    return nullptr;  // ������� nullptr, ���� ������������ �� ������
}

User* UserManager::findUserByPhoneNumber(string& phoneNumber) {
    for (auto& user : users) {
        if (user.getPhoneNumber() == phoneNumber) {
            return &user;  // ������� ��������� �� ������������, ���� ������
        }
    }
    return nullptr;  // ������� nullptr, ���� ������������ �� ������
}

bool UserManager::isUserExist(const User& user) const {
    for (const auto& u : users) {
        if (u.getLogin() == user.getLogin()) {
            return true;  // ������� true, ���� ������������ � ����� ������� ����������
        }
    }
    return false;  // ������� false, ���� ������������ �� ������
}

void UserManager::loadUsersFromFile() {
    ifstream file(filename);  // �������� ����� ��� ������

    if (!file.is_open()) {
        cerr << "������ �������� ����� ��� ������: " << filename << "\n";
        return;
    }

    users.clear();  // ������� �������� ������ �������������

    string line;
    while (getline(file, line)) {
        istringstream iss(line);
        string lastName, firstName, middleName, phoneNumber, email, login, passwordHash;

        // ������ ������ ������������ �� ������
        if (getline(iss, lastName, '|') &&
            getline(iss, firstName, '|') &&
            getline(iss, middleName, '|') &&
            getline(iss, phoneNumber, '|') &&
            getline(iss, email, '|') &&
            getline(iss, login, '|') &&
            getline(iss, passwordHash, '|')) {
            User user(lastName, firstName, middleName, phoneNumber, email, login, passwordHash);
            users.push_back(user);  // ���������� ������������ � ������ users
        }
        else {
            cerr << "������ ������ ������ �� �����: " << filename << "\n";
        }
    }

    file.close();  // �������� �����
}

void UserManager::writeUsersToFile() const {
    ofstream file(filename);  // �������� ����� ��� ������

    if (!file.is_open()) {
        cerr << "������ �������� ����� ��� ������: " << filename << "\n";
        return;
    }

    // ������ ������ ������������� � ����
    for (const auto& user : users) {
        file << user.getLastName() << '|' << user.getFirstName() << '|' << user.getMiddleName() << '|'
            << user.getPhoneNumber() << '|' << user.getEmail() << '|' << user.getLogin() << '|' << user.getPasswordHash() << '\n';
    }

    file.close();  // �������� �����
}

void UserManager::showUserList() const {
    if (users.empty()) {
        cout << "������ ������������� ����.\n";
        return;
    }

    cout << "������ �������������:\n";
    // ����� ������ ������� ������������
    for (const auto& user : users) {
        cout << "���: " << user.getLastName() << " " << user.getFirstName() << " " << user.getMiddleName() << "\n"
            << "�������: " << user.getPhoneNumber() << "\n"
            << "E-mail: " << user.getEmail() << "\n"
            << "�����: " << user.getLogin() << "\n\n";
    }
}

void UserManager::addUser() {
    string lastName, firstName, middleName, phoneNumber, email, login, password;

    // ���� ������ ������ ������������ � ����������
    do {
        cout << "������� �������: ";
        getline(cin, lastName);
    } while (!User::isValidName(lastName));

    do {
        cout << "������� ���: ";
        getline(cin, firstName);
    } while (!User::isValidName(firstName));

    do {
        cout << "������� ��������: ";
        getline(cin, middleName);
    } while (!User::isValidName(middleName));

    do {
        cout << "������� ����� �������� � ������� +7-(222)-222-22-22: ";
        getline(cin, phoneNumber);
    } while (!User::isValidPhoneNumber(phoneNumber));

    do {
        cout << "������� e-mail: ";
        getline(cin, email);
    } while (!User::isValidEmail(email));

    cout << "������� �����: ";
    getline(cin, login);

    do {
        cout << "������� ������ (������� 8 ��������, ������ ��������� ���� �� ���� ��������� �����, ���� ��������, ���� ����� � ���� ����������� ������): ";
        getline(cin, password);
    } while (!User::isValidPassword(password));

    // �������� ������ ������������ � ���������� ��� � ������
    User newUser(lastName, firstName, middleName, phoneNumber, email, login, password);
    users.push_back(newUser);

    cout << "������������ ������� ��������.\n";
}

void UserManager::deleteUser() {
    string choice;
    cout << "�������� ������ �������� ������������:\n"
        << "1. �� �������-�����\n"
        << "2. �� ������\n"
        << "3. �� ������ ��������\n";

    getline(cin, choice);
    User* user = nullptr;

    // ����� ������ ������ ������������
    if (choice == "1") {
        string fullName;
        cout << "������� ��� ������������ (� ������� ������� ��� ��������): ";
        getline(cin, fullName);

        user = findUserByFullName(fullName);
        if (!user) {
            cerr << "������������ �� ������.\n";
            return;
        }
    }
    else if (choice == "2") {
        string login;
        cout << "������� ����� ������������: ";
        getline(cin, login);

        user = findUserByLogin(login);

        if (!user) {
            cerr << "������������ �� ������.\n";
            return;
        }
    }
    else if (choice == "3") {
        string phoneNumber;
        cout << "������� ����� �������� ������������: ";
        getline(cin, phoneNumber);

        user = findUserByPhoneNumber(phoneNumber);
        if (!user) {
            cerr << "������������ �� ������.\n";
            return;
        }
    }
    else {
        cerr << "�������� �����.\n";
        return;
    }

    // �������� ������ � �������� ������������
    if (user != nullptr) {
        string password;
        cout << "������� ������: ";
        getline(cin, password);
        hash<string> hasher;
        string passwordHash = to_string(hasher(password));

        if (passwordHash == user->getPasswordHash()) {
            users.erase(remove(users.begin(), users.end(), *user), users.end());
            cout << "������������ ������� ������.\n";
        }
        else {
            cerr << "������ ��������.\n";
            return;
        }
    }
}

void UserManager::editUser() {
    string choice;
    cout << "�������� ������ �������������� ������������:\n"
        << "1. �� �������-�����\n"
        << "2. �� ������\n"
        << "3. �� ������ ��������\n";

    getline(cin, choice);

    User* user = nullptr;

    // ����� ������ ������ ������������
    if (choice == "1") {
        string fullName;
        cout << "������� ��� ������������ (� ������� ������� ��� ��������): ";
        getline(cin, fullName);

        user = findUserByFullName(fullName);
        if (!user) {
            cerr << "������������ �� ������.\n";
        }
    }
    else if (choice == "2") {
        string login;
        cout << "������� ����� ������������: ";
        getline(cin, login);

        user = findUserByLogin(login);
        if (!user) {
            cerr << "������������ �� ������.\n";
        }
    }
    else if (choice == "3") {
        string phoneNumber;
        cout << "������� ����� �������� ������������: ";
        getline(cin, phoneNumber);

        user = findUserByPhoneNumber(phoneNumber);
        if (!user) {
            cerr << "������������ �� ������.\n";
        }
    }
    else {
        cerr << "�������� �����.\n";
        return;
    }

    // �������� ������ � �������������� ������������
    if (user != nullptr) {
        string password;
        cout << "������� ������: ";
        getline(cin, password);
        hash<string> hasher;
        string passwordHash = to_string(hasher(password));

        if (passwordHash == user->getPasswordHash()) {
            cout << "������� ����� ������:\n";
            string lastName, firstName, middleName, newPhoneNumber, email, login, password;

            // ���� ����� ������ � ����������
            do {
                cout << "������� ����� �������: ";
                getline(cin, lastName);
            } while (!User::isValidName(lastName));

            do {
                cout << "������� ����� ���: ";
                getline(cin, firstName);
            } while (!User::isValidName(firstName));

            do {
                cout << "������� ����� ��������: ";
                getline(cin, middleName);
            } while (!User::isValidName(middleName));

            do {
                cout << "������� ����� ����� �������� � ������� +7-(222)-222-22-22: ";
                getline(cin, newPhoneNumber);
            } while (!User::isValidPhoneNumber(newPhoneNumber));

            do {
                cout << "������� ����� e-mail: ";
                getline(cin, email);
            } while (!User::isValidEmail(email));

            cout << "������� ����� �����: ";
            getline(cin, login);

            do {
                cout << "������� ����� ������ (������� 8 ��������, ������ ��������� ���� �� ���� ��������� �����, ���� ��������, ���� ����� � ���� ����������� ������): ";
                getline(cin, password);
            } while (!User::isValidPassword(password));

            // ���������� ������ ������������
            user->setLastName(lastName);
            user->setFirstName(firstName);
            user->setMiddleName(middleName);
            user->setPhoneNumber(newPhoneNumber);
            user->setEmail(email);
            user->setLogin(login);
            user->setPassword(password);

            cout << "������ ������������ ������� ���������.\n";
        }
        else {
            cerr << "������ ��������.\n";
            return;
        }
    }
}

void UserManager::saveChangesToFile() {
    writeUsersToFile();  // ������ ��������� � ����
    cout << "��������� ��������� � ����.\n";
}

void UserManager::sendEmailToUser() {
    string choice;
    cout << "�������� ������ �������� ��������� ������������:\n"
        << "1. �� �������-�����\n"
        << "2. �� ������\n"
        << "3. �� ������ ��������\n";

    getline(cin, choice);

    // ����� ������ ������ ������������ ��� �������� ���������
    if (choice == "1") {
        string fullName;
        cout << "������� ��� ������������ (� ������� ������� ��� ��������): ";
        getline(cin, fullName);

        User* user = findUserByFullName(fullName);
        if (user) {
            string message;
            cout << "������� ��������� ��� �������� �� e-mail " << user->getEmail() << ": ";
            getline(cin, message, '\n');

            cout << "��������� ������� ���������� �� e-mail " << user->getEmail() << ".\n";
        }
        else {
            cerr << "������������ �� ������.\n";
        }
    }
    else if (choice == "2") {
        string login;
        cout << "������� ����� ������������: ";
        getline(cin, login);

        User* user = findUserByLogin(login);
        if (user) {
            string message;
            cout << "������� ��������� ��� �������� �� e-mail " << user->getEmail() << ": ";
            getline(cin, message, '\n');

            cout << "��������� ������� ���������� �� e-mail " << user->getEmail() << ".\n";
        }
        else {
            cerr << "������������ �� ������.\n";
        }
    }
    else if (choice == "3") {
        string phoneNumber;
        cout << "������� ����� �������� ������������: ";
        getline(cin, phoneNumber);

        User* user = findUserByPhoneNumber(phoneNumber);
        if (user) {
            string message;
            cout << "������� ��������� ��� �������� �� e-mail " << user->getEmail() << ": ";
            getline(cin, message, '\n');

            cout << "��������� ������� ���������� �� e-mail " << user->getEmail() << ".\n";
        }
        else {
            cerr << "������������ �� ������.\n";
        }
    }
    else {
        cerr << "�������� �����.\n";
    }
}

void UserManager::sortUsers() {
    string choice;
    cout << "�������� ���� ��� ����������:\n"
        << "1. �������\n"
        << "2. ���\n"
        << "3. ��������\n"
        << "4. ����� ��������\n"
        << "5. E-mail\n"
        << "6. �����\n";

    getline(cin, choice);

    // ����� ������ ���������� �������������
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
        cerr << "�������� �����.\n";
    }

    cout << "������ ������������� ������������.\n";
}

bool UserManager::authenticateUser(const User& user) const {
    for (const auto& u : users) {
        if (u.getLogin() == user.getLogin() && u.getPasswordHash() == user.getPasswordHash()) {
            return true;  // ������� true, ���� �������������� ������ �������
        }
    }
    return false;  // ������� false, ���� �������������� �� �������
}

bool UserManager::isPasswordCorrect(const User& user, const string& password) const {
    hash<string> passwordHash;
    // �������� ������������ ������
    return user.getPasswordHash() == to_string(passwordHash(password));
}