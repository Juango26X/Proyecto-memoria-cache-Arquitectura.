#include <iostream>
using namespace std;
 
class Bloque {
    public:
    int v;
    int D;
    int tag;
    char datos[32];
};

class Via {
    public:
    Bloque Bloques[32];
};

class Cache {
    private:
    int hits;
    int misses;
    public:
    Via Vias[2];
    void imprimirCache();
    Cache();
    void Write(int num, int tag,int index,int offset,char cambio);
    void Read(int num, int tag,int index,int offset);
    int getHits();
    int getMisses();
     void incrementHits();
    void incrementMisses();
    double getMissPercentage();
    double getHitsPercentage();

};