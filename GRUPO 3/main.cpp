#include <iostream>
#include <cstring>
#include "proceso.h"
#include "lista_enlazada.h"
#include "cola_prioridad.h"
#include "pila_memoria.h"

using namespace std;

int main() {
    ListaEnlazada gestor;
    ColaPrioridad planificador;
    PilaMemoria memoria;
    const char* ARCHIVO = "estado.dat";

    // Cargar estado previo (incluye ultimoId)
    gestor.cargarDeArchivo(ARCHIVO);
    int idAuto = gestor.getUltimoId() + 1; // Continuar desde el último ID

    int opcion, id, prioridad, tamanio;
    char nombre[50];

    do {
        cout << "\n=== SISTEMA DE GESTION DE PROCESOS ===\n";
        cout << "1. Agregar proceso\n";
        cout << "2. Eliminar proceso\n";
        cout << "3. Buscar proceso por ID\n";
        cout << "4. Buscar proceso por nombre\n";
        cout << "5. Modificar prioridad\n";
        cout << "6. Enviar a cola de prioridad\n";
        cout << "7. Ejecutar siguiente proceso\n";
        cout << "8. Asignar memoria\n";
        cout << "9. Liberar memoria\n";
        cout << "10. Mostrar todos los procesos\n";
        cout << "11. Mostrar cola de prioridad\n";
        cout << "12. Mostrar pila de memoria\n";
        cout << "0. Salir y guardar\n";
        cout << "Opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1: {
                Proceso p;
                p.id = idAuto++;
                cout << "Nombre: "; cin >> p.nombre;
                cout << "Prioridad (1-10): "; cin >> p.prioridad;
                if (p.prioridad < 1) p.prioridad = 1;
                if (p.prioridad > 10) p.prioridad = 10;
                strcpy(p.estado, "listo");
                p.memoriaAsignada = 0;
                gestor.insertar(p);
                cout << "Proceso agregado con ID " << p.id << endl;
                break;
            }
            case 2:
                cout << "ID a eliminar: "; cin >> id;
                gestor.eliminar(id);
                cout << "Proceso eliminado (si existía).\n";
                break;
            case 3:
                cout << "ID: "; cin >> id;
                if (gestor.buscar(id))
                    cout << "Proceso encontrado.\n";
                else
                    cout << "No encontrado.\n";
                break;
            case 4:
                cout << "Nombre: "; cin >> nombre;
                if (gestor.buscarPorNombre(nombre))
                    cout << "Proceso encontrado.\n";
                else
                    cout << "No encontrado.\n";
                break;
            case 5:
                cout << "ID: "; cin >> id;
                cout << "Nueva prioridad: "; cin >> prioridad;
                gestor.modificarPrioridad(id, prioridad);
                cout << "Prioridad actualizada.\n";
                break;
            case 6:
                cout << "ID del proceso a encolar: "; cin >> id;
                {
                    Proceso* p = gestor.buscar(id);
                    if (p) {
                        planificador.encolar(*p);
                        cout << "Proceso '" << p->nombre << "' encolado por prioridad " << p->prioridad << ".\n";
                    } else cout << "Proceso no encontrado.\n";
                }
                break;
            case 7:
                {
                    Proceso p = planificador.desencolar();
                    if (p.id == -1) cout << "Cola vacía.\n";
                    else cout << "Ejecutando: " << p.nombre << " (Prioridad: " << p.prioridad << ")\n";
                }
                break;
            case 8:
                cout << "ID del proceso: "; cin >> id;
                cout << "Tamaño en KB: "; cin >> tamanio;
                {
                    BloqueMemoria b;
                    b.idProceso = id;
                    b.tamanio = tamanio;
                    memoria.push(b);
                    // Opcional: actualizar memoriaAsignada en el gestor
                    Proceso* p = gestor.buscar(id);
                    if (p) p->memoriaAsignada = tamanio;
                    cout << "Memoria asignada.\n";
                }
                break;
            case 9:
                {
                    BloqueMemoria b = memoria.pop();
                    if (b.idProceso == -1) cout << "Pila vacía.\n";
                    else cout << "Memoria liberada para proceso ID " << b.idProceso << "\n";
                }
                break;
            case 10: gestor.mostrar(); break;
            case 11: planificador.mostrar(); break;
            case 12: memoria.mostrar(); break;
            case 0:
                gestor.guardarEnArchivo(ARCHIVO);
                cout << "Estado guardado. ¡Adiós!\n";
                break;
            default:
                cout << "Opción inválida.\n";
        }
    } while (opcion != 0);

    return 0;
}

