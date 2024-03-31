#include <iostream>
#include <string>
#include <fstream>
#include <cctype>
// Программа создания ведомости выплат.

std::string inputDate()
{
    // Процедура ввода даты и проверка ввода на корректность
    int day, month, year;
    std::string result = "NULL";
    std::cout << "Enter a date in the format dd.mm.yyyy: ";
    while (result == "NULL")
    {
        std::cin >> day;           // Считываем день
        if (std::cin.get() != '.') // Проверяем наличие '.' в качестве разделителя
        {
            std::cerr << "Expected '.'. Repeat input: ";
            std::cin.clear();
            std::cin.ignore();
        }
        std::cin >> month;         // Считываем месяц
        if (std::cin.get() != '.') // Проверяем наличие '.' в качестве разделителя
        {
            std::cerr << "Expected '.'. Repeat input: ";
            std::cin.clear();
            std::cin.ignore();
        }
        std::cin >> year;          // Считываем год
        // Проверяем корректность введённой даты, включая проверку на високосный год
        if (year > 0)
        {
            if ((month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12) && day > 0 && day < 32)
                result = std::to_string(day) + '.' + std::to_string(month) + '.' + std::to_string(year);
            else if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 0 && day < 31)
                result = std::to_string(day) + '.' + std::to_string(month) + '.' + std::to_string(year);
            else if (month == 2)
                if (year % 400 == 0 || (year % 100 != 0 && year % 4 == 0) && day > 0 && day < 30)
                    result = std::to_string(day) + '.' + std::to_string(month) + '.' + std::to_string(year);
                else if (day > 0 && day < 29)
                    result = std::to_string(day) + '.' + std::to_string(month) + '.' + std::to_string(year);
                else
                {
                    std::cerr << "Incorrect date. Repeat input: ";
                    std::cin.clear();
                    std::cin.ignore();
                }
            else
            {
                std::cerr << "Incorrect date. Repeat input: ";
                std::cin.clear();
                std::cin.ignore();
            }
        }
        else
        {
            std::cerr << "Incorrect date. Repeat input: ";
            std::cin.clear();
            std::cin.ignore();
        }
    }
    return result;
}

std::string inputString(std::string title)
{   // Эта процедура позволяет вводить имя и фамилию или qiut для выхода из программы
    std::string inStr;
    bool fail;
    std::cout << "Enter a " << title << " or 'quit' for exit: ";
    do
    {
        fail = false;
        std::cin >> inStr;
        for (int i = 0;!fail && i < inStr.length();i++)
        {
            if (!isalpha(inStr[i]))
            {
                fail = true;
                std::cout << "Input incorrect " << title << ". Repeat input: ";
            }
        }
    } while (fail);
    return inStr;
}

float inputPayment()
{   // Вводим сумму, можно с точкой
    std::string inStr;
    bool fail;
    std::cout << "Enter a payment: ";
    do
    {
        fail = false;
        std::cin >> inStr;
        for (int i = 0;!fail && i < inStr.length(); i++)
        {
            if (!isdigit(inStr[i]) && inStr[i] != '.')
            {
                fail = true;
                std::cout << "Input incorrect. Repeat input: ";
            }
        }
    } while (fail);
    return std::stof(inStr);
}

int main()
{   // Главная программа, которая записывает введённые данные в файл.
    std::string firstName, secondName, payDate;
    float salary;
    std::ofstream out;
    bool finish = false;
    out.open("Statement.txt",std::ios_base::app);
    if (out.is_open())
    {
        while (!finish)
        {
            firstName = inputString("first name");
            if (firstName != "quit")
            {
                secondName = inputString("second name");
                if (secondName != "quit")
                {
                    salary = inputPayment();
                    payDate = inputDate();
                    out << firstName << ' ' << secondName << ' ' << salary << ' ' << payDate << '\n';
                }
                else
                    finish = true;
            }
            else
                finish = true;
        }
    }
    out.close();
    std::cout << "Program is finihed.\n";
}