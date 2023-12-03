# Расширенный узловой метод

Базис расширенного узлового метода составляют:

1. производные переменных состояния;
2. переменные состояния;
3. Переменные типа узловых потенциалов (далее узловые потенциалы);
4. Переменные типа потока для идеальных источников переменной типа потенциала (далее ток идеальных источников ЭДС).

## Добавление нового элемента

Сначала необходимо ввести тип элемента: (E, C, R, L, I)
```cpp
Enter elements one by one with their characteristics.
Enter 'exit' to finish input.
Enter element type (E, C, R, L, I): E
```

Затем введите начальный узел элемента (из этого узла будет идти стрелка направления)
```cpp
Enter start node: 1
```

После этого введите конечный узел элемента (в него будет направлена стрелка)"
```cpp
Enter end node: 2
```

Далее введите значение
```cpp
Enter value: 10
```

После этого введите имя элемента
```cpp
Enter element name: E1
```

## Пример
```cpp
Enter elements one by one with their characteristics.
Enter 'exit' to finish input.
Enter element type (E, C, R, L, I): E
Enter start node: 1
Enter end node: 2
Enter value: 10
Enter element name: E1
Enter element type (E, C, R, L, I): R
Enter start node: 2
Enter end node: 3
Enter value: 12
Enter element name: R1
Enter element type (E, C, R, L, I): exit
```
