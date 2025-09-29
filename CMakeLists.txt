cmake_minimum_required(VERSION 3.10)
project(StudentsDatabase)

set(CMAKE_CXX_STANDARD 11)

# Включить FetchContent для загрузки GoogleTest
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.12.1
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
target_link_libraries(students_db_test gtest gtest_main)

enable_testing()
add_test(NAME StudentsDatabaseTests COMMAND students_db_test)
