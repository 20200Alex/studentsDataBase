#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cassert>
#include "gtest/gtest.h"

struct Student {
    std::string name;
    int age;
    std::string major;
    double gpa;
};

// Функция для добавления студента в базу данных
void addStudent(std::vector<Student>& database) {
    Student student;
    std::cout << "Введите имя студента: ";
    std::cin >> student.name;
    std::cout << "Введите возраст студента: ";
    std::cin >> student.age;
    std::cout << "Введите специальность студента: ";
    std::cin >> student.major;
    std::cout << "Введите средний балл студента: ";
    std::cin >> student.gpa;

    database.push_back(student);
    std::cout << "Студент добавлен в базу данных.\n";
}

// Функция для вывода всех студентов из базы данных
void displayStudents(const std::vector<Student>& database) {
    if (database.empty()) {
        std::cout << "База данных пуста.\n";
        return;
    }
    
    std::cout << "Список студентов:\n";
    for (const Student& student : database) {
        std::cout << "Имя: " << student.name << "\n";
        std::cout << "Возраст: " << student.age << "\n";
        std::cout << "Специальность: " << student.major << "\n";
        std::cout << "Средний балл: " << student.gpa << "\n\n";
    }
}

// Функция для сортировки студентов по имени (по возрастанию)
void sortStudentsByName(std::vector<Student>& database) {
    std::sort(database.begin(), database.end(), 
        [](const Student& a, const Student& b) {
            return a.name < b.name;
        });
}

// Функция для сортировки студентов по среднему баллу (по убыванию)
void sortStudentsByGPA(std::vector<Student>& database) {
    std::sort(database.begin(), database.end(), 
        [](const Student& a, const Student& b) {
            return a.gpa > b.gpa;
        });
}

// Функция для сортировки студентов по среднему баллу (по возрастанию)
void sortStudentsByGPAAsc(std::vector<Student>& database) {
    std::sort(database.begin(), database.end(), 
        [](const Student& a, const Student& b) {
            return a.gpa < b.gpa;
        });
}

int main(int argc, char **argv) {
    // Если переданы аргументы командной строки, запускаем тесты
    /*if (argc > 1 && std::string(argv[1]) == "--test") {
        ::testing::InitGoogleTest(&argc, argv);
        return RUN_ALL_TESTS();
    }
    
    // Иначе запускаем обычное меню программы*/
    std::vector<Student> database;

    int choice;
    do {
        std::cout << "\nМеню:\n";
        std::cout << "1. Добавить студента\n";
        std::cout << "2. Вывести список студентов\n";
        std::cout << "3. Сортировать студентов по имени\n";
        std::cout << "4. Сортировать студентов по среднему баллу (по убыванию)\n";
        std::cout << "5. Сортировать студентов по среднему баллу (по возрастанию)\n";
        std::cout << "6. Запустить тесты\n";
        std::cout << "0. Выход\n";
        std::cout << "Выберите действие: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                addStudent(database);
                break;
            case 2:
                displayStudents(database);
                break;
            case 3:
                if (database.empty()) {
                    std::cout << "База данных пуста. Нечего сортировать.\n";
                } else {
                    sortStudentsByName(database);
                    std::cout << "Студенты отсортированы по имени.\n";
                }
                break;
            case 4:
                if (database.empty()) {
                    std::cout << "База данных пуста. Нечего сортировать.\n";
                } else {
                    sortStudentsByGPA(database);
                    std::cout << "Студенты отсортированы по среднему баллу (по убыванию).\n";
                }
                break;
            case 5:
                if (database.empty()) {
                    std::cout << "База данных пуста. Нечего сортировать.\n";
                } else {
                    sortStudentsByGPAAsc(database);
                    std::cout << "Студенты отсортированы по среднему баллу (по возрастанию).\n";
                }
                break;
            case 6:
                runTests();
                break;
            case 0:
                std::cout << "Выход из программы.\n";
                break;
            default:
                std::cout << "Неверный выбор. Попробуйте снова.\n";
        }
    } while (choice != 0);

    return 0;
}
