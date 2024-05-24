# Documentacion Proyecto P1

## Interfaz

```c++
#include <utility>
#include <iostream>

template <typename Object>
class DLList {
private:
    struct Node {
        Object data;
        Node *prev;
        Node *next;

        Node(const Object &d = Object{}, Node *p = nullptr, Node *n = nullptr);
        Node(Object &&d, Node *p = nullptr, Node *n = nullptr);
    };

public:
    class const_iterator{
    public:
        const_iterator();
        const Object &operator*() const;
        const_iterator &operator++();
        const_iterator operator++ (int);
        bool operator== (const const_iterator& rhs) const;
        bool operator!= (const const_iterator& rhs) const;

    protected:
        Node* current;
        Object& retrieve() const;
        const_iterator(Node *p);

        friend class DLList<Object>;
    };

    class iterator : public const_iterator {
    public:
        iterator();
        Object& operator*();
        const Object& operator*() const;
        iterator & operator++ ();
        iterator &operator--();
        iterator operator++ (int);
        iterator operator-- (int);
        iterator operator+ (int steps) const;

    protected:
        iterator(Node *p);

        friend class DLList<Object>;
    };

public:
    DLList();
    DLList(std::initializer_list<Object> initList);
    ~DLList();
    DLList(const DLList &rhs);
    DLList &operator=(const DLList &rhs);
    DLList(DLList &&rhs);
    DLList &operator=(DLList &&rhs);

    iterator begin();
    const_iterator begin() const;
    iterator end();
    const_iterator end() const;

    int size() const;
    bool empty() const;

    void clear();

    Object &front();
    const Object &front() const;
    Object &back();
    const Object &back() const;

    void push_front(const Object &x);
    void push_front(Object &&x);
    void push_back(const Object &x);
    void push_back(Object &&x);

    void pop_front();
    void pop_back();

    iterator insert(iterator itr, const Object &x);
    iterator insert(iterator itr, Object &&x);

    void insert(int pos, const Object &x);
    void insert(int pos, Object &x);

    iterator erase(iterator itr);
    void erase(int pos);
    iterator erase(iterator from, iterator to);

    void print() const;

private:
    int theSize;
    Node *head;
    Node *tail;

    void init();
    iterator get_iterator(int pos);
};

#include "DLList.cpp"
```

```c++
template <typename Object>
class DLList {
private:
    struct Node {
        Object data;
        Node *prev;
        Node *next;

        Node(const Object &d = Object{}, Node *p = nullptr, Node *n = nullptr);
        Node(Object &&d, Node *p = nullptr, Node *n = nullptr);
    };
```
La primera parte del codigo de implementacion sirve para poder es una implementacion para
poder crear una lista doblemente enlazada que pueda contener culaquier tipo de dato, 
ademas de utilizar nodos que sirvan para apuntar tanto al nodo anterior como al siguiente

```c++
public:
    class const_iterator{
    public:
        const_iterator();
        const Object &operator*() const;
        const_iterator &operator++();
        const_iterator operator++ (int);
        bool operator== (const const_iterator& rhs) const;
        bool operator!= (const const_iterator& rhs) const;

    protected:
        Node* current;
        Object& retrieve() const;
        const_iterator(Node *p);

        friend class DLList<Object>;
    };
```
Esta parte funciona como una persona(iterador) pueda recorrer toda la lista doblemente enlazada 
ademas de haber miembros que estan protegidos dentro de este codigo pero que se puede acceder a ellos
meidante la clase ddlist.

```c++
class iterator : public const_iterator {
    public:
        iterator();
        Object& operator*();
        const Object& operator*() const;
        iterator & operator++ ();
        iterator &operator--();
        iterator operator++ (int);
        iterator operator-- (int);
        iterator operator+ (int steps) const;

    protected:
        iterator(Node *p);

        friend class DLList<Object>;
    };
```
Esta parte del codigo lo que permite es que por medio de la clase iterador se pueda modificar
elemento de la lista doblemente enlazada, con mayor facilidad ademas de que aqui se usa el * para sobrecargarlo 
y asi poder modificar elementos de la lista, cosa que yo no sabia
```c++
public:
    DLList();
    DLList(std::initializer_list<Object> initList);
    ~DLList();
    DLList(const DLList &rhs);
    DLList &operator=(const DLList &rhs);
    DLList(DLList &&rhs);
    DLList &operator=(DLList &&rhs);

    iterator begin();
    const_iterator begin() const;
    iterator end();
    const_iterator end() const;

    int size() const;
    bool empty() const;

    void clear();

    Object &front();
    const Object &front() const;
    Object &back();
    const Object &back() const;

    void push_front(const Object &x);
    void push_front(Object &&x);
    void push_back(const Object &x);
    void push_back(Object &&x);

    void pop_front();
    void pop_back();

    iterator insert(iterator itr, const Object &x);
    iterator insert(iterator itr, Object &&x);

    void insert(int pos, const Object &x);
    void insert(int pos, Object &x);

    iterator erase(iterator itr);
    void erase(int pos);
    iterator erase(iterator from, iterator to);

    void print() const;

private:
    int theSize;
    Node *head;
    Node *tail;

    void init();
    iterator get_iterator(int pos);
};
```
Esta parte del codigo se conforma de varias funciones que cumplen con propositos diferentes
, como primera parte inicializa la lista vacia, despues hace lo mismo de inicializar otra lista pero con elementos
de initializer_list<Object>, despues ~DLList(): es un destructor que libera memoria, DLList(const DLList &rhs):  es un constructor
que crea una lista como copia de otra ya existente, DLList &operator=(const DLList &rhs): sobrecarga el operador de asignacion para poder 
realizar una asignacion mas a detalle entre dos listas, DLList(DLList &&rhs): este es como un camion de carga que transporte elementos de una
lista a otra, DLList &operator=(DLList &&rhs): lo mismo nadamas que sobrecargan el operador de asignacion, la verdad no encontre diferencias
entre una a otra, las demas funciones son algunas que ya hemos visto que son iteradores que apuntan a un elemento de la lista como el begin que apunta al principio,
despues seguiriamos con metodos que permiten manipular la lista, int size() const: que es para el numero de elemtos de la lista,
bool empty() const: verifica si la lista esta vacia, void clear(): elmina todos los elementos de la lista, Métodos para acceder al primer y último elemento de la lista, tanto en versión modificable como constante (front(), back())
, Métodos para añadir elementos al frente o al final de la lista (push_front(), push_back()),
metodos para eleminar el elemento de la primera posicion de la lista asi como el ultimo con las funciones pop_front(), pop_back(),
insert(): este es un metodo para poder isertar un dato en un punto especifico de la lista,
metodo para eliminar elementos de una posición específica o un rango de posiciones ques erase()

## Implementacion

```c++
#include "DLList.h"

template<typename Object>
DLList<Object>::Node::Node(const Object &d, Node *p, Node *n)
        : data{d}, prev{p}, next{n} {}

template<typename Object>
DLList<Object>::Node::Node(Object &&d, Node *p, Node *n)
        : data{std::move(d)}, prev{p}, next{n} {}

template<typename Object>
DLList<Object>::const_iterator::const_iterator() : current{nullptr} {}

template<typename Object>
const Object &DLList<Object>::const_iterator::operator*() const {
    return retrieve();
}

template<typename Object>
typename DLList<Object>::const_iterator &DLList<Object>::const_iterator::operator++() {
    current = current->next;
    return *this;
}

template<typename Object>
typename DLList<Object>::const_iterator DLList<Object>::const_iterator::operator++(int) {
    const_iterator old = *this;
    ++(*this);
    return old;
}

template<typename Object>
bool DLList<Object>::const_iterator::operator==(const const_iterator &rhs) const {
    return current == rhs.current;
}

template<typename Object>
bool DLList<Object>::const_iterator::operator!=(const const_iterator &rhs) const {
    return !(*this == rhs);
}

template<typename Object>
Object &DLList<Object>::const_iterator::retrieve() const {
    return current->data;
}

template<typename Object>
DLList<Object>::const_iterator::const_iterator(Node *p) : current{p} {}

template<typename Object>
DLList<Object>::iterator::iterator() {}

template<typename Object>
Object &DLList<Object>::iterator::operator*() {
    return const_iterator::retrieve();
}

template<typename Object>
const Object &DLList<Object>::iterator::operator*() const {
    return const_iterator::operator*();
}

template<typename Object>
typename DLList<Object>::iterator &DLList<Object>::iterator::operator++() {
    this->current = this->current->next;
    return *this;
}

template<typename Object>
typename DLList<Object>::iterator &DLList<Object>::iterator::operator--() {
    this->current = this->current->prev;
    return *this;
}

template<typename Object>
typename DLList<Object>::iterator DLList<Object>::iterator::operator++(int) {
    iterator old = *this;
    ++(*this);
    return old;
}

template<typename Object>
typename DLList<Object>::iterator DLList<Object>::iterator::operator--(int) {
    iterator old = *this;
    --(*this);
    return old;
}

template<typename Object>
typename DLList<Object>::iterator DLList<Object>::iterator::operator+(int steps) const {
    iterator new_itr = *this;
    for(int i = 0; i < steps; ++i) {
        ++new_itr;
    }
    return new_itr;
}

template<typename Object>
DLList<Object>::iterator::iterator(Node *p) : const_iterator{p} {}

template<typename Object>
DLList<Object>::DLList() : theSize{0}, head{new Node}, tail{new Node} {
    head->next = tail;
    tail->prev = head;
}

template<typename Object>
DLList<Object>::DLList(std::initializer_list<Object> initList) : DLList() {
    for(const auto &item : initList) {
        push_back(item);
    }
}

template<typename Object>
DLList<Object>::~DLList() {
    clear();
    delete head;
    delete tail;
}

template<typename Object>
DLList<Object>::DLList(const DLList &rhs) : DLList() {
    for(auto &item : rhs) {
        push_back(item);
    }
}

template<typename Object>
DLList<Object> &DLList<Object>::operator=(const DLList &rhs) {
    DLList copy = rhs;
    std::swap(*this, copy);
    return *this;
}

template<typename Object>
DLList<Object>::DLList(DLList &&rhs) : theSize{rhs.theSize}, head{rhs.head}, tail{rhs.tail} {
    rhs.theSize = 0;
    rhs.head = nullptr;
    rhs.tail = nullptr;
}

template<typename Object>
DLList<Object> &DLList<Object>::operator=(DLList &&rhs) {
    std::swap(theSize, rhs.theSize);
    std::swap(head, rhs.head);
    std::swap(tail, rhs.tail);
    return *this;
}

template<typename Object>
typename DLList<Object>::iterator DLList<Object>::begin() {
    return {head->next};
}

template<typename Object>
typename DLList<Object>::const_iterator DLList<Object>::begin() const {
    return {head->next};
}

template<typename Object>
typename DLList<Object>::iterator DLList<Object>::end() {
    return {tail};
}

template<typename Object>
typename DLList<Object>::const_iterator DLList<Object>::end() const {
    return {tail};
}

template<typename Object>
int DLList<Object>::size() const {
    return theSize;
}

template<typename Object>
bool DLList<Object>::empty() const {
    return size() == 0;
}

template<typename Object>
void DLList<Object>::clear() {
    while(!empty()) {
        pop_front();
    }
}

template<typename Object>
Object &DLList<Object>::front() {
    return *begin();
}

template<typename Object>
const Object &DLList<Object>::front() const {
    return *begin();
}

template<typename Object>
Object &DLList<Object>::back() {
    return *(--end());
}

template<typename Object>
const Object &DLList<Object>::back() const {
    return *(--end());
}

template<typename Object>
void DLList<Object>::push_front(const Object &x) {
    insert(begin(), x);
}

template<typename Object>
void DLList<Object>::push_front(Object &&x) {
    insert(begin(), std::move(x));
}

template<typename Object>
void DLList<Object>::push_back(const Object &x) {
    insert(end(), x);
}

template<typename Object>
void DLList<Object>::push_back(Object &&x) {
    insert(end(), std::move(x));
}

template<typename Object>
void DLList<Object>::pop_front() {
    erase(begin());
}

template<typename Object>
void DLList<Object>::pop_back() {
    erase(--end());
}

template<typename Object>
typename DLList<Object>::iterator DLList<Object>::insert(iterator itr, const Object &x) {
    Node *p = itr.current;
    theSize++;
    return {p->prev = p->prev->next = new Node{x, p->prev, p}};
}

template<typename Object>
typename DLList<Object>::iterator DLList<Object>::insert(iterator itr, Object &&x) {
    Node *p = itr.current;
    theSize++;
    return {p->prev = p->prev->next = new Node{std::move(x), p->prev, p}};
}

template<typename Object>
void DLList<Object>::insert(int pos, const Object &x) {
    insert(get_iterator(pos), x);
}

template<typename Object>
void DLList<Object>::insert(int pos, Object &&x) {
    insert(get_iterator(pos), std::move(x));
}

template<typename Object>
typename DLList<Object>::iterator DLList<Object>::erase(iterator itr) {
    Node *p = itr.current;
    iterator retVal(p->next);
    p->prev->next = p->next;
    p->next->prev = p->prev;
    delete p;
    theSize--;
    return retVal;
}

template<typename Object>
void DLList<Object>::erase(int pos) {
    erase(get_iterator(pos));
}

template<typename Object>
typename DLList<Object>::iterator DLList<Object>::erase(iterator from, iterator to) {
    for(iterator itr = from; itr != to;) {
        itr = erase(itr);
    }
    return to;
}

template<typename Object>
void DLList<Object>::print() const {
    for(const auto &item : *this) {
        std::cout << item << " ";
    }
    std::cout << std::endl;
}

template<typename Object>
void DLList<Object>::init() {
    theSize = 0;
    head = new Node;
    tail = new Node;
    head->next = tail;
    tail->prev = head;
}

template<typename Object>
typename DLList<Object>::iterator DLList<Object>::get_iterator(int pos) {
    iterator itr = begin();
    for(int i = 0; i < pos; ++i) {
        ++itr;
    }
    return itr;
}
```
La implementacion esta conformada por varios metodos variados para difertentes propositos

```c++
template<typename Object>
DLList<Object>::Node::Node(const Object &d, Node *p, Node *n)
        : data{d}, prev{p}, next{n} {}
```
Este es un constructor que se utiliza para crear un nuevo nodo en una lista doblemente enlazada y permite especificiar el dato que contendra el nodo asi como los punteros
del nodo anterior y siguiente en la lista

```c++
template<typename Object>
DLList<Object>::Node::Node(Object &&d, Node *p, Node *n)
        : data{std::move(d)}, prev{p}, next{n} {}
```
Es lo mismo que el anterior metodo, permite crear una lista doblemente enlazada permitiendo especificar que tipo de dato contendra el nodo, solamente que atraves del rvalue reference
```c++
template<typename Object>
DLList<Object>::const_iterator::const_iterator() : current{nullptr} {}
```
Este es un contructor que se utiliza para para inicializar un objeto const_iterator estableciendo su puntero current en nullptr, lo que indica
que el iterador no apunta actualmente a ningun elemento de la lista.

```c++
template<typename Object>
const Object &DLList<Object>::const_iterator::operator*() const {
    return retrieve();
}
```
este metodo se centra en el operador * que permite acceder al dato al que apunta el iterador constante,
devuelve una referencia constante al dato al dato para evitar que se modifique el dato atravez del iterador constante

```c++
template<typename Object>
typename DLList<Object>::const_iterator &DLList<Object>::const_iterator::operator++() {
    current = current->next;
    return *this;
}
```
este metodo sirve para que un operador de incremento prefijo avanza al iterador al siguiente nodo en la lista y luego devuleve una referencia
al iterador actualizado para permitir el encadenamiento de operaciones de incremento

```c++
template<typename Object>
typename DLList<Object>::const_iterator DLList<Object>::const_iterator::operator++(int) {
    const_iterator old = *this;
    ++(*this);
    return old;
}
```
este motodo sirve para este operador de incremeto de sufijo devuelve una copia de iterador antes de ser incrementado, y luego incrementa
el iterador.
```c++
template<typename Object>
bool DLList<Object>::const_iterator::operator==(const const_iterator &rhs) const {
    return current == rhs.current;
}
```
ESte ya lo habiamos vistos que es que sobrecarga el operador de igualdad para comparar si dos iteradores constantes estan apuntando a un mismo nodo,
en la lista devolviendo true si es asi y false si no lo hacen

```c++
template<typename Object>
bool DLList<Object>::const_iterator::operator!=(const const_iterator &rhs) const {
    return !(*this == rhs);
}
```
este metodo tambienes un comparador que sobrecarga el operador de desigualdad, si dos iteradores constantes son diferentes, 
devuelve true si son iguales y si no lo son devuelve false
```c++
template<typename Object>
Object &DLList<Object>::const_iterator::retrieve() const {
    return current->data;
}
```
este metodo se utiliza para recuperar el dato almacenado en el nodo al que apunta el iterador constante, devolviendo una referencia al dato
```c++
template<typename Object>
DLList<Object>::const_iterator::const_iterator(Node *p) : current{p} {}
```
Este es un constructor se utiliza para crear un iterador constante qeu apunta a un nodo especifico de la lista doblemente enlazada,
recibe un puntero a un nodo como parámetro y establece el miembro current del iterador para que apunte a ese nodo
```c++
template<typename Object>
DLList<Object>::iterator::iterator() {}
```
este constructor solamente inicializa un iterador sin hacer nada especial, solamente lo crea
```c++
template<typename Object>
Object &DLList<Object>::iterator::operator*() {
    return const_iterator::retrieve();
}
```
sirve para que el operador * se utilize para acceder al dato al que apunta el iterador, y devolver una referencia de este dato,
ademas la función retrieve() se encarga de obtener el dato desde el nodo actual al que apunta el iterador.
```c++
template<typename Object>
const Object &DLList<Object>::iterator::operator*() const {
    return const_iterator::operator*();
}
```
esta parte del codigo tambien sirve para el operador * constante se utiliza para acceder al dato al que apunta el iterador y devolver una referencia constante a ese dato.
```c++
template<typename Object>
typename DLList<Object>::iterator &DLList<Object>::iterator::operator++() {
    this->current = this->current->next;
    return *this;
}
```
Este es parecido al un metodo anteriormente visto, sirve para este operador de incremento prefijo avanza al iterador al siguiente nodo en la lista y luego devuelve una referencia del iterador actualizada para permitir
el encadenamiento de operaciones de incremento.

```c++
template<typename Object>
typename DLList<Object>::iterator &DLList<Object>::iterator::operator--() {
    this->current = this->current->prev;
    return *this;
}
```
lo mismo que el anterior metodo, con la diferencia de que este lo hace pero con el operador de decremento, osea hace retroceder el iterador para encadenar operadores de decremento
```c++
template<typename Object>
typename DLList<Object>::iterator DLList<Object>::iterator::operator++(int) {
    iterator old = *this;
    ++(*this);
    return old;
}
```
Este metodo lo que hace es hacer una copia del iterador antes y depues de incremetar el iterador
esto garantiza que el iterador devuelto represente el estado previo de iteradro de su incremento
```c++
template<typename Object>
typename DLList<Object>::iterator DLList<Object>::iterator::operator--(int) {
    iterator old = *this;
    --(*this);
    return old;
}
```
lo mismo que el anterior, pero solamente que en vez de incrementarlo lo decrementa

```c++
template<typename Object>
typename DLList<Object>::iterator DLList<Object>::iterator::operator+(int steps) const {
    iterator new_itr = *this;
    for(int i = 0; i < steps; ++i) {
        ++new_itr;
    }
    return new_itr;
}
```
Este funcion o metodo es como un algoritmo que permite avanzar el iterador por la lista un cierto numero, lo que devuelve el iteradro restante
```c++
template<typename Object>
DLList<Object>::iterator::iterator(Node *p) : const_iterator{p} {}
```
este constructor de la lase iterator inicializa la parte base de const_iterator con un puntero "p",
que generalmente se utiliza para inicializar el iterador en una posicion especifica de la lista
```c++
template<typename Object>
DLList<Object>::DLList() : theSize{0}, head{new Node}, tail{new Node} {
    head->next = tail;
    tail->prev = head;
}
```
Este constuctor tambien ya lo habiamos visto antes, nadamas que de una manera distinta, este contructor
lo que hace es crear una lista doblemente enalzada con un nodo nodo cabeza osea en el principio y un nodo cola
o tail osea al final para fijar una conexion entre ellos.
```c++
template<typename Object>
DLList<Object>::DLList(std::initializer_list<Object> initList) : DLList() {
    for(const auto &item : initList) {
        push_back(item);
    }
}
```
este constructor tambien permite crear una lista doblemente enlazada solamente que lo hace basandose de una lista de inicializacion,
ademas de iterar sobe los elementos de lista de inicializacion y los agrega al final de la lista doblemente enlazada.

```c++
template<typename Object>
DLList<Object>::~DLList() {
    clear();
    delete head;
    delete tail;
}
```
este es un destructor que se encarga de limpiar lo que hizo el constructor anteriormente hecho con la creacion de nodos de head y tail,
este permite limpiar la memoria, eliminando mas a profundidad estos nodos

```c++
template<typename Object>
DLList<Object>::DLList(const DLList &rhs) : DLList() {
    for(auto &item : rhs) {
        push_back(item);
    }
}
```
Este constructor crea una nueva instancia dllist que es una copia de otra instancia existente, rhs copiando todos los elementos de esta en una nueva
lista 
```c++
template<typename Object>
DLList<Object> &DLList<Object>::operator=(const DLList &rhs) {
    DLList copy = rhs;
    std::swap(*this, copy);
    return *this;
}
```
Esta parte del codigo es como un copia y pega de toda la vida ya que por medio del operador de asigancaion copia los elementos
de una lista rhs en otra lista *this, utilizando una copia temporal para garantizar la seguridad en caso de excepción durante
la asignacion
```c++
template<typename Object>
DLList<Object>::DLList(DLList &&rhs) : theSize{rhs.theSize}, head{rhs.head}, tail{rhs.tail} {
    rhs.theSize = 0;
    rhs.head = nullptr;
    rhs.tail = nullptr;
}
```
este constructor de movimiento toma los recursos de una instancia temporal de dllist y los mueve ala instacia actual
, dejando la instacia temporal en un estado valido pero sin recursos asociados
```c++
template<typename Object>
DLList<Object> &DLList<Object>::operator=(DLList &&rhs) {
    std::swap(theSize, rhs.theSize);
    std::swap(head, rhs.head);
    std::swap(tail, rhs.tail);
    return *this;
}
```
este es casi igual que uno anteriormente visto, lo que hace es transferir elementos de una lista temporal rhs a la otra lista
*this, nadamas que utilizando los punteros , lo que evita copias innecesarias y mejora el rendimiento
```c++
template<typename Object>
typename DLList<Object>::iterator DLList<Object>::begin() {
    return {head->next};
}
```
este metodo devuelve un iterador que apunta al primer elemento de la lista, excluyendo el nodo cabeza, 
esto permite permite iterar sobre los elementos de la lista utilizando el iterador retornando por este metodo
```c++
template<typename Object>
typename DLList<Object>::const_iterator DLList<Object>::begin() const {
    return {head->next};
}
```
este es lo mismo que anterior pero con la diferencia de que lo hace incluso 
en instancias constantes de la clase dllist
```c++
template<typename Object>
typename DLList<Object>::iterator DLList<Object>::end() {
    return {tail};
}
```
este hace casi lo mismo que el de head pero al ser reemplazado con el tail, este apunta el ultimo elemento
esto permitiendo iterar sobre los elementos de la lista utilizando el iterador retornado por este método, y marcar el final de la iteración en la lista.
```c++
template<typename Object>
typename DLList<Object>::const_iterator DLList<Object>::end() const {
    return {tail};
}
```
lo mismo que el anterior pero ahora lo hace incluso en instacias constantes de la clase dllist
```c++
template<typename Object>
int DLList<Object>::size() const {
    return theSize;
}
```
este metodo lo que hace es devolver el tamaño de la lista
```c++
template<typename Object>
bool DLList<Object>::empty() const {
    return size() == 0;
}
```
este tambien lo habiamos visto antes, lo que hace es verificar si la lista esta vacia o no, sin conocer el tamaño de la lista
devolviendo true si esta vacia y false si esta con datos
```c++
template<typename Object>
void DLList<Object>::clear() {
    while(!empty()) {
        pop_front();
    }
}
```
este tambien lo habiamos visto antes, en resumen limpia toda una lista por medio de la funcion
pop_front
```c++
template<typename Object>
Object &DLList<Object>::front() {
    return *begin();
}
```
este metodo permite poder acceder al primer elemento de una lista, permitiendo visualizarlo asi como poder
modificarlo 
```c++
template<typename Object>
const Object &DLList<Object>::front() const {
    return *begin();
}
```
este es lo mismo que el anterior pero con la diferencia de que se puede visualizar pero no se puede modificar
```c++
template<typename Object>
Object &DLList<Object>::back() {
    return *(--end());
}
```
lo mismo que los anteriores permitiendo poder visualizarlo y modificarlo, pero lo hace con el ultimo elemento de la lista
```c++
template<typename Object>
const Object &DLList<Object>::back() const {
    return *(--end());
}
```
lo mismo que antes, pero que nadamas se puede visualizarlo pero no modificar el ultimo elemento de la lista
```c++
template<typename Object>
void DLList<Object>::push_front(const Object &x) {
    insert(begin(), x);
}
```
este metodo proporciona una nueva forma de poder insertar datos por medio del insert()
```c++
template<typename Object>
void DLList<Object>::push_front(Object &&x) {
    insert(begin(), std::move(x));
}
```
este metodo proporciona una forma conveniente de insertar un nuevo elemento al frente de la lista utilizando la semántica de movimiento, 
lo que puede ser más eficiente que una copia directa, especialmente para objetos grandes o costosos de copiar
```c++
template<typename Object>
void DLList<Object>::push_back(const Object &x) {
    insert(end(), x);
}
```
lo mismo que el anterior pero al final de la lista con la funcion insert()
```c++
template<typename Object>
void DLList<Object>::push_back(Object &&x) {
    insert(end(), std::move(x));
}
```
este método proporciona una forma conveniente de insertar un nuevo elemento al final de la lista utilizando la semántica de movimiento
lo que puede ser más eficiente que una copia directa especialmente para objetos grandes o costosos de copiar
```c++
template<typename Object>
void DLList<Object>::pop_front() {
    erase(begin());
}
```
Este metodo lo que permite hacer es elimiar el primer elemento de una lista con la funcion erase()
```c++
template<typename Object>
void DLList<Object>::pop_back() {
    erase(--end());
}
```
lo mismo que el anterior nadamas que lo hace con el ultimo elemento de la lista
```c++
template<typename Object>
typename DLList<Object>::iterator DLList<Object>::insert(iterator itr, const Object &x) {
    Node *p = itr.current;
    theSize++;
    return {p->prev = p->prev->next = new Node{x, p->prev, p}};
}
```
este metodo permite insertar un dato dependiendo de la posicion del iterador itr,
recorriendo los demas elementos a la derecha luego retorna un iteradro apuntando al nuevo elemento insertado
```c++
template<typename Object>
typename DLList<Object>::iterator DLList<Object>::insert(iterator itr, Object &&x) {
    Node *p = itr.current;
    theSize++;
    return {p->prev = p->prev->next = new Node{std::move(x), p->prev, p}};
}
```
este hace casi lo mismo que el anterior nadamas que usa un valor ya dado para moverlo en este caso x, para despues
retornar un iterador apuntando a un nuevo elemento insertado
```c++
template<typename Object>
void DLList<Object>::insert(int pos, const Object &x) {
    insert(get_iterator(pos), x);
}
```
este metodo proporciona una forma de insertar un nuevo elemento en la lista en la posicion indicada por pos
utilizando el metodo insert()
```c++
template<typename Object>
void DLList<Object>::insert(int pos, Object &&x) {
    insert(get_iterator(pos), std::move(x));
}
```
lo mismo que el anterior con el elemento pos, para poder insertar un elemento en la lista,
pero el dato que va a poner un elemento de la lista, en lugar de crearlo lo mueve en este caso x,
el método get_iterator(pos) se utiliza para obtener el iterador correspondiente a la posición pos en la lista
```c++
template<typename Object>
typename DLList<Object>::iterator DLList<Object>::erase(iterator itr) {
    Node *p = itr.current;
    iterator retVal(p->next);
    p->prev->next = p->next;
    p->next->prev = p->prev;
    delete p;
    theSize--;
    return retVal;
}
```
este metodo lo que permite es que usando el iterador como para cuando insertamos un dato
en este caso el iterador itr de la lista elimina el elemento de la lista apuntado por el iterador
ajusta los punteros de los nodos adyacentes y luego retorna un iterador apuntando al siguiente elemento después del elemento eliminado
```c++
template<typename Object>
void DLList<Object>::erase(int pos) {
    erase(get_iterator(pos));
}
```
este método proporciona una forma conveniente de eliminar el elemento en la posición pos de la lista
utilizando el método erase() de la clase
```c++
template<typename Object>
typename DLList<Object>::iterator DLList<Object>::erase(iterator from, iterator to) {
    for(iterator itr = from; itr != to;) {
        itr = erase(itr);
    }
    return to;
}
```
Este metodo elmina todos los elementos de una lista en un rango definido por el rango [from to]
utilizando el elemento erase()
```c++
template<typename Object>
void DLList<Object>::print() const {
    for(const auto &item : *this) {
        std::cout << item << " ";
    }
    std::cout << std::endl;
}
```
esta parte solo sirve para poder imprimir todos los elementos de una lista pero con un salto de linea y espacio para hacerlo
mas estetico
```c++
template<typename Object>
void DLList<Object>::init() {
    theSize = 0;
    head = new Node;
    tail = new Node;
    head->next = tail;
    tail->prev = head;
}
```
este metodo crea una lista doblemente enlazada creando los nodos de cabeza y de la cola, ademas de establecer
los punteros apropiados para indicar que la lista esta vacia y lista para su uso
```c++
template<typename Object>
typename DLList<Object>::iterator DLList<Object>::get_iterator(int pos) {
    iterator itr = begin();
    for(int i = 0; i < pos; ++i) {
        ++itr;
    }
    return itr;
}
```
este método devuelve un iterador apuntando al elemento en la posición pos de la lista
permitiendo acceder a ese elemento y realizar operaciones en el