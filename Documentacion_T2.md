# Documentacion T2P1

## Interfaz

```c++
#ifndef SLLLIST_H
#define SLLLIST_H

#include <iostream>
#include <utility>

template<typename Object>
class SLList {
public:
    struct Node {
        Object data;
        Node *next;

        Node(const Object &d = Object{}, Node *n = nullptr);

        Node(Object &&d, Node *n = nullptr);
    };

public:
    class iterator {
    public:
        iterator();

        Object &operator*();

        iterator &operator++();

        const iterator operator++(int);

        bool operator==(const iterator &rhs) const;

        bool operator!=(const iterator &rhs) const;

    private:
        Node *current;

        iterator(Node *p);

        friend class SLList<Object>;
    };

public:
    SLList();

    SLList(std::initializer_list <Object> init_list);

    ~SLList();

    iterator begin();

    iterator end();

    int size() const;

    bool empty() const;

    void clear();

    Object &front();

    void push_front(const Object &x);

    void push_front(Object &&x);

    void pop_front();

    iterator insert(iterator itr, const Object &x);

    iterator insert(iterator itr, Object &&x);

    iterator erase(iterator itr);

    void print();

private:
    Node *head;
    Node *tail;
    int theSize;

    void init();
};

#include "SLList.cpp"

#endif
```
Este codigo al igual que el anterior dado, se compone de dos partes, una como interfaz
y la otra donde se ejecutaran todas las funciones 
```c++
template<typename Object>
class SLList {
public:
    struct Node {
        Object data;
        Node *next;

        Node(const Object &d = Object{}, Node *n = nullptr);

        Node(Object &&d, Node *n = nullptr);
    };
```
Como primera parte se introduce lo que es el template que sirve para que todos los datos que
se introduzcan en la clase se vuelvan de tipo object por predeterminado lo que permite tener mayor orden
en como menejamos los datos, en la siguiente parte en palabras simples es una estructura llamada
nodo que permite almacenar datos en la lista medienta data para que despues next apunte al siguiente espacio
de la lista, ademas de que estan dos variables llamadas d y n que son basicamente data y next que sirven para lo anteriormente
explicado, estas tienes un valor predeterminado de tipo object.
```c++
public:
    class iterator {
    public:
        iterator();

        Object &operator*();

        iterator &operator++();

        const iterator operator++(int);

        bool operator==(const iterator &rhs) const;

        bool operator!=(const iterator &rhs) const;

    private:
        Node *current;

        iterator(Node *p);

        friend class SLList<Object>;
    };
```
Primero hace publica la funcion de iterador para que esta se pueda acceder
desde cualquier medio, primero hace hace un constructor llamado iterator para
despues sobrecargar operator adeams de dejar una referencia del objeto,
para despues volver a sobrecargar el operador con el prefijo ++, para avanzar
el iterador a la siguiente espacio de la lista, despues hace una especie de if con
el bool operator, para que este calcule o cheque si hay dos operadores que apuntan a un
mismo nodo para delvolver si o no dependiendo de lo que se pide, para despues
tener una seccion que solo se podra acceder por medio de la funcion, que declara
una variable de tipo puntero a node, para despues hace un constructor de clase iterador
que toma un puntero a node como argumento, para por ultimo hacer que la clase sllist,
sea amiguis de la clase iterador lo que hara que esta pueda acceder funciones o variables
privadas en este caso.

```c++
public:
    SLList();

    SLList(std::initializer_list <Object> init_list);

    ~SLList();

    iterator begin();

    iterator end();

    int size() const;

    bool empty() const;

    void clear();

    Object &front();

    void push_front(const Object &x);

    void push_front(Object &&x);

    void pop_front();

    iterator insert(iterator itr, const Object &x);

    iterator insert(iterator itr, Object &&x);

    iterator erase(iterator itr);

    void print();

private:
    Node *head;
    Node *tail;
    int theSize;

    void init();
};
```
Lo primero que hace es crear un constructor se utiliza para crear una lista
enlazada vacia, para despues inicializar otro lista enlazada perp con datos dados anteriormente,
para por ultimo hacer un destructor que libere memoria, para despues devolver el iterador
al primer espacio de la lista para despues en end() hace lo mismo pero al final
de la listespa, para despues por medio de int size() const devuelve el numero de elementos de la lista
, despues bool empty() const; devuelve true si la lista esta vacia de lo contrario
devuelve false, void clear(); hace que elimine todos los elementos de la lista
, front(): Devuelve una referencia al primer elemento de la lista, push_front(const Object &x): Inserta un elemento al principio de la lista
, push_front(Object &&x): Inserta un elemento al principio de la lista, utilizando el movimiento de objetos,
pop_front(): Elimina el primer elemento de la lista, insert(iterator itr, const Object &x): Inserta un elemento antes de la posición indicada por el iterador itr,
insert(iterator itr, Object &&x): Inserta un elemento antes de la posición indicada por el iterador itr, utilizando el movimiento de objetos,
erase(iterator itr) elimina el elemento de la lista apuntado por el iterador, para despues imprimir la lista.
```c++
private:
    Node *head;
    Node *tail;
    int theSize;

    void init();
};
```
para despues de manera privada hace que nodo apunten al principio de la lista, y al
ultimo de lista, por medio del int theSize medira el tamaño de la lista,
void init();: Un método privado que inicializa la lista. Puede ser utilizado internamente para evitar la duplicación de código en los constructores.

## Implementacion

```c++
#include "SLList.h"

template<typename Object>
SLList<Object>::Node::Node(const Object &d, Node *n)
        : data{d}, next{n} {}

template<typename Object>
SLList<Object>::Node::Node(Object &&d, Node *n)
        : data{std::move(d)}, next{n} {}

template<typename Object>
SLList<Object>::iterator::iterator() : current{nullptr} {}

template<typename Object>
Object &SLList<Object>::iterator::operator*() {
    if(current == nullptr)
        throw std::logic_error("Trying to dereference a null pointer.");
    return current->data;
}

template<typename Object>
typename SLList<Object>::iterator &SLList<Object>::iterator::operator++() {
    if(current)
        current = current->next;
    else
        throw std::logic_error("Trying to increment past the end.");
    return *this;
}

template<typename Object>
typename SLList<Object>::iterator SLList<Object>::iterator::operator++(int) {
    iterator old = *this;
    ++(*this);
    return old;
}

template<typename Object>
bool SLList<Object>::iterator::operator==(const iterator &rhs) const {
    return current == rhs.current;
}

template<typename Object>
bool SLList<Object>::iterator::operator!=(const iterator &rhs) const {
    return !(*this == rhs);
}

template<typename Object>
SLList<Object>::iterator::iterator(Node *p) : current{p} {}

template<typename Object>
SLList<Object>::SLList() : head(new Node()), tail(new Node()), theSize(0) {
    head->next = tail;
}

template<typename Object>
SLList<Object>::SLList(std::initializer_list <Object> init_list) {
    head = new Node();
    tail = new Node();
    head->next = tail;
    theSize = 0;
    for(const auto& x : init_list) {
        push_front(x);
    }
}

template<typename Object>
SLList<Object>::~SLList() {
    clear();
    delete head;
    delete tail;
}

template<typename Object>
typename SLList<Object>::iterator SLList<Object>::begin() { return {head->next}; }

template<typename Object>
typename SLList<Object>::iterator SLList<Object>::end() { return {tail}; }

template<typename Object>
int SLList<Object>::size() const { return theSize; }

template<typename Object>
bool SLList<Object>::empty() const { return size() == 0; }

template<typename Object>
void SLList<Object>::clear() { while (!empty()) pop_front(); }

template<typename Object>
Object &SLList<Object>::front() {
    if(empty())
        throw std::logic_error("List is empty.");
    return *begin();
}

template<typename Object>
void SLList<Object>::push_front(const Object &x) { insert(begin(), x); }

template<typename Object>
void SLList<Object>::push_front(Object &&x) { insert(begin(), std::move(x)); }

template<typename Object>
void SLList<Object>::pop_front() {
    if(empty())
        throw std::logic_error("List is empty.");
    erase(begin());
}

template<typename Object>
typename SLList<Object>::iterator SLList<Object>::insert(iterator itr, const Object &x) {
    Node *p = itr.current;
    Node *newNode = new Node{x, p->next};
    p->next = newNode;
    theSize++;
    return iterator(newNode);
}

template<typename Object>
typename SLList<Object>::iterator SLList<Object>::insert(iterator itr, Object &&x) {
    Node *p = itr.current;
    Node *newNode = new Node{std::move(x), p->next};
    p->next = newNode;
    theSize++;
    return iterator(newNode);
}

template<typename Object>
typename SLList<Object>::iterator SLList<Object>::erase(iterator itr) {
    if (itr == end())
        throw std::logic_error("Cannot erase at end iterator");
    Node *p = head;
    while (p->next != itr.current) p = p->next;
    Node *toDelete = itr.current;
    p->next = itr.current->next;
    delete toDelete;
    theSize--;
    return iterator(p->next);
}

template<typename Object>
void SLList<Object>::print() {
    iterator itr = begin();
    while (itr != end()) {
        std::cout << *itr << " ";
        ++itr;
    }
    std::cout << std::endl;
}

template<typename Object>
void SLList<Object>::init() {
    theSize = 0;
    head->next = tail;
}
```
Ahora vamos a explicar lo que es la implementacion que es una parte muy importante
del codigo
```c++
template<typename Object>
SLList<Object>::Node::Node(const Object &d, Node *n)
        : data{d}, next{n} {}
```
Este es un contructor que permite crear un nuevo nodo de la lista enlazada
con un valor de datos especificos y hace un puntero al siguiente nodo en la secuencia
```c++
template<typename Object>
SLList<Object>::Node::Node(Object &&d, Node *n)
        : data{std::move(d)}, next{n} {}
```
Este constructor hace lo mismo que el anterior, con la diferencia de que
agarra "&&d", un valor de datos que se ha movido de otro objeto, que permite que el
codigo tenga una mayor eficiencia.
```c++
template<typename Object>
SLList<Object>::iterator::iterator() : current{nullptr} {}
```
Este es un constructor que proporciona una manera de inicializar un iterador
para una lista simple sin especificar un nodo inicial, esto sirve para que no tenga
una posicion inicial, para despues poder moverlo a otro lado para mas comodidad
```c++
template<typename Object>
Object &SLList<Object>::iterator::operator*() {
    if(current == nullptr)
        throw std::logic_error("Trying to dereference a null pointer.");
    return current->data;
}
```
Esta es una funcion que permite acceder al valor de datos de un nodo al que apunta el
iterador en una lista enlazada simple, y lanza un mensaje de error si no apunta 
a ningun nodo valido
```c++
template<typename Object>
typename SLList<Object>::iterator &SLList<Object>::iterator::operator++() {
    if(current)
        current = current->next;
    else
        throw std::logic_error("Trying to increment past the end.");
    return *this;
}
```
Esta parte del codigo funciona de manera de que el iterador avance por todo el nodo
de la lista enlazada simple de tal manera que sobrecarga el iterador para ir sumandolo
y lanza un error cuando este revasa el limte de la lista
```c++
template<typename Object>
typename SLList<Object>::iterator SLList<Object>::iterator::operator++(int) {
    iterator old = *this;
    ++(*this);
    return old;
}
```
Este hace casi lo mismo que al anterior nadamas que al sobrecargar el iterador este
guarda el valor anterior a ser incrementado, esto para tener como una copia de seguridad
```c++
template<typename Object>
bool SLList<Object>::iterator::operator==(const iterator &rhs) const {
    return current == rhs.current;
}
```
Esta parte sirve para poder sobrecargar el operador de igual lo que permite comparar
dos iteradores apuntan a un mismo nodo en una lista enlazada simple
```c++
template<typename Object>
bool SLList<Object>::iterator::operator!=(const iterator &rhs) const {
    return !(*this == rhs);
}
```
Lo mismo que al anterior parte del codigo nadamas que este lo compara si no esta
apuntando a un mismo nodo
```c++
template<typename Object>
SLList<Object>::iterator::iterator(Node *p) : current{p} {}
```
Esta parte sirve para poder crear un iterador y establecer que apunte a un nodo dentro
de una lista enlazada
```c++
template<typename Object>
SLList<Object>::SLList() : head(new Node()), tail(new Node()), theSize(0) {
    head->next = tail;
}
```
Este constructor crea una lista enlazada vacia ademas de dos nodos head y tail
que permite crear una conexion entre ellos para indicar que la lista esta vacia
```c++
template<typename Object>
SLList<Object>::SLList(std::initializer_list <Object> init_list) {
    head = new Node();
    tail = new Node();
    head->next = tail;
    theSize = 0;
    for(const auto& x : init_list) {
        push_front(x);
    }
}
```
Este codigo sirve para poder crear una lista enlazada simple para inicializando sus elementos, con valores
dados en la lista de inicializacion.
```c++
template<typename Object>
SLList<Object>::~SLList() {
    clear();
    delete head;
    delete tail;
}
```
Este es un destructor que sirve para que cuando el objeto sllist se destruye o borre todos los recursos
asociados a este se eliminen correctamente.
```c++
template<typename Object>
typename SLList<Object>::iterator SLList<Object>::begin() { return {head->next}; }
```
este sirve para proporciona un iterador que apunta al primer elemento de una lista enlazada permitiendo recorrer una lista desde el principio

```c++
template<typename Object>
typename SLList<Object>::iterator SLList<Object>::end() { return {tail}; }
```
Lo mismo que el anterior pero en lugar del principio de la lista lo hace hasta al final lo que permite recorrerlos de principio
a fin por medio de un iterador
```c++
template<typename Object>
int SLList<Object>::size() const { return theSize; }
```
Este parte del codigo es simple solamente sirve para poder averiguar el tamaño de la lista sin necesidad de modificarla o manipularla
```c++
template<typename Object>
bool SLList<Object>::empty() const { return size() == 0; }
```
Esta parte verifica si la lista esta vacia o no sin necesidad de checar el tamaño de la lista
```c++
template<typename Object>
void SLList<Object>::clear() { while (!empty()) pop_front(); }
```
Este codigo sirve apra poder eliminar todos los elemento de la lista usando una funcion llamada pop_front que no conocia
```c++
template<typename Object>
Object &SLList<Object>::front() {
    if(empty())
        throw std::logic_error("List is empty.");
    return *begin();
}
```
Este permite acceder a una lista enlazada buscando el primer parametro de esta lista
primero verificando si esta lista vacia o no
```c++
template<typename Object>
typename SLList<Object>::iterator SLList<Object>::insert(iterator itr, const Object &x) {
    Node *p = itr.current;
    Node *newNode = new Node{x, p->next};
    p->next = newNode;
    theSize++;
    return iterator(newNode);
}
```
Este es confuso ya que entiendo que permite insertar un elemento en una lista enlazada antes de la posicion indicada por el iterador pero no entiendo como funciona esto.
```c++
template<typename Object>
typename SLList<Object>::iterator SLList<Object>::insert(iterator itr, Object &&x) {
    Node *p = itr.current;
    Node *newNode = new Node{std::move(x), p->next};
    p->next = newNode;
    theSize++;
    return iterator(newNode);
}
```
Este método proporciona una forma eficiente de insertar un nuevo elemento en la lista enlazada utilizando una semántica de movimiento para el valor que se va a insertar.
```c++
template<typename Object>
typename SLList<Object>::iterator SLList<Object>::erase(iterator itr) {
    if (itr == end())
        throw std::logic_error("Cannot erase at end iterator");
    Node *p = head;
    while (p->next != itr.current) p = p->next;
    Node *toDelete = itr.current;
    p->next = itr.current->next;
    delete toDelete;
    theSize--;
    return iterator(p->next);
}
```
Este metodo proporciona una eliminar un elemento una lista enlazada en la posicion dada por el iterador y devuelve un iterador que apunta al siguiente elemento
despues de la elimincacion.
```c++
template<typename Object>
void SLList<Object>::print() {
    iterator itr = begin();
    while (itr != end()) {
        std::cout << *itr << " ";
        ++itr;
    }
    std::cout << std::endl;
}
```
Esta es una forma de poder emprimri los datos de una lista de manera ordenada osea dandoles espacio por cada dato dato
```c++
template<typename Object>
void SLList<Object>::init() {
    theSize = 0;
    head->next = tail;
}
```
Este metodo sirve para poder basicamente reinciar una lista, osea dejarla vacia o inicial antes de haberla utilizado
para poder alamacenar datos.