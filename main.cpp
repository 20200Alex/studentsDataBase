#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <gtest/gtest.h>

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
    std::cout << "Список студентов:\n";
    for (const Student& student : database) {
        std::cout << "Имя: " << student.name << "\n";
        std::cout << "Возраст: " << student.age << "\n";
        std::cout << "Специальность: " << student.major << "\n";
        std::cout << "Средний балл: " << student.gpa << "\n\n";
    }
}

// Функции сравнения для сортировки
bool compareByName(const Student& a, const Student& b) {
    return a.name < b.name;
}

bool compareByGPA(const Student& a, const Student& b) {
    return a.gpa > b.gpa; // по убыванию (высокий GPA первый)
}

bool compareByGPAAscending(const Student& a, const Student& b) {
    return a.gpa < b.gpa; // по возрастанию
}

// Функция для сортировки студентов
void sortStudents(std::vector<Student>& database, int sortBy) {
    switch (sortBy) {
        case 1: // по имени
            std::sort(database.begin(), database.end(), compareByName);
            std::cout << "Студенты отсортированы по имени.\n";
            break;
        case 2: // по GPA (по убыванию)
            std::sort(database.begin(), database.end(), compareByGPA);
            std::cout << "Студенты отсортированы по среднему баллу (по убыванию).\n";
            break;
        case 3: // по GPA (по возрастанию)
            std::sort(database.begin(), database.end(), compareByGPAAscending);
            std::cout << "Студенты отсортированы по среднему баллу (по возрастанию).\n";
            break;
        default:
            std::cout << "Неверный выбор сортировки.\n";
    }
}

// ==================== GOOGLE TESTS ====================

TEST(StudentDatabaseTest, SortByName) {
    std::vector<Student> database = {
        {"Ivan", 20, "CS", 3.5},
        {"Anna", 21, "Math", 3.8},
        {"Boris", 22, "Physics", 3.2}
    };
    
    sortStudents(database, 1);
    
    EXPECT_EQ(database[0].name, "Anna");
    EXPECT_EQ(database[1].name, "Boris");
    EXPECT_EQ(database[2].name, "Ivan");
    EXPECT_EQ(database[0].age, 21);
    EXPECT_EQ(database[1].age, 22);
    EXPECT_EQ(database[2].age, 20);
}

TEST(StudentDatabaseTest, SortByGPADescending) {
    std::vector<Student> database = {
        {"Ivan", 20, "CS", 3.5},
        {"Anna", 21, "Math", 3.8},
        {"Boris", 22, "Physics", 3.2},
        {"Maria", 19, "Biology", 3.8} // Тест с одинаковым GPA
    };
    
    sortStudents(database, 2);
    
    EXPECT_DOUBLE_EQ(database[0].gpa, 3.8);
    EXPECT_DOUBLE_EQ(database[1].gpa, 3.8);
    EXPECT_DOUBLE_EQ(database[2].gpa, 3.5);
    EXPECT_DOUBLE_EQ(database[3].gpa, 3.2);
}

TEST(StudentDatabaseTest, SortByGPAAscending) {
    std::vector<Student> database = {
        {"Ivan", 20, "CS", 3.5},
        {"Anna", 21, "Math", 3.8},
        {"Boris", 22, "Physics", 3.2}
    };
    
    sortStudents(database, 3);
    
    EXPECT_DOUBLE_EQ(database[0].gpa, 3.2);
    EXPECT_DOUBLE_EQ(database[1].gpa, 3.5);
    EXPECT_DOUBLE_EQ(database[2].gpa, 3.8);
    EXPECT_EQ(database[0].name, "Boris");
    EXPECT_EQ(database[1].name, "Ivan");
    EXPECT_EQ(database[2].name, "Anna");
}

TEST(CompareFunctionsTest, CompareByName) {
    Student a = {"Anna", 20, "CS", 3.5};
    Student b = {"Boris", 21, "Math", 3.8};
    Student c = {"Anna", 22, "Physics", 4.0}; // Тест с одинаковыми именами
    
    EXPECT_TRUE(compareByName(a, b));   // Anna < Boris
    EXPECT_FALSE(compareByName(b, a));  // Boris > Anna
    EXPECT_FALSE(compareByName(a, a));  // Anna == Anna
    EXPECT_FALSE(compareByName(a, c));  // Anna == Anna (другой студент)
}

TEST(CompareFunctionsTest, CompareByGPA) {
    Student a = {"Anna", 20, "CS", 3.5};
    Student b = {"Boris", 21, "Math", 3.8};
    Student c = {"Maria", 22, "Physics", 3.5}; // Тест с одинаковым GPA
    
    EXPECT_TRUE(compareByGPA(b, a));   // 3.8 > 3.5
    EXPECT_FALSE(compareByGPA(a, b));  // 3.5 < 3.8
    EXPECT_FALSE(compareByGPA(a, a));  // 3.5 == 3.5
    EXPECT_FALSE(compareByGPA(a, c));  // 3.5 == 3.5
}

TEST(StudentDatabaseTest, EmptyDatabase) {
    std::vector<Student> emptyDatabase;
    
    // Не должно вызывать ошибок
    EXPECT_NO_THROW(sortStudents(emptyDatabase, 1));
    EXPECT_NO_THROW(sortStudents(emptyDatabase, 2));
    EXPECT_NO_THROW(sortStudents(emptyDatabase, 3));
    EXPECT_TRUE(emptyDatabase.empty());
}

TEST(StudentDatabaseTest, SingleStudent) {
    std::vector<Student> database = {{"Anna", 20, "CS", 3.5}};
    
    sortStudents(database, 1);
    EXPECT_EQ(database.size(), 1);
    EXPECT_EQ(database[0].name, "Anna");
    
    sortStudents(database, 2);
    EXPECT_EQ(database[0].name, "Anna");
    
    sortStudents(database, 3);
    EXPECT_EQ(database[0].name, "Anna");
}

TEST(StudentDatabaseTest, CaseSensitiveSort) {
    std::vector<Student> database = {
        {"ivan", 20, "CS", 3.5},
        {"Anna", 21, "Math", 3.8},
        {"boris", 22, "Physics", 3.2}
    };
    
    sortStudents(database, 1);
    
    // Проверяем, что сортировка учитывает регистр (A < b < i)
    EXPECT_EQ(database[0].name, "Anna");
    EXPECT_EQ(database[1].name, "boris");
    EXPECT_EQ(database[2].name, "ivan");
}

TEST(StudentDatabaseTest, InvalidSortOption) {
    std::vector<Student> database = {
        {"Ivan", 20, "CS", 3.5},
        {"Anna", 21, "Math", 3.8}
    };
    
    // Сохраняем исходный порядок
    std::vector<Student> original = database;
    
    // Неверная опция сортировки
    testing::internal::CaptureStdout();
    sortStudents(database, 999);
    std::string output = testing::internal::GetCapturedStdout();
    
    // База данных не должна измениться
    EXPECT_EQ(database.size(), original.size());
    EXPECT_EQ(database[0].name, original[0].name);
    EXPECT_EQ(database[1].name, original[1].name);
}

// ==================== MAIN FUNCTION ====================

int main(int argc, char **argv) {
    // Если передан аргумент --test, запускаем тесты
    if (argc > 1 && std::string(argv[1]) == "--test") {
        std::cout << "Запуск Google Tests...\n";
        testing::InitGoogleTest(&argc, argv);
        return RUN_ALL_TESTS();
    }
    
    // Обычный режим работы программы
    std::vector<Student> database;

    int choice;
    do {
        std::cout << "Меню:\n";
        std::cout << "1. Добавить студента\n";
        std::cout << "2. Вывести список студентов\n";
        std::cout << "3. Отсортировать студентов\n";
        std::cout << "4. Запустить тесты\n";
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
                if (!database.empty()) {
                    std::cout << "Сортировка по:\n";
                    std::cout << "1. Имени\n";
                    std::cout << "2. Среднему баллу (по убыванию)\n";
                    std::cout << "3. Среднему баллу (по возрастанию)\n";
                    std::cout << "Выберите тип сортировки: ";
                    int sortChoice;
                    std::cin >> sortChoice;
                    sortStudents(database, sortChoice);
                } else {
                    std::cout << "База данных пуста. Нечего сортировать.\n";
                }
                break;
            case 4:
                std::cout << "Для запуска тестов перезапустите программу с аргументом --test\n";
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
