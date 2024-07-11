#include <iostream>     // Для работы с вводом и выводом
#include <Windows.h>   
#include "UserManager.hpp"  // Включение заголовочного файла UserManager

using namespace std;

int main() {
    setlocale(0, "");  // Установка локали для корректного вывода русских символов

    // Установка кодовой страницы для корректного отображения русских символов в консоли
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    UserManager userManager("users.txt");  // Создание экземпляра UserManager с именем файла для хранения пользователей

    char choice;  // Переменная для хранения выбора пользователя

    do {
        // Вывод меню выбора действий
        cout << "Выберите одну из альтернатив:\n"
            << "a. Посмотреть список пользователей\n"
            << "b. Добавить пользователя\n"
            << "c. Удалить пользователя\n"
            << "d. Изменить пользователя\n"
            << "e. Сохранить изменения в файл\n"
            << "f. Отправить сообщение на e-mail пользователя\n"
            << "g. Отсортировать по выбранному полю\n"
            << "h. Выход\n";

        cin >> choice; 

        cin.ignore();  // Очистка буфера ввода

        // Обработка выбора пользователя
        switch (choice) {
        case 'a':
            userManager.showUserList();  // Показать список пользователей
            break;
        case 'b':
            userManager.addUser();  // Добавить пользователя
            break;
        case 'c':
            userManager.deleteUser();  // Удалить пользователя
            break;
        case 'd':
            userManager.editUser();  // Изменить пользователя
            break;
        case 'e':
            userManager.saveChangesToFile();  // Сохранить изменения в файл
            break;
        case 'f':
            userManager.sendEmailToUser();  // Отправить сообщение на e-mail пользователя
            break;
        case 'g':
            userManager.sortUsers();  // Отсортировать пользователей по выбранному полю
            break;
        case 'h':
            cout << "До свидания!\n";  // Завершение работы программы
            break;
        default:
            cout << "Неверный выбор. Попробуйте снова.\n";  // Обработка некорректного выбора
            break;
        }
    } while (choice != 'h');  // Цикл продолжается, пока пользователь не выберет выход ('h')

    return 0; 
}
