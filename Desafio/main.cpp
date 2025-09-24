#include <iostream>
#include <fstream>
#include "encriptacion.h"
#include "compresion.h"

using namespace std;

char* leerArchivo(const char* nombreArchivo, int& largo) {
    FILE* archivo = fopen(nombreArchivo, "r");
    if (archivo == NULL) {
        cout << "No se pudo abrir el archivo." << endl;
        return NULL;
    }

    fseek(archivo, 0, SEEK_END);
    largo = ftell(archivo);
    rewind(archivo);

    char* contenido = new char[largo + 1];

    fread(contenido, 1, largo, archivo);
    contenido[largo] = '\0';
    fclose(archivo);

    return contenido;
}
int main()
{
    return 0;
}
