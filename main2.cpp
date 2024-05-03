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
                int d=0;
                while(d<=3071){
                    offset = d % MAX_OFFSET;
                    tag = d >> (BITS_INDEX + BITS_OFFSET);
                    index = indexForm(d, MAX_OFFSET, MAX_INDEX);
                    miCache.Read(d,tag,index,offset);
                    cout << "porcentajeHits "<<miCache.getHitsPercentage()<<"%"<<endl;
                    cout << "porcentajemiss "<< miCache.getMissPercentage()<<"%"<<endl;
                    d++;
                };
                int f=0;
                while(f<=3071){
                    offset = f % MAX_OFFSET;
                    tag = f >> (BITS_INDEX + BITS_OFFSET);
                    index = indexForm(f, MAX_OFFSET, MAX_INDEX);
                    miCache.Write(f,tag,index,offset,'a');
                    cout << "porcentajeHits "<<miCache.getHitsPercentage()<<"%"<<endl;
                    cout << "porcentajemiss "<< miCache.getMissPercentage()<<"%"<<endl;
                    f++;
                };
             miCache.imprimirCache();
  
}