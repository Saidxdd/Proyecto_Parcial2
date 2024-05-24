# Documentacion T1P1
### Hecho por Said de Jesus Vidal Ramirez 

## Interfaz
```c++

#ifndef INTCELL_H
#define INTCELL_H

class IntCell {
public:
    IntCell() = default;
    IntCell(int newValue = 0);
    IntCell(const IntCell &rhs);
    IntCell(IntCell &&rhs) noexcept;
    ~IntCell() = default;

    IntCell &operator=(const IntCell &rhs);
    IntCell &operator=(IntCell &&rhs) noexcept;
    IntCell &operator=(int rhs);
    IntCell &operator+(const IntCell &rhs);
    IntCell &operator+(int rhs);
    IntCell &operator-(const IntCell &rhs);
    IntCell &operator-(int rhs);

    int getValue() const;
    void setValue(int newValue);

private:
    int storedValue;
    int storedValue2;
    int storedValue3;
};

#endif  // INTCELL_H

```
El codigo proporcionado cuenta de dos maneras, una es un .h y otra ya es un.cpp esto sirve
bien especialmente para mantener un orden en el codigo y se mas facil de manejar,
en primer lugar la interfaz como su propio nombre lo dice es donde el usuario o el programador va a poder 
interactuar con el programa en cuestion por medio de funciones, o datos que el proporcione:

```c++
IntCell() = default;
    IntCell(int newValue = 0);
    IntCell(const IntCell &rhs);
    IntCell(IntCell &&rhs) noexcept;
    ~IntCell() = default;
```
La primera parte de la interfaz declara varios contructores que nos serviran en la parte de la implementacion el primer contructor declara un entere con un valor por defecto que proporcionara
el mismo compilador, el segundo constructor sirve para darle un valor de 0 cuando este se incialice, para despues
declarar un constructor que hace una copia de del entero, despues hace un contructor que sirve para mover el dato a otro espacio de memoria
para por ultimo hacer un contructor que sirve para liberar el espacio de memoria de lo que hizo el contructor

```c++
IntCell &operator=(const IntCell &rhs);
    IntCell &operator=(IntCell &&rhs) noexcept;
    IntCell &operator=(int rhs);
    IntCell &operator+(const IntCell &rhs);
    IntCell &operator+(int rhs);
    IntCell &operator-(const IntCell &rhs);
    IntCell &operator-(int rhs);
```
Primero lo que hace es sobrecargar el operador para poder copiarlo, para despues volver a sobrecargarlo y mover a otro espacio de memoria, para despues sobrecargarlo y darle un valor entero, y luego sobrecargarlo
y sumar con un intcell, para despues volver a hacer lo mismo pero ahora sumarlo con un entero, despues lo sobrecarga y ahora resta un intcell , para volver a hacer lo mismo pero con un entero

```c++
int getValue() const;
    void setValue(int newValue);
```
Estos dos sirven muy bien, getValue sirve para conseguir los datos almacenados en el intcell, el setvalue sirve para lo contrario establecer un dato.

```c++
private:
    int storedValue;
    int storedValue2;
    int storedValue3;
```
Aqui es donde se declaran todos los datos, y donde se alamaceran los datos anteriormente mencionados

## Implementacion
```c++
#include "IntCell.h"

IntCell::IntCell(int newValue) : storedValue(newValue) {}

IntCell::IntCell(const IntCell &rhs) : storedValue(rhs.storedValue) {}

IntCell::IntCell(IntCell &&rhs) noexcept : storedValue(rhs.storedValue) {}

IntCell &IntCell::operator=(const IntCell &rhs) {
    if (this != &rhs) {
        storedValue = rhs.storedValue;
    }
    return *this;
}

IntCell &IntCell::operator=(IntCell &&rhs) noexcept {
    if (this != &rhs) {
        storedValue = rhs.storedValue;
        rhs.storedValue = 0;
    }
    return *this;
}

IntCell &IntCell::operator=(int rhs) {
    storedValue = rhs;
    return *this;
}

IntCell &IntCell::operator+(const IntCell &rhs) {
    storedValue = storedValue + rhs.storedValue;
    return *this;
}

IntCell &IntCell::operator+(int rhs) {
    storedValue = storedValue + rhs;
    return *this;
}

IntCell &IntCell::operator-(const IntCell &rhs) {
    storedValue = storedValue - rhs.storedValue;
    return *this;
}

IntCell &IntCell::operator-(int rhs) {
    storedValue = storedValue - rhs;
    return *this;
}

int IntCell::getValue() const {
    return storedValue;
}

void IntCell::setValue(int newValue) {
    storedValue = newValue;
}

```
La implementacio es una parte muy importante de este codigo ya que es el hara que los contructores funcionen ya que definen lo que hacen y como estos interactuan con los datos

```c++
IntCell::IntCell(int newValue) : storedValue(newValue) {}
```
Este constructor inicaliza lo que es el valor entero, ademas de reservar un espacio de memoria
```c++
IntCell::IntCell(const IntCell &rhs) : storedValue(rhs.storedValue) {}
```

Este constructor lo que hace es crear una copia de este este intcell, lo que hace en general es preparar la maquina para guardarla en un espacio de memoria libre 

```c++
IntCell::IntCell(IntCell &&rhs) noexcept : storedValue(rhs.storedValue) {}
```
Este es el contructor de movimiento que al igual que el de copia, reserva un espacio de memoria para que el stored value se mueva de manera mas eficiente, segura y rapida y no deje libre algun espacio de memoria
```C++
IntCell &IntCell::operator=(const IntCell &rhs) {
    if (this != &rhs) {
        storedValue = rhs.storedValue;
    }
    return *this;
}
```
Esta parte del contructor ya es la parte de los operadores matematicos, una forma de ver el como funcionan 
los compiladores por dentro, su funcion es facil, asigna un valor dado al stored value, sin antes haber reservado un espacio ya para su uso, esto nos servira mas adelante para poder asignar un entero a un espacio
```C++
    IntCell &IntCell::operator=(IntCell &&rhs) noexcept {
    if (this != &rhs) {
        storedValue = rhs.storedValue;
        rhs.storedValue = 0;
    }
    return *this;
}
```
Este constructor tambien es de asiganacion pero con la diferencia de que este toma el dato de otro dato almacenado en el intcell y ocupa su espacio de memoria
```c++
IntCell &IntCell::operator=(int rhs) {
    storedValue = rhs;
    return *this;
}
```

Este es el constructor que sirve para asignar un valor por pretermidado entero, en caso de que el usuario no haya ingreasado nada, al final ya tiene este espacio reservado en caso de que le den o no el valor

```C++
IntCell &IntCell::operator+(const IntCell &rhs) {
    storedValue = storedValue + rhs.storedValue;
    return *this;
}
```
Este constructor permite la sobrecarga del operador de la suma, lo que permite sumar el valor de un objeto con el de otro objeto en el intcell
```C++
IntCell &IntCell::operator+(int rhs) {
    storedValue = storedValue + rhs;
    return *this;
}
```
Lo mismo que el anterior solamente que ahora lo hace con los valores enteros actuales del intecell, al sobrecargar la suma esta ya tiene preparada la localizacion de los datos asi como donde se alojaran 
antes de terminar la suma para mantener un ritmo eficiente
```C++
IntCell &IntCell::operator-(const IntCell &rhs) {
    storedValue = storedValue - rhs.storedValue;
    return *this;
}
```
Este constructor hace lo mismo que los anteriores, con la diferencia de que ahora va a sobrecargar el signo de resta, lo que hara que se puedan restar los dos objetos del intcell

```C++
IntCell &IntCell::operator-(int rhs) {
    storedValue = storedValue - rhs;
    return *this;
}
```
Este lo mismo, sobrecarga el operador de resta para poder restar dos valores enteros del intcell

```C++
int IntCell::getValue() const {
    return storedValue;
}
```
Este es el que permite devolver un dato almacedado, simplemente devolviendo el valor de la variable storedvalue

```c++
void IntCell::setValue(int newValue) {
    storedValue = newValue;
}
```
Este al contrario lo que hace es asignarle un valor storedvalue por medio del newvalue