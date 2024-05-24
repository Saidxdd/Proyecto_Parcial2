# Documentacion T1P1
### Hecho por Said de Jesus Vidal Ramirez

## Interfaz
```c++
#ifndef TREE_H
#define TREE_H

#include <iostream>

template <typename T>
class Node {
public:
    T data;
    Node* firstChild;
    Node* nextSibling;

    explicit Node(T data);
};

template <typename T>
class Tree {
public:
    Node<T>* root;

    Tree();

    Node<T>* addNode(T data, Node<T>* parent = nullptr);

    void printTree(Node<T>* node, int level = 0);
};

#include "Tree.cpp"

#endif //TREE_H
```
La interfaz como siempre es para poder acceder a las funcion del codigo

```c++
public:
    T data;
    Node* firstChild;
    Node* nextSibling;

    explicit Node(T data);
};
```
En resumen la clase nodo representa un nodo generico con un dato y dos 
punteros que pueden ser utilizados para construir estructuras como 
arboles o listas enlazadas, el atributo data almacena el valor del 
nodo, firstChild apunta al primer hijo del nodo y 
nextSibling apunta al siguiente nodo hermano en la estructura.
```c++
template <typename T>
class Tree {
public:
    Node<T>* root;

    Tree();

    Node<T>* addNode(T data, Node<T>* parent = nullptr);

    void printTree(Node<T>* node, int level = 0);
};
```
El metodo addNode puede agregar nodos como hijos de un nodo 
padre especifico o como hijos de la raiz si no se proporciona un nodo padre, 
el metodo printtree imprime el arbol comenzando desde un nodo dado, 
utilizando una indentación para mostrar la estructura jerárquica del arbol

## Implementacion
```c++
#include "Tree.h"


template <typename T>
Node<T>::Node(T data) : data(data), firstChild(nullptr), nextSibling(nullptr) {}

template <typename T>
Tree<T>::Tree() : root(nullptr) {}

template <typename T>
Node<T>* Tree<T>::addNode(T data, Node<T>* parent) {
    Node<T>* newNode = new Node<T>(data);

    if(parent) {
        if(parent->firstChild) {
            Node<T>* sibling = parent->firstChild;
            while(sibling->nextSibling) {
                sibling = sibling->nextSibling;
            }
            sibling->nextSibling = newNode;
        } else {
            parent->firstChild = newNode;
        }
    } else {
        root = newNode;
    }

    return newNode;
}

template <typename T>
void Tree<T>::printTree(Node<T>* node, int level) {
    if(!node) return;

    for(int i = 0; i < level; i++) std::cout << "--";
    std::cout << node->data << '\n';

    printTree(node->firstChild, level + 1);
    printTree(node->nextSibling, level);
}
```
Aqui ya se aborda mas acerca de los arboles y su funcionamientos, con la ayuda de templates

```c++
template <typename T>
Node<T>::Node(T data) : data(data), firstChild(nullptr), nextSibling(nullptr) {}
```
Este constructor de la clase Node 
inicializa un nuevo nodo con un valor de tipo t 
proporcionado, el nodo se inicializa sin hijos 
(firstChild es nullptr) y sin hermanos siguientes (nextsibling es nullptr).

```c++
template <typename T>
Tree<T>::Tree() : root(nullptr) {}
```
Este al igual que el anterior es un constructor por defecto de la clase
tree, este inicializa un nuevo objeto de tipo tree con su atributo root 
establecido en nullptr, 
indicando que el arbol esta vacío y no tiene nodos en la raiz.

```c++
template <typename T>
Node<T>* Tree<T>::addNode(T data, Node<T>* parent) {
    Node<T>* newNode = new Node<T>(data);

    if(parent) {
        if(parent->firstChild) {
            Node<T>* sibling = parent->firstChild;
            while(sibling->nextSibling) {
                sibling = sibling->nextSibling;
            }
            sibling->nextSibling = newNode;
        } else {
            parent->firstChild = newNode;
        }
    } else {
        root = newNode;
    }

    return newNode;
}
```
Este addnode permite agregar un nuevo nodo al arbol, 
si se proporciona un nodo padre, el nuevo nodo se agrega como un 
hijo de ese nodo padre, si no se proporciona un nodo padre, 
el nuevo nodo se agrega como nodo raiz del arbol, ademas este tambien
se encarga de acomadar bien los nodos y que no tengan ningun solo error

```c++
template <typename T>
void Tree<T>::printTree(Node<T>* node, int level) {
    if(!node) return;

    for(int i = 0; i < level; i++) std::cout << "--";
    std::cout << node->data << '\n';

    printTree(node->firstChild, level + 1);
    printTree(node->nextSibling, level);
}
```
Este es un metodo que se encarga de imprimir todo comenzando desde el nodo propocionado
, imprime cada nodo con su respectivo nivel de indentacion, y luego imprime 
recursivamente los hijos y hermanos siguientes del nodo actual, esta es un impresion sencilla pero que nos ayuda bastante
a poder visualizar todos los datos del arbol

