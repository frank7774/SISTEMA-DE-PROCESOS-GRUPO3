#ifndef PILA_MEMORIA_H
#define PILA_MEMORIA_H

#include <iostream>

struct BloqueMemoria {
    int idProceso;
    int tamanio; // KB
};

struct NodoPila {
    BloqueMemoria dato;
    NodoPila* siguiente;
};

class PilaMemoria {
private:
    NodoPila* tope;
public:
    PilaMemoria() : tope(0) {}
    
    void push(BloqueMemoria b) {
        NodoPila* nuevo = new NodoPila;
        nuevo->dato = b;
        nuevo->siguiente = tope;
        tope = nuevo;
    }
    
    BloqueMemoria pop() {
        if (!tope) {
            BloqueMemoria vacio;
            vacio.idProceso = -1;
            return vacio;
        }
        NodoPila* temp = tope;
        BloqueMemoria b = tope->dato;
        tope = tope->siguiente;
        delete temp;
        return b;
    }
    
    void mostrar() {
        if (!tope) {
            std::cout << "Pila vacía.\n";
            return;
        }
        NodoPila* actual = tope;
        int i = 1;
        while (actual) {
            std::cout << i++ << ". Proceso ID: " << actual->dato.idProceso
                      << " | Memoria: " << actual->dato.tamanio << " KB\n";
            actual = actual->siguiente;
        }
    }
    
    ~PilaMemoria() {
        while (tope) {
            NodoPila* temp = tope;
            tope = tope->siguiente;
            delete temp;
        }
    }
};

#endif

