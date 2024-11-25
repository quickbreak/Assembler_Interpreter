<h1 align="center">
  Ассемблер и интерпретатор для учебной виртуальной машины 
</h1>
<h2 align="center">Постановка задачи</h2>

Разработать ассемблер и интерпретатор для учебной виртуальной машины (УВМ). Система команд УВМ представлена далее.  

Для ассемблера необходимо разработать читаемое представление команд УВМ. Ассемблер принимает на вход файл с текстом исходной программы, путь к которой задается из командной строки. Результатом работы ассемблера является бинарный файл в виде последовательности байт, путь к которому задается из командной строки. Дополнительный ключ командной строки задает путь к файлу 46 логу, в котором хранятся ассемблированные инструкции в духе списков “ключ=значение”, как в приведенных далее тестах. 

Интерпретатор принимает на вход бинарный файл выполняет команды УВМ и сохраняет в файле-результате значения из диапазона памяти УВМ. Диапазон также указывается из командной строки. 

Форматом для файла-лога и файла-результата является yaml.  

Необходимо реализовать приведенные тесты для всех команд, а также написать и отладить тестовую программу.

```
Загрузка константы 
A Биты 0—5
B Биты 6—22 
C Биты 23—25 
Размер команды: 6 байт. Операнд: поле B. Результат: регистр по адресу, которым является поле C. 
Тест (A=6, B=464, C=2): 
0x06, 0x74, 0x00, 0x01, 0x00, 0x00 
```
```
Чтение значения из памяти 
A Биты 0—5
B Биты 6—8 
C Биты 9—27
Размер команды: 6 байт. Операнд: значение в памяти по адресу, которым является поле C. Результат: регистр по адресу, которым является поле B.  
Тест (A=56, B=5, C=1014): 
0x78, 0xED, 0x07, 0x00, 0x00, 0x00
```
```
Запись значения в память 
A Биты 0—5
B Биты 6—8 
C Биты 9—11
Размер команды: 6 байт. Операнд: регистр по адресу, которым является поле C. Результат: значение в памяти по адресу, которым является регистр по адресу, которым является поле B. 
Тест (A=51, B=5, C=0): 
0x73, 0x01, 0x00, 0x00, 0x00, 0x00  
```
```
Бинарная операция: "<" 
A Биты 0—5
B Биты 6—8 
C Биты 9—27
Размер команды: 6 байт. Первый операнд: регистр по адресу, которым является поле B. Второй операнд: значение в памяти по адресу, которым является поле C. Результат: регистр по адресу, которым является поле B.  
Тест (A=17, B=3, C=762):
0xD1, 0xF4, 0x05, 0x00, 0x00, 0x00 
```
```
Тестовая программа 
Выполнить поэлементно операцию "<" над двумя векторами длины 8. Результат записать в новый вектор. 
```
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
