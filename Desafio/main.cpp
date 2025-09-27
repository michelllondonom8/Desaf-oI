#include <iostream>
#include <cstdio>
#include <cstring>
#include <cctype>
#include <cstdint>
#include "encriptacion.h"
#include "compresion.h"

using namespace std;

int my_min(int a, int b) { return (a < b) ? a : b; }

char* leerArchivo(const char* nombreArchivo, int& largo) {
    FILE* archivo = fopen(nombreArchivo, "rb");
    if (!archivo) {
        cout << "No se pudo abrir el archivo: " << nombreArchivo << endl;
        largo = 0;
        return NULL;
    }
    fseek(archivo, 0, SEEK_END);
    long t = ftell(archivo);
    if (t < 0) { fclose(archivo); largo = 0; return NULL; }
    largo = (int)t;
    rewind(archivo);

    char* contenido = new char[largo + 1];
    size_t leidos = fread(contenido, 1, largo, archivo);
    contenido[leidos] = '\0';
    fclose(archivo);
    return contenido;
}
int main() {
    return 0;
}
