# Documentacion Struct Wars: El Retorno del Árbol
### Hecho por Said de Jesus Vidal Ramirez

## Interfaz
```c++
#ifndef AVLTREE_H
#define AVLTREE_H
#include <iostream>

struct Node {
    int value;
    Node* left;
    Node* right;
    int height;
};

class AVLTree {
    public:
    void printTree() {
        printTree(root, 0, 10);
    }
private:
    Node* root;

    int getNodeHeight(Node* N) {
        if (N == nullptr)
            return 0;
        return N->height;
    }

    int maxHeight(int a, int b) {
        return (a > b)? a : b;
    }

    Node* newNode(int value) {
        Node* node = new Node();
        node->value = value;
        node->left = nullptr;
        node->right = nullptr;
        node->height = 1;
        return(node);
    }

    Node* rightRotate(Node* y) {
        Node* x = y->left;
        Node* T2 = x->right;

        x->right = y;
        y->left = T2;

        y->height = maxHeight(getNodeHeight(y->left), getNodeHeight(y->right)) + 1;
        x->height = maxHeight(getNodeHeight(x->left), getNodeHeight(x->right)) + 1;

        return x;
    }

    Node* leftRotate(Node* x) {
        Node* y = x->right;
        Node* T2 = y->left;

        y->left = x;
        x->right = T2;

        x->height = maxHeight(getNodeHeight(x->left), getNodeHeight(x->right)) + 1;
        y->height = maxHeight(getNodeHeight(y->left), getNodeHeight(y->right)) + 1;

        return y;
    }

    int getBalance(Node* N) {
        if (N == nullptr)
            return 0;
        return getNodeHeight(N->left) - getNodeHeight(N->right);
    }

    Node* insertNode(Node* node, int value) {
        if (node == nullptr)
            return(newNode(value));

        if (value < node->value)
            node->left = insertNode(node->left, value);
        else if (value > node->value)
            node->right = insertNode(node->right, value);
        else
            return node;

        node->height = 1 + maxHeight(getNodeHeight(node->left), getNodeHeight(node->right));

        int balance = getBalance(node);

        if (balance > 1 && value < node->left->value)
            return rightRotate(node);

        if (balance < -1 && value > node->right->value)
            return leftRotate(node);

        if (balance > 1 && value > node->left->value) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        if (balance < -1 && value < node->right->value) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node;
    }

    Node* minValueNode(Node* node) {
        Node* current = node;

        while (current->left != nullptr)
            current = current->left;

        return current;
    }

    Node* deleteNode(Node* root, int value) {
        if (root == nullptr)
            return root;

        if ( value < root->value )
            root->left = deleteNode(root->left, value);
        else if( value > root->value )
            root->right = deleteNode(root->right, value);
        else {
            if( (root->left == nullptr) || (root->right == nullptr) ) {
                Node *temp = root->left ? root->left : root->right;

                if(temp == nullptr) {
                    temp = root;
                    root = nullptr;
                }
                else
                    *root = *temp;

                delete temp;
            }
            else {
                Node* temp = minValueNode(root->right);

                root->value = temp->value;

                root->right = deleteNode(root->right, temp->value);
            }
        }

        if (root == nullptr)
            return root;

        root->height = 1 + maxHeight(getNodeHeight(root->left), getNodeHeight(root->right));

        int balance = getBalance(root);

        if (balance > 1 && getBalance(root->left) >= 0)
            return rightRotate(root);

        if (balance > 1 && getBalance(root->left) < 0) {
            root->left = leftRotate(root->left);
            return rightRotate(root);
        }

        if (balance < -1 && getBalance(root->right) <= 0)
            return leftRotate(root);

        if (balance < -1 && getBalance(root->right) > 0) {
            root->right = rightRotate(root->right);
            return leftRotate(root);
        }

        return root;
    }

    void deleteTree(Node* node) {
        if (node == nullptr)
            return;

        deleteTree(node->left);
        deleteTree(node->right);

        delete node;
    }

public:
    AVLTree() : root(nullptr) {}

    ~AVLTree() {
        deleteTree(root);
    }

    void insert(int value) {
        root = insertNode(root, value);
    }

    void remove(int value) {
        root = deleteNode(root, value);
    }

    void inorderTraversal(Node* node) {
        if (node == nullptr)
            return;

        inorderTraversal(node->left);
        std::cout << node->value << " ";
        inorderTraversal(node->right);
    }

    void preorderTraversal(Node* node) {
        if (node == nullptr)
            return;

        std::cout << node->value << " ";
        preorderTraversal(node->left);
        preorderTraversal(node->right);
    }

    void postorderTraversal(Node* node) {
        if (node == nullptr)
            return;

        postorderTraversal(node->left);
        postorderTraversal(node->right);
        std::cout << node->value << " ";
    }
    void printTree(Node* root, int space = 0, int COUNT = 10) {
        if (root == nullptr) {
            return;
        }

        space += COUNT;
        printTree(root->right, space);

        std::cout << std::endl;

        for (int i = COUNT; i < space; i++) {
            std::cout << " ";
        }

        std::cout << root->value << "\n";

        printTree(root->left, space);
    }
};


#endif // AVLTREE_H
```
Este codigo solamente tiene la interfaz por lo que todo se desarrolla en este codigo de manera conjunta

```c++
struct Node {
    int value;
    Node* left;
    Node* right;
    int height;
};
```
Este struct es crucial para el codigo ya que es el que permite, crear los nodos para la construccion de arboles binarios
cada uno de los nodos tiene un valor asi como punteros a sus hijos izquierdo y derecho

```c++
class AVLTree {
    public:
    void printTree() {
        printTree(root, 0, 10);
    }
```
En palabras sencillas este es un print que permite vizualizar el arbol AVL, llama a una función interna con el 
puntero a la raiz del arbol, un nivel de profundidad inicial y un ancho de impresion predeterminado.
```c++
private:
    Node* root;

    int getNodeHeight(Node* N) {
        if (N == nullptr)
            return 0;
        return N->height;
    }
```
En resumen getnodeheight es una funcion privada que se utiliza para obtener la altura de un nodo en especifico
del arbol, si el nodo es null se devuelve 0.
```c++
int maxHeight(int a, int b) {
        return (a > b)? a : b;
    }
```
Esta parte del codigo es una simple comparacion de dos datos para saber cual de los dos es mas grande en altura
```c++
Node* newNode(int value) {
        Node* node = new Node();
        node->value = value;
        node->left = nullptr;
        node->right = nullptr;
        node->height = 1;
        return(node);
    }
```
Esta parte del codigo se utiliza para crear un nuevo nodo para el arbol binario con un valor en espcifico, e
ste nodo se inicializa con punteros a nullptr para sus hijos (ya que es una hoja), y la altura se inicializa en 1
```c++
Node* rightRotate(Node* y) {
        Node* x = y->left;
        Node* T2 = x->right;

        x->right = y;
        y->left = T2;

        y->height = maxHeight(getNodeHeight(y->left), getNodeHeight(y->right)) + 1;
        x->height = maxHeight(getNodeHeight(x->left), getNodeHeight(x->right)) + 1;

        return x;
    }
```
esta funcion implementa una rotacion hacia la derecha del arbol, alrededor del nodo "y", esta rotacion
restaura la propiedad, de balance del arbol AVL despues de que se haya desequilibrado a la izquierda
```c++
Node* leftRotate(Node* x) {
        Node* y = x->right;
        Node* T2 = y->left;

        y->left = x;
        x->right = T2;

        x->height = maxHeight(getNodeHeight(x->left), getNodeHeight(x->right)) + 1;
        y->height = maxHeight(getNodeHeight(y->left), getNodeHeight(y->right)) + 1;

        return y;
    }
```
Es lo mismo que el anterior, nadamas que este tiene una rotacion hacia la izquierda del arbol, alrededor del nodo "x",
despues de que se haya desquilibrado hacia la derecha.
```c++
int getBalance(Node* N) {
        if (N == nullptr)
            return 0;
        return getNodeHeight(N->left) - getNodeHeight(N->right);
    }
```
esta funcion calcula el factor de equilibrio, de un nodo en un arbol AVL, si el nodo es null devuelve 0, 
de lo contrario devuelve la diferencia entre la altura del subarbol izquierdo y la altura derecho del nodo
```c++
Node* insertNode(Node* node, int value) {
        if (node == nullptr)
            return(newNode(value));

        if (value < node->value)
            node->left = insertNode(node->left, value);
        else if (value > node->value)
            node->right = insertNode(node->right, value);
        else
            return node;

        node->height = 1 + maxHeight(getNodeHeight(node->left), getNodeHeight(node->right));

        int balance = getBalance(node);

        if (balance > 1 && value < node->left->value)
            return rightRotate(node);

        if (balance < -1 && value > node->right->value)
            return leftRotate(node);

        if (balance > 1 && value > node->left->value) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        if (balance < -1 && value < node->right->value) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node;
    }
```
Esta funcion se utiliza para insertar un nuevo nodo con un valor dado, en un arbol AVL. La insercion en un arbol AVL, implica los dos pasos
principales, la insercion del nodo como en un arbol binario de busqueda normal, seguido de la restauracion del balance del arbol AVL, en resumen, esta funcion inserta un nuevo nodo en un arbol AVL y realiza las rotaciones necesarias para mantener el arbol balanceado despues de la inserción.
```c++
Node* minValueNode(Node* node) {
        Node* current = node;

        while (current->left != nullptr)
            current = current->left;

        return current;
    }
```
En resumen, esta funcion recorre el subarbol izquierdo de un nodo dado hasta encontrar el 
nodo con el valor minimo, y devuelve un puntero a ese nodo, es util en operaciones como eliminar el nodo con el valor mínimo en un arbol binario de busqueda.

```c++
Node* deleteNode(Node* root, int value) {
        if (root == nullptr)
            return root;

        if ( value < root->value )
            root->left = deleteNode(root->left, value);
        else if( value > root->value )
            root->right = deleteNode(root->right, value);
        else {
            if( (root->left == nullptr) || (root->right == nullptr) ) {
                Node *temp = root->left ? root->left : root->right;

                if(temp == nullptr) {
                    temp = root;
                    root = nullptr;
                }
                else
                    *root = *temp;

                delete temp;
            }
            else {
                Node* temp = minValueNode(root->right);

                root->value = temp->value;

                root->right = deleteNode(root->right, temp->value);
            }
        }

        if (root == nullptr)
            return root;

        root->height = 1 + maxHeight(getNodeHeight(root->left), getNodeHeight(root->right));

        int balance = getBalance(root);

        if (balance > 1 && getBalance(root->left) >= 0)
            return rightRotate(root);

        if (balance > 1 && getBalance(root->left) < 0) {
            root->left = leftRotate(root->left);
            return rightRotate(root);
        }

        if (balance < -1 && getBalance(root->right) <= 0)
            return leftRotate(root);

        if (balance < -1 && getBalance(root->right) > 0) {
            root->right = rightRotate(root->right);
            return leftRotate(root);
        }

        return root;
    }
```
Esta funcion se utiliza para eliminar un nodo con un valor dado, de un arbol AVL, la eliminacion de un nodo del arbol AVL
puede afectar al balance del arbol, por lo que despues de la eliminacion, se realizan las rotacioens necesarias, para mantener
el al arbol balanceado.
```c++
void deleteTree(Node* node) {
        if (node == nullptr)
            return;

        deleteTree(node->left);
        deleteTree(node->right);

        delete node;
    }
```
esta funcion elimina todos los nodos de un arbol binario, comenzando desde el nodo dado, y recorriendo recursivamente todos los nodos del arbol
es importante llamar esta funcion para eliminar todos los nodos del arbol satisfactoriamente y asi se libere la memoria correctamente
```c++
public:
    AVLTree() : root(nullptr) {}

    ~AVLTree() {
        deleteTree(root);
    }
```
En resumen, el constructor inicializa el árbol con una raíz nula y el destructor libera todos los nodos del arbol cuando 
se destruye la instancia de AVLTree ,esto garantiza una gestion adecuada de la memoria y evita problemas de perdida de memoria.
```c++
void insert(int value) {
        root = insertNode(root, value);
    }
```
este es le proporciona una interfaz para insertar valores en el arbol AVL, llamando a la funcion insert()
```c++
void remove(int value) {
        root = deleteNode(root, value);
    }
```
Al igual que el anterior este proporciona una interfaz para poder eleminar un valor del arbol AVL, llamando a ala funcion remove()
```c++
void inorderTraversal(Node* node) {
        if (node == nullptr)
            return;

        inorderTraversal(node->left);
        std::cout << node->value << " ";
        inorderTraversal(node->right);
    }
```
En resumen, el metodo inorderTraversal() realiza un recorrido en orden en el arbol binario, visitando los nodos en el 
orden correcto y mostrando sus valores, esto se hace de manera recursiva para cada nodo del arbol, comenzando desde la raiz.
```c++
void preorderTraversal(Node* node) {
        if (node == nullptr)
            return;

        std::cout << node->value << " ";
        preorderTraversal(node->left);
        preorderTraversal(node->right);
    }
```
En resumen, el metodo preorderTraversal() realiza un recorrido en preorden en 
el arbol binario, visitando los nodos en el orden correcto y mostrando sus valores, esto se hace de manera recursiva para cada nodo del arbol, comenzando desde la raiz
```c++
void postorderTraversal(Node* node) {
        if (node == nullptr)
            return;

        postorderTraversal(node->left);
        postorderTraversal(node->right);
        std::cout << node->value << " ";
    }
```
En resumen, el metodo postorderTraversal() realiza un recorrido en postorden en el arbol binario, visitando los nodos en el orden correcto y mostrando sus valores,
esto se hace de manera recursiva para cada nodo del arbol, comenzando desde la raiz.
```c++
void printTree(Node* root, int space = 0, int COUNT = 10) {
        if (root == nullptr) {
            return;
        }

        space += COUNT;
        printTree(root->right, space);

        std::cout << std::endl;

        for (int i = COUNT; i < space; i++) {
            std::cout << " ";
        }

        std::cout << root->value << "\n";

        printTree(root->left, space);
    }
```
Este ultimo parte del codigo sirve para poder imprimir lo que es el arbol de manera ordenada y legible, para demostrar de una manera mas representativa como es el que arbol binario y su manera de funcionar, 
esto se hace de manera recursiva para cada nodo del arbol, comenzando desde la raiz y continuando con los subarboles, izquierdo y derecho. 