#ifndef PROCESO_H
#define PROCESO_H

struct Proceso {
    int id;
    char nombre[50];
    int prioridad; // 1 = más alta, 10 = más baja
    char estado[20]; // "listo", "ejecutando", etc.
    int memoriaAsignada; // en KB
};

#endif


