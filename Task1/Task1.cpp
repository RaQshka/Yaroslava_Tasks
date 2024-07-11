#define _USE_MATH_DEFINES  // Включение констант математических функций, таких как M_PI, из cmath

#include <iostream>  // Для работы с вводом и выводом
#include <cmath>     // Для математических функций, таких как abs и arg
#include <vector>    // Для работы с векторами

using namespace std;

// Определение структуры для работы с комплексными числами
struct Complex {
    double real;  // Действительная часть
    double imag;  // Мнимая часть

    // Конструкторы
    Complex(double r = 0, double i = 0) : real(r), imag(i) {}

    // Функция для сложения
    Complex AddComplex( Complex& other)  {
        return Complex(real + other.real, imag + other.imag);
    }

    // Функция для вычитания
    Complex SubComplex( Complex& other)  {
        return Complex(real - other.real, imag - other.imag);
    }

    // Функция для умножения
    Complex MulComplex( Complex& other)  {
        return Complex(real * other.real - imag * other.imag, real * other.imag + imag * other.real);
    }

    //  Функция для деления
    Complex DivComplex( Complex& other)  {
        double denominator = other.real * other.real + other.imag * other.imag;
        return Complex((real * other.real + imag * other.imag) / denominator,
            (imag * other.real - real * other.imag) / denominator);
    }

    // Вычисление модуля комплексного числа
    double abs() const {
        return sqrt(real * real + imag * imag);
    }

    // Вычисление аргумента комплексного числа
    double arg() const {
        return atan2(imag, real);
    }

    //функция для ввода
    void Input() {
        cin >> real >> imag;
    }
    //Функция для вывода
    void Print() {
        cout << real;
        if (imag >= 0) {
            cout << " + " << imag << "i";
        }
        else {
            cout << " - " << imag << "i";
        }
    }
};

// Функция для вывода комплексного числа в алгебраической форме
void printComplex(Complex& c) {
    c.Print();
}

// Функция для преобразования комплексного числа из алгебраической формы в тригонометрическую и экспоненциальную формы
void algebraicToTrigAndExp(Complex& c) {
    double r = c.abs();  // Модуль комплексного числа
    double theta = c.arg();  // Аргумент комплексного числа

    // Вывод тригонометрической формы
    cout << "Тригонометрическая форма: " << r << " * (cos(" << theta << ") + i*sin(" << theta << "))\n";
    // Вывод экспоненциальной формы
    cout << "Экспоненциальная форма: " << r << " * exp(i*" << theta << ")\n";
}

// Функция для преобразования комплексного числа из тригонометрической формы в алгебраическую и экспоненциальную формы
void trigToAlgebraicAndExp(double r, double theta) {
    // Преобразование в алгебраическую форму
    Complex c(r * cos(theta), r * sin(theta));
    cout << "Алгебраическая форма: ";
    printComplex(c);  // Вывод алгебраической формы
    cout << "\n";

    // Вывод экспоненциальной формы
    cout << "Экспоненциальная форма: " << r << " * exp(i*" << theta << ")\n";
}

// Функция для преобразования комплексного числа из экспоненциальной формы в алгебраическую и тригонометрическую формы
void expToAlgebraicAndTrig(double r, double theta) {
    // Преобразование в алгебраическую форму
    Complex c(r * cos(theta), r * sin(theta));
    cout << "Алгебраическая форма: ";
    printComplex(c);  // Вывод алгебраической формы
    cout << "\n";

    // Вывод тригонометрической формы
    cout << "Тригонометрическая форма: " << r << " * (cos(" << theta << ") + i*sin(" << theta << "))\n";
}

// Функция для возведения комплексного числа в степень
Complex pow(const Complex& c, int n) {
    double r = pow(c.abs(), n);
    double theta = c.arg() * n;
    return Complex(r * cos(theta), r * sin(theta));
}
// Главная функция
int main() {
    setlocale(0, "");  // Установка локали для корректного вывода сообщений на русском языке
    int choice = 0;

    while (true) {
        // Меню выбора операции
        cout << "Выберите операцию:\n";
        cout << "1. Сложение\n";
        cout << "2. Умножение\n";
        cout << "3. Разность\n";
        cout << "4. Деление\n";
        cout << "5. Алгебраическая -> Тригонометрическая и Экспоненциальная\n";
        cout << "6. Тригонометрическая -> Алгебраическая и Экспоненциальная\n";
        cout << "7. Экспоненциальная -> Алгебраическая и Тригонометрическая\n";
        cout << "8. Возведение в степень\n";
        cout << "9. Корни\n";
        cout << "10. Закрыть\n";
        cout << "Введите свой выбор: ";
        cin >> choice;  // Ввод выбора пользователя

        if (choice == 10) {
            break;  // Завершение программы
        }

        Complex c1, c2;  // Комплексные числа для операций
        double r, theta;  // Радиус и аргумент для тригонометрической и экспоненциальной форм
        int n;  // Степень для операций возведения в степень и нахождения корней

        switch (choice) {
        case 1:
            // Сложение двух комплексных чисел
            cout << "Введите первое комплексное число (real imag): ";
            c1.Input();
            cout << "Введите второе комплексное число (real imag): ";
            c2.Input();
            cout << "Результат: ";
            c1 = c1.AddComplex(c2);
            printComplex(c1);
            cout << "\n";
            break;

        case 2:
            // Умножение двух комплексных чисел
            cout << "Введите первое комплексное число (real imag): ";
            c1.Input();
            cout << "Введите второе комплексное число (real imag): ";
            c2.Input();
            cout << "Результат: ";
            c1 = c1.MulComplex(c2);
            printComplex(c1);
            cout << "\n";
            break;

        case 3:
            // Разность двух комплексных чисел
            cout << "Введите первое комплексное число (real imag): ";
            c1.Input();
            cout << "Введите второе комплексное число (real imag): ";
            c2.Input();
            cout << "Результат: ";
            c1 = c1.SubComplex(c2);
            printComplex(c1);
            cout << "\n";
            break;

        case 4:
            // Деление двух комплексных чисел
            cout << "Введите первое комплексное число (real imag): ";
            c1.Input();
            cout << "Введите второе комплексное число (real imag): ";
            c2.Input();
            cout << "Результат: ";
            c1 = c1.DivComplex(c2);
            printComplex(c1);
            cout << "\n";
            break;

        case 5:
            // Преобразование комплексного числа из алгебраической формы в тригонометрическую и экспоненциальную
            cout << "Введите комплексное число (real imag): ";
            c1.Input();
            algebraicToTrigAndExp(c1);
            break;

        case 6:
            // Преобразование комплексного числа из тригонометрической формы в алгебраическую и экспоненциальную
            cout << "Введите модуль и аргумент r и theta: ";
            cin >> r >> theta;
            trigToAlgebraicAndExp(r, theta);
            break;
        case 7:
            // Преобразование комплексного числа из экспоненциальной формы в алгебраическую и тригонометрическую
            cout << "Введите модуль и аргумент r и theta: ";
            cin >> r >> theta;
            expToAlgebraicAndTrig(r, theta);
            break;

        case 8:
            // Возведение комплексного числа в степень
            cout << "Введите комплексное число (real imag): ";
            c1.Input();
            cout << "Введите степень: ";
            cin >> n;
            cout << "Результат: ";
            c1 = pow(c1, n);
            printComplex(c1);
            cout << "\n";
            break;

        case 9:
        {
            // Нахождение корней комплексного числа
            cout << "Введите комплексное число (real imag): ";
            c1.Input();
            cout << "Введите степень: ";
            cin >> n;

            vector<Complex> roots;
            // Нахождение модуля и аргумента корней
            double magnitude = pow(c1.abs(), 1.0 / n);
            double initialTheta = c1.arg();

            // Вычисление всех корней
            for (int k = 0; k < n; ++k) {
                double theta = (initialTheta + 2 * M_PI * k) / n;
                roots.push_back(Complex(magnitude * cos(theta), magnitude * sin(theta)));
            }

            cout << "Корни:\n";

            // Вывод всех корней
            for (auto root : roots) {
                printComplex(root);
                cout << "\n";
            }
            break;
        }
        default:
            // Обработка неверного выбора
            cout << "Неверный выбор. Попробуйте еще раз.\n";
        }
    }
    return 0;
}
