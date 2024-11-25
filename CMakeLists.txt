cmake_minimum_required(VERSION 3.10)

project(UVM)

include_directories(${PROJECT_SOURCE_DIR}/include)

add_executable(UVM 
                ./src/main.cpp
                ./src/vmprocessor.cpp
                ./src/assembler.cpp
                ./src/interpreter.cpp
)

# Создаем кастомную цель для запуска программы с аргументами
add_custom_target(run ALL
    COMMAND UVM "../data/inputs/textfile.txt" "../data/tmp/binfile.bin" "../data/logs/logfile.yaml" "../data/outputs/resultfile.yaml" "0-8"
    DEPENDS UVM
    COMMENT "Running MyProject with arguments"
)

# Подключаем GoogleTest
# add_subdirectory(googletest)  # если бы у меня не были скомпилированы исходники gtest

include_directories(${PROJECT_SOURCE_DIR}/tests)

enable_testing()

set(CTEST_OUTPUT_ON_FAILURE "TRUE")

add_executable(tests
    tests/main.cpp
    ./src/vmprocessor.cpp
    ./src/assembler.cpp
    ./src/interpreter.cpp
)

# Линкуем тесты с GoogleTest и GoogleMock
target_link_libraries(tests gtest gtest_main)

# Добавляем цель для запуска тестов (обязательно)
add_test(NAME MyTests COMMAND tests)

# Создаем кастомную цель для запуска тестов
add_custom_target(run_tests ALL
    COMMAND ${CMAKE_CTEST_COMMAND} --output-on-failure
    COMMAND ctest -V
    DEPENDS tests  # Указываем, что тесты должны быть собраны перед их запуском
    COMMENT "Running tests..."
)

# cd build
# cmake ..
# make
# ./UVM для запуска программы
# make run для запуска программы с аргументами, указанными в add_cutom_target(run ...)
# make run_tests для запуска тестов
# 
# если добавить слово ALL в add_custom_target(run ALL ...), 
# одной командой make будут собираться проект и запускаться программа с аргументами, указанными в add_cutom_target(run ...)
# 
# если добавить слово ALL в add_custom_target(run_tests ALL ...), 
# одной командой make будут собираться проект и запускаться тесты
