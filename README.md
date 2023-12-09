# Расширенный узловой метод

Базис расширенного узлового метода составляют:

1. производные переменных состояния;
2. переменные состояния;
3. Переменные типа узловых потенциалов (далее узловые потенциалы);
4. Переменные типа потока для идеальных источников переменной типа потенциала (далее ток идеальных источников ЭДС).

## Добавление нового элемента

Добавить новый элемент необходимо в файле [main] ([http://webdesign.ru.net адрес ссылки - невидимая часть](https://github.com/sadevans/mimapr/blob/main/main.cpp))


Добавление осуществляется по шаблону
```cpp
Element* el = new Element(ElementType::type, start node, end node, value, "name");
```

Для элементов типа `E` можно указать наличие синусоидального источника с помощью флага **true** или **false**. По умолчанию флаг установлен в **false**.

Для элементов типа `Id` можно задать параметры диода: $I_t$ и $m \cdot phit_t$. По умолчанию $I_t = 1e^{-12}$ и $m \cdot phit_t = 0.026$.



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
