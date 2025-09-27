#include <iostream>
#include <fstream>
#include "archivos.h"

using namespace std;

char* leerArchivo(const char* nombre, long& tam) {
    ifstream file(nombre, ios::binary | ios::ate);
    if (!file.is_open()) {
        cout << "Error: no se pudo abrir " << nombre << endl;
        return nullptr;
    }
    tam = file.tellg();
    if (tam <= 0) {
        cout << "Archivo vacio: " << nombre << endl;
        file.close();
        return nullptr;
    }
    file.seekg(0, ios::beg);
    char* buffer = new char[tam + 1];
    file.read(buffer, tam);
    buffer[tam] = '\0';
    file.close();
    return buffer;
}

void escribirArchivo(const char* nombre, const char* datos) {
    ofstream file(nombre, ios::binary);
    if (!file.is_open()) {
        cout << "Error: no se pudo crear " << nombre << endl;
        return;
    }
    int i = 0;
    while (datos[i] != '\0') {
        file.put(datos[i]);
        i++;
    }
    file.close();
}
