cmake_minimum_required(VERSION 3.10)
project(StudentsDatabase)

set(CMAKE_CXX_STANDARD 11)

# Включить FetchContent для загрузки GoogleTest
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9fdabf8a6d4c6ad7e9b4dac.zip
)

# Для Windows: предотвратить переопределение макросов min/max
if (WIN32)
  add_definitions(-DNOMINMAX)
endif()

# Включить GoogleTest
FetchContent_MakeAvailable(googletest)

# Основная программа
add_executable(students_db main.cpp)

# Тестовая программа
add_executable(students_db_test main.cpp)
target_link_libraries(students_db_test gtest_main)

# Разрешить запуск тестов через CTest
enable_testing()
add_test(NAME StudentsDatabaseTests COMMAND students_db_test)
