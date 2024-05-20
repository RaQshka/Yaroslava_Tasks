#include <string>
#include <regex>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <algorithm>

using namespace std;

class User {
public:
    // ����������� ������ User, ���������������� ��� ����
    User(const string& lastName, const string& firstName, const string& middleName,
        const string& phoneNumber, const string& email, const string& login, const string& password);

    // ������� ��� ��������� �������� �����
    string getLastName() const;
    string getFirstName() const;
    string getMiddleName() const;
    string getPhoneNumber() const;
    string getEmail() const;
    string getLogin() const;
    string getPasswordHash() const;
    string getFullName() const;

    // ������� ��� ��������� �������� �����
    void setLastName(const string& lastName);
    void setFirstName(const string& firstName);
    void setMiddleName(const string& middleName);
    void setPhoneNumber(const string& phoneNumber);
    void setEmail(const string& email);
    void setLogin(const string& login);
    void setPassword(const string& password);

    // �������� ���������� ������ ������������
    static bool isValidPhoneNumber(const string& phoneNumber);
    static bool isValidEmail(const string& email);
    static bool isValidPassword(const string& password);
    static bool isValidName(const string& name);

    // ��������������� ��������� ==
    bool operator==(const User& other) const;

private:
    string lastName;
    string firstName;
    string middleName;
    string phoneNumber;
    string email;
    string login;
    string passwordHash;

    // ��������������� ������
    string hashPassword(const string& password) const; // ����������� ������
    bool hasDigits(const string& str) const; // �������� ������� ���� � ������
    void capitalize(string& str) const; // ���������� ������ ����� � �������� ��������
    static bool isCorrectPasswordFormat(const string& password); // �������� ������� ������
};

// ��������������� ��������� == ��� ��������� ������������� �� ������
bool User::operator==(const User& other) const {
    return this->login == other.login;
}

// ����������� ������ User, ���������������� ���� � ���������� ������
User::User(const string& lastName, const string& firstName, const string& middleName,
    const string& phoneNumber, const string& email, const string& login, const string& password)
    : lastName(lastName), firstName(firstName), middleName(middleName), phoneNumber(phoneNumber),
    email(email), login(login), passwordHash(hashPassword(password)) {
    capitalize(this->lastName);
    capitalize(this->firstName);
    capitalize(this->middleName);
}

// ������� ��� ��������� �������� �����
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

// ����� ��� ��������� ������� ����� ������������
string User::getFullName() const {
    return lastName + " " + firstName + " " + middleName;
}

// ������� ��� ��������� �������� �����
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
        cerr << "������������ ������ ������ ��������.\n";
    }
}

void User::setEmail(const string& email) {
    if (isValidEmail(email)) {
        this->email = email;
    }
    else {
        cerr << "������������ ������ e-mail.\n";
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
        cerr << "������������ ������ ������.\n";
    }
}

// �������� ���������� ������ ��������
bool User::isValidPhoneNumber(const string& phoneNumber) {
    // ������ +7-(222)-222-22-22
    regex pattern(R"(^\+\d{1,2}-\(\d{3}\)-\d{3}-\d{2}-\d{2}$)");
    return regex_match(phoneNumber, pattern);
}

// �������� ���������� e-mail
bool User::isValidEmail(const string& email) {
    // ������� �������� �� ������
    regex pattern(R"(^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$)");
    return regex_match(email, pattern);
}

// �������� ���������� ������
bool User::isValidPassword(const string& password) {
    return isCorrectPasswordFormat(password);
}

// �������� ���������� ����� (������� ��� ��������)
bool User::isValidName(const string& name) {
    regex pattern(R"(^[a-zA-Z�-��-���]{2,}$)");
    return regex_match(name, pattern);
}

// ����� ��� ����������� ������
string User::hashPassword(const string& password) const {
    // ������ ����������� ����������� (�� ��� ��������� ����������!)
    // � �������� ��������� ������� ������������ ����� ���������� ��������� �����������
    hash<string> hasher;
    return to_string(hasher(password));
}

// �������� ������� ���� � ������
bool User::hasDigits(const string& str) const {
    return any_of(str.begin(), str.end(), ::isdigit);
}

// ���������� ������ ����� � �������� ��������
void User::capitalize(string& str) const {
    if (!str.empty()) {
        str[0] = toupper(str[0]);
        for (size_t i = 1; i < str.size(); ++i) {
            str[i] = tolower(str[i]);
        }
    }
}

// �������� ������� ������ (������� 8 ��������, ���� ���������, ���� ��������, ���� �����, ���� ����������� ������)
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