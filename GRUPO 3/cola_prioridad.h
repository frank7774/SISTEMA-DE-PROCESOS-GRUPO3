#ifndef COLA_PRIORIDAD_H
#define COLA_PRIORIDAD_H

#include "proceso.h"
#include <iostream>

struct NodoCola {
    Proceso dato;
    NodoCola* siguiente;
};

class ColaPrioridad {
private:	
    NodoCola* frente;
public:
    ColaPrioridad() : frente(0) {}
    
    void encolar(Proceso p) {
        NodoCola* nuevo = new NodoCola;
        nuevo->dato = p;
        nuevo->siguiente = 0;
        if (!frente || p.prioridad < frente->dato.prioridad) {
            nuevo->siguiente = frente;
            frente = nuevo;
        } else {
            NodoCola* actual = frente;
            while (actual->siguiente && actual->siguiente->dato.prioridad <= p.prioridad)
                actual = actual->siguiente;
            nuevo->siguiente = actual->siguiente;
            actual->siguiente = nuevo;
        }
    }
    
    Proceso desencolar() {
        if (!frente) {
            Proceso vacio;
            vacio.id = -1;
            return vacio;
        }
        NodoCola* temp = frente;
        Proceso p = frente->dato;
        frente = frente->siguiente;
        delete temp;
        return p;
    }
    
    void mostrar() {
        if (!frente) {
            std::cout << "Cola vacía.\n";
            return;
        }
        NodoCola* actual = frente;
        int i = 1;
        while (actual) {
            std::cout << i++ << ". " << actual->dato.nombre
                      << " (Prioridad: " << actual->dato.prioridad << ")\n";
            actual = actual->siguiente;
        }
    }
    
    ~ColaPrioridad() {
        while (frente) {
            NodoCola* temp = frente;
            frente = frente->siguiente;
            delete temp;
        }
    }
};

#endif

