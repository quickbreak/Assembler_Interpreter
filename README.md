<h1 align="center">
  Ассемблер и интерпретатор для учебной виртуальной машины 
</h1>

<h2 align="center">Пример работы программы</h2>

Входной файл для ассемблера:
```
LOAD_CONSTANT 1 0
LOAD_CONSTANT 2 1
LOAD_CONSTANT 600 2
LOAD_CONSTANT 601 3
LOAD_CONSTANT 3 4
LOAD_CONSTANT 602 5
LOAD_CONSTANT 4 6
LOAD_CONSTANT 5 7
WRITE 0 0
WRITE 1 1
WRITE 2 2
WRITE 3 3
WRITE 4 4
WRITE 5 5
WRITE 6 6
WRITE 7 7
LOAD_CONSTANT 500 0
LOAD_CONSTANT 501 1
LOAD_CONSTANT 10 2
LOAD_CONSTANT 11 3
LOAD_CONSTANT 502 4
LOAD_CONSTANT 12 5
LOAD_CONSTANT 503 6
LOAD_CONSTANT 504 7
LESS 0 0
LESS 1 1
LESS 2 2
LESS 3 3
LESS 4 4
LESS 5 5
LESS 6 6
LESS 7 7
WRITE 0 0
WRITE 1 1
WRITE 2 2
WRITE 3 3
WRITE 4 4
WRITE 5 5
WRITE 6 6
WRITE 7 7
```
Выходной файл интерпретатора (результат поэлементного сравнения двух массивов длины 8):
```
0 0 1 1 0 1 0 0 
```
# Инструкция по скачиванию и запуску проекта на вашей машине (Linux)
Откройте терминал или командную строку и выполните следующие команды...  
## 1. Клонирование репозитория
Скачать репозиторий (с подмодулями):
```
git clone --recurse-submodules https://github.com/quickbreak/Assembler_Interpreter.git
```
Перейти в нужный каталог:
```
cd Assembler_Interpreter
```
## 2. Запуск проекта
Скомпилировать основной код:
```
g++ vmprocessor.cpp assembler.cpp interpreter.cpp main.cpp -o main
```
Выполнить команды из ./data/inputs/textfile.txt:
```
./main "./textfile.txt" "./binfile.bin" "./logfile.yaml" "./resultfile.yaml" "0-8"
```
## 3. Запуск тестов
Скомпилировать тесты:
```
g++ ../src/vmprocessor.cpp ../src/assembler.cpp ../src/interpreter.cpp -std=c++17 -I../googletest/googletest/include -I../googletest/googletest ./main.cpp -o test ../googletest/build/lib/libgtest.a ../googletest/build/lib/libgtest_main.a -pthread
```
Запустить тесты:
```
./test
```
