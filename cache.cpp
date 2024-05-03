#include "p2.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib> // Necesario para la función rand()
#include <ctime>   // Necesario para la función time()
void leerArchivoYCopiar(std::ifstream& archivo, char datos[], int inicio, int fin) {
    if (!archivo) {
        std::cerr << "No se pudo abrir el archivo." << std::endl;
    }
    int numLinea = 1; 
    int g=0;
    std::string linea;
    int flag=0;
    while (std::getline(archivo, linea)&&flag==0) {
        if (numLinea >= inicio && numLinea <= fin) {
            if (g<32){
            linea.copy(&datos[g], linea.size());
            }
            g++;
        }

        if (numLinea == fin) {
            flag=1;
        }

        numLinea++;
    }
    archivo.close();
};
void Cache::imprimirCache() {
    cout << "Contenido de la cache:" << endl;
    for (int i = 0; i < 2; ++i) {
        cout << "Via " << i << ":" << endl;
        for (int j = 0; j < 32; ++j) {
            cout << "  Bloque " << j << ":"<< "    v: " << Vias[i].Bloques[j].v << "    D: " << Vias[i].Bloques[j].D << "    tag: " << Vias[i].Bloques[j].tag << "    datos: ";
            for (int g = 0; g < 32;++g){
                    printf("%c|", Vias[i].Bloques[j].datos[g]);
            }
            printf("\n");
        }
    }
};

Cache::Cache() {
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 32; ++j) {
            for (int k = 0; k < 32; ++k) {
                Vias[i].Bloques[j].datos[k] = ' ';
            }
            Vias[i].Bloques[j].tag = -1;
            Vias[i].Bloques[j].v = 0;
            Vias[i].Bloques[j].D = 0;
        }
    }
    hits=0;
    misses=0;
};

int Cache::getHits() {
        return hits;
}

int Cache::getMisses() {
        return misses;
}

 void Cache::incrementHits() {
        hits++;
    }

    void Cache::incrementMisses() {
        misses++;
    }
double Cache::getMissPercentage() {
        int a = getHits();
        int b = getMisses();
        int totalOperations = a+b;
        if (totalOperations == 0) {
            return 0.0; // Evitar división por cero
        }
        return (static_cast<double>(b) / totalOperations) * 100.0;
    }

double Cache::getHitsPercentage() {
        int a = getHits();
        int b = getMisses();
        int totalOperations = a+b;
        if (totalOperations == 0) {
            return 0.0; // Evitar división por cero
        }
        return (static_cast<double>(a) / totalOperations) * 100.0;
    }
int original(int tag,int index) {
    int dir = (tag << 10) + (index << 5);
    std::cout << dir << std::endl;
    return dir;
}
void editarmem(char arreglito[],int inicio){
    int fin = inicio+31;
    // Abrir el archivo y leer cada línea en un vector
    ifstream archivo("dram.txt");
    vector<string> lineas;
    string linea;
    while (getline(archivo, linea)) {
        lineas.push_back(linea);
    }
    archivo.close();
        int z = 0;
        for (int i = inicio; i <= fin && i < lineas.size(); ++i) {
            // Modificar cada línea con el nuevo dato
            lineas[i] = arreglito[z];
            z++;
        }

        // Escribir el vector modificado de vuelta al archivo
        ofstream archivoSalida("dram.txt");
        if (archivoSalida.is_open()) {
            for (const string& linea : lineas) {
                archivoSalida << linea << endl;
            }
            archivoSalida.close();
        } else {
            cout << "No se pudo abrir el archivo para escribir." << endl;
        }
};
void Cache::Write(int num, int tag,int index,int offset,char cambio) {
    if (Vias[0].Bloques[index].tag==-1){
        printf("miss");
        incrementMisses();
        Vias[0].Bloques[index].tag=tag;
        Vias[0].Bloques[index].v=1;
        int rango1 = (num - (num %32))+1;
        int rango2 =  (rango1+31)+1;
        std::ifstream archivo("dram.txt");
        leerArchivoYCopiar(archivo, Vias[0].Bloques[index].datos, rango1, rango2);
        Vias[0].Bloques[index].D=1;
        Vias[0].Bloques[index].datos[offset]=cambio;

    }
    else if (Vias[0].Bloques[index].tag==tag){
        printf("hit");
        incrementHits();
        Vias[0].Bloques[index].D=1;
        Vias[0].Bloques[index].datos[offset]=cambio;
    }
    else if (Vias[1].Bloques[index].tag==-1){
        printf("miss");
        incrementMisses();
        Vias[1].Bloques[index].tag=tag;
        Vias[1].Bloques[index].v=1;
        int rango1 = (num - (num %32))+1;
        int rango2 =  (rango1+31)+1;
        std::ifstream archivo("dram.txt");
        leerArchivoYCopiar(archivo, Vias[1].Bloques[index].datos, rango1, rango2);
        Vias[1].Bloques[index].D=1;
        Vias[1].Bloques[index].datos[offset]=cambio;
    }
    else if (Vias[1].Bloques[index].tag==tag){
        printf("hit");
        incrementHits();
        Vias[1].Bloques[index].D=1;
        Vias[1].Bloques[index].datos[offset]=cambio;        
    }
    else{
        printf("miss");
        incrementMisses();
        srand(time(nullptr));
        int numero = rand() % 2;
            if (Vias[numero].Bloques[index].D==1){
                int inicio=original(Vias[numero].Bloques[index].tag,index);
                editarmem( Vias[numero].Bloques[index].datos,inicio);
                Vias[numero].Bloques[index].tag=tag;
                Vias[numero].Bloques[index].v=1;
                int rango1 = (num - (num %32))+1;
                int rango2 =  (rango1+31)+1;
                std::ifstream archivo("dram.txt");
                leerArchivoYCopiar(archivo, Vias[numero].Bloques[index].datos, rango1, rango2);
                Vias[numero].Bloques[index].D=1;
                Vias[numero].Bloques[index].datos[offset]=cambio;
            }
        else{
            Vias[numero].Bloques[index].tag=tag;
            Vias[numero].Bloques[index].v=1;
            int rango1 = (num - (num %32))+1;
            int rango2 =  (rango1+31)+1;
            std::ifstream archivo("dram.txt");
            leerArchivoYCopiar(archivo, Vias[numero].Bloques[index].datos, rango1, rango2);
            Vias[numero].Bloques[index].D=1;
            Vias[numero].Bloques[index].datos[offset]=cambio;
        }

    }
};
void Cache::Read(int num, int tag,int index,int offset){
    if (Vias[0].Bloques[index].tag==-1){
        printf("miss");
        printf("\n");
        incrementMisses();
        Vias[0].Bloques[index].tag=tag;
        Vias[0].Bloques[index].v=1;
        int rango1 = (num - (num %32))+1;
        int rango2 =  (rango1+31)+1;
        std::ifstream archivo("dram.txt");
        leerArchivoYCopiar(archivo, Vias[0].Bloques[index].datos, rango1, rango2);
        cout << "el dato es: " << Vias[0].Bloques[index].datos[offset]<<endl;

    }
    else if (Vias[0].Bloques[index].tag==tag){
        printf("hit");
        printf("\n");
        incrementHits();
        cout<< "el dato es: " << Vias[0].Bloques[index].datos[offset]<<endl;
    }
    else if (Vias[1].Bloques[index].tag==-1){
        printf("miss");
        printf("\n");
        incrementMisses();
        Vias[1].Bloques[index].tag=tag;
        Vias[1].Bloques[index].v=1;
        int rango1 = (num - (num %32))+1;
        int rango2 =  (rango1+31)+1;
        std::ifstream archivo("dram.txt");
        leerArchivoYCopiar(archivo, Vias[1].Bloques[index].datos, rango1, rango2);
        cout << "el dato es: " << Vias[1].Bloques[index].datos[offset]<<endl;
    }
    else if (Vias[1].Bloques[index].tag==tag){
        printf("hit");
        incrementHits();
        cout<< "el dato es" <<Vias[1].Bloques[index].datos[offset]<<endl;
    }
    else{
        printf("miss");
        incrementMisses();
        srand(time(nullptr));
        int numero = rand() % 2;
        if (Vias[numero].Bloques[index].D==1){
        int inicio=original(Vias[numero].Bloques[index].tag,index);
        editarmem( Vias[numero].Bloques[index].datos,inicio);
        Vias[numero].Bloques[index].tag=tag;
        Vias[numero].Bloques[index].v=1;
        int rango1 = (num - (num %32))+1;
        int rango2 =  (rango1+31)+1;
        std::ifstream archivo("dram.txt");
        leerArchivoYCopiar(archivo, Vias[numero].Bloques[index].datos, rango1, rango2);
        cout << "el dato es: " << Vias[numero].Bloques[index].datos[offset]<<endl;
        Vias[numero].Bloques[index].D=0;
        //reemplazo con dirty 1 (editar en memoria) hecho
        }
        else{
        Vias[numero].Bloques[index].tag=tag;
        Vias[numero].Bloques[index].v=1;
        int rango1 = (num - (num %32))+1;
        int rango2 =  (rango1+31)+1;
        std::ifstream archivo("dram.txt");
        leerArchivoYCopiar(archivo, Vias[numero].Bloques[index].datos, rango1, rango2);
        cout << "el dato es: " << Vias[numero].Bloques[index].datos[offset]<<endl;
        }

    }

};

