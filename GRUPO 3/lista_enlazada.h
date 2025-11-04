#ifndef LISTA_ENLAZADA_H
#define LISTA_ENLAZADA_H

#include "proceso.h"
#include <iostream>
#include <cstring>
#include <cstdio>  // Para FILE, fopen, fread, fwrite, fseek, ftell

struct NodoLista {
    Proceso dato;
    NodoLista* siguiente;
};

class ListaEnlazada {
private:
    NodoLista* cabeza;
    int ultimoId;  // Almacena el ID más alto asignado

public:
    // Constructor: inicializa punteros y último ID en 0
    ListaEnlazada() : cabeza(0), ultimoId(0) {}

    // Inserta un proceso al inicio de la lista
    void insertar(Proceso p) {
        NodoLista* nuevo = new NodoLista;
        nuevo->dato = p;
        nuevo->siguiente = cabeza;
        cabeza = nuevo;
        if (p.id > ultimoId) {
            ultimoId = p.id;
        }
    }

    // Elimina un proceso por ID
    void eliminar(int id) {
        if (!cabeza) return;
        if (cabeza->dato.id == id) {
            NodoLista* temp = cabeza;
            cabeza = cabeza->siguiente;
            delete temp;
            return;
        }
        NodoLista* actual = cabeza;
        while (actual->siguiente && actual->siguiente->dato.id != id)
            actual = actual->siguiente;
        if (actual->siguiente) {
            NodoLista* temp = actual->siguiente;
            actual->siguiente = temp->siguiente;
            delete temp;
        }
    }

    // Busca un proceso por ID
    Proceso* buscar(int id) {
        NodoLista* actual = cabeza;
        while (actual) {
            if (actual->dato.id == id) return &(actual->dato);
            actual = actual->siguiente;
        }
        return 0;  // Equivalente a nullptr en C++98
    }

    // Busca un proceso por nombre
    Proceso* buscarPorNombre(const char* nombre) {
        NodoLista* actual = cabeza;
        while (actual) {
            if (strcmp(actual->dato.nombre, nombre) == 0)
                return &(actual->dato);
            actual = actual->siguiente;
        }
        return 0;
    }

    // Modifica la prioridad de un proceso
    void modificarPrioridad(int id, int nuevaPrioridad) {
        Proceso* p = buscar(id);
        if (p) p->prioridad = nuevaPrioridad;
    }

    // Muestra todos los procesos
    void mostrar() {
        NodoLista* actual = cabeza;
        if (!actual) {
            std::cout << "No hay procesos.\n";
            return;
        }
        while (actual) {
            std::cout << "ID: " << actual->dato.id
                      << " | Nombre: " << actual->dato.nombre
                      << " | Prioridad: " << actual->dato.prioridad
                      << " | Estado: " << actual->dato.estado
                      << " | Memoria: " << actual->dato.memoriaAsignada << " KB\n";
            actual = actual->siguiente;
        }
    }

    // Guarda el estado completo en un archivo binario
    void guardarEnArchivo(const char* archivo) {
        FILE* f = fopen(archivo, "wb");
        if (!f) return;

        // Primero: guardar el último ID
        fwrite(&ultimoId, sizeof(int), 1, f);

        // Luego: guardar todos los procesos
        NodoLista* actual = cabeza;
        while (actual) {
            fwrite(&(actual->dato), sizeof(Proceso), 1, f);
            actual = actual->siguiente;
        }
        fclose(f);
    }

    // Carga el estado desde un archivo binario (con verificación de tamaño)
    void cargarDeArchivo(const char* archivo) {
        FILE* f = fopen(archivo, "rb");
        if (!f) return;

        // Verificar que el archivo tenga al menos el tamaño de un 'int'
        fseek(f, 0, SEEK_END);
        long tam = ftell(f);
        fseek(f, 0, SEEK_SET);

        if (tam < (long)sizeof(int)) {
            fclose(f);
            return; // Archivo vacío o inválido ? no cargar nada
        }

        // Leer el último ID
        fread(&ultimoId, sizeof(int), 1, f);

        // Leer los procesos
        Proceso p;
        while (fread(&p, sizeof(Proceso), 1, f) == 1) {
            insertar(p);
        }
        fclose(f);
    }

    // Devuelve el último ID asignado (para continuar la numeración)
    int getUltimoId() const {
        return ultimoId;
    }

    // Destructor: libera toda la memoria dinámica
    ~ListaEnlazada() {
        while (cabeza) {
            NodoLista* temp = cabeza;
            cabeza = cabeza->siguiente;
            delete temp;
        }
    }
};

#endif

