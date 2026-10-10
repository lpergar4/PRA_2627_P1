#ifndef LIST_LINKED_H
#define LIST_LINKED_H

#include <ostream>
#include <stdexcept>
#include "List.h"
#include "Node.h"

template <typename T>
class ListLinked : public List<T> {
private:
    Node<T>* first;
    int n;

public:
    // Constructor sin argumentos
    ListLinked() : first(nullptr), n(0) {}

    // Destructor
    ~ListLinked() {
        while (first != nullptr) {
            Node<T>* aux = first->next;
            delete first;
            first = aux;
        }
        n = 0;
    }

    // Inserción en una posición dada
    void insert(int pos, T e) override {
        if (pos < 0 || pos > n) {
            throw std::out_of_range("Posicion fuera de rango en insert()");
        }
        if (pos == 0) {
            first = new Node<T>(e, first);
        } else {
            Node<T>* current = first;
            for (int i = 0; i < pos - 1; ++i) {
                current = current->next;
            }
            current->next = new Node<T>(e, current->next);
        }
        n++;
    }

    // Eliminación en una posición dada
    T remove(int pos) override {
        if (pos < 0 || pos >= n) {
            throw std::out_of_range("Posicion fuera de rango en remove()");
        }
        T removed_val;
        if (pos == 0) {
            Node<T>* aux = first;
            first = first->next;
            removed_val = aux->data;
            delete aux;
        } else {
            Node<T>* current = first;
            for (int i = 0; i < pos - 1; ++i) {
                current = current->next;
            }
            Node<T>* aux = current->next;
            current->next = aux->next;
            removed_val = aux->data;
            delete aux;
        }
        n--;
        return removed_val;
    }

    // Obtener el elemento en una posición dada
    T get(int pos) const override {
        if (pos < 0 || pos >= n) {
            throw std::out_of_range("Posicion fuera de rango en get()");
        }
        Node<T>* current = first;
        for (int i = 0; i < pos; ++i) {
            current = current->next;
        }
        return current->data;
    }

    // Modificar el elemento en una posición dada
    void set(int pos, T e) override {
        if (pos < 0 || pos >= n) {
            throw std::out_of_range("Posicion fuera de rango en set()");
        }
        Node<T>* current = first;
        for (int i = 0; i < pos; ++i) {
            current = current->next;
        }
        current->data = e;
    }

    // Buscar la posición de un elemento
    int search(T e) const override {
        Node<T>* current = first;
        int idx = 0;
        while (current != nullptr) {
            if (current->data == e) {
                return idx;
            }
            current = current->next;
            idx++;
        }
        return -1;
    }

    // Comprobar si la lista está vacía
    bool empty() const override {
        return n == 0;
    }

    // Devolver el número de elementos
    int size() const override {
        return n;
    }

    // Sobrecarga del operador []
    T operator[](int pos) {
        if (pos < 0 || pos >= n) {
            throw std::out_of_range("Posicion fuera de rango en operator[]");
        }
        return get(pos);
    }

    // Sobrecarga global del operador <<
    friend std::ostream& operator<<(std::ostream &out, const ListLinked<T> &list) {
        out << "ListLinked [";
        Node<T>* current = list.first;
        while (current != nullptr) {
            out << current->data;
            if (current->next != nullptr) {
                out << ", ";
            }
            current = current->next;
        }
        out << "]";
        return out;
    }
};

#endif // LIST_LINKED_H
