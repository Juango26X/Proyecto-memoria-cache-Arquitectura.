#include "p2.h"
#include <cstring>
#include <cmath>
#include <iostream>
int indexForm(int dir, int MAX_OFFSET, int MAX_INDEX) {
    // Obtener el piso de la división y convertirlo a un entero
    int piso = static_cast<int>(std::floor(static_cast<double>(dir) / MAX_OFFSET));
    // Calcular el módulo con respecto a MAX_INDEX
    return piso % MAX_INDEX;
}
using namespace std;

void mostrarMenu() {
    cout << "Menu:" << endl;
    cout << " ingresa 1 si deseas hacer lectura" << endl;
    cout << "ingresa 2 si deseas hacer escritura" << endl;
    cout << "ingresa 3 si deseas imprimir la cache en pantalla" << endl;
    cout << "ingresa 4 si deseas Salir" << endl;
    cout << "Seleccione una opcion: ";
}


int main() {
  
  int dir = 0;
  int MAX_INDEX = 32;
  int MAX_OFFSET = 32;
  int BITS_INDEX = 5;
  int BITS_OFFSET = 5;
  int opcion;
  int offset;
  int tag;
  int index;
  Cache miCache;
   while (true) {
        mostrarMenu();
        cin >> opcion;

        switch (opcion) {
            case 1:
                cout << "ingresa posicion a leer" << endl;
                std::cin >> dir;
                if(dir <= 3071) {
                offset = dir % MAX_OFFSET;
                tag = dir >> (BITS_INDEX + BITS_OFFSET);
                index = indexForm(dir, MAX_OFFSET, MAX_INDEX);
                miCache.Read(dir,tag,index,offset);
                cout << "porcentajeHits "<<miCache.getHitsPercentage()<<"%"<<endl;
                cout << "porcentajemiss "<< miCache.getMissPercentage()<<"%"<<endl;
                }
                break;
            case 2:
                cout << "ingre posición escritura" << endl;
                std::cin >> dir;
                if(dir <= 3071) {
                offset = dir % MAX_OFFSET;
                tag = dir >> (BITS_INDEX + BITS_OFFSET);
                index = indexForm(dir, MAX_OFFSET, MAX_INDEX);
                char cambio;
                cout << "ingre dato que quiere poner" << endl;
                std::cin >> cambio;
                miCache.Write(dir,tag,index,offset,cambio);
                cout << "porcentajeHits "<<miCache.getHitsPercentage()<<"%"<<endl;
                cout << "porcentajemiss "<< miCache.getMissPercentage()<<"%"<<endl;
                }
                break;
            case 3:
                cout << "imprimir cache" << endl;
                miCache.imprimirCache();
                break;
            case 4:
                cout << "Saliendo del programa..." << endl;
                return 0;
            default:
                cout << "Opción no válida. Por favor, seleccione una opcion válida." << endl;
                break;
        }
    }
  
}