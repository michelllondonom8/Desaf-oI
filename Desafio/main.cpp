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
    int totalCasos;
    cout << "Cuantos archivos quieres evaluar?: ";
    cin >> totalCasos;

    for (int caso = 1; caso <= totalCasos; ++caso) {
        cout << "\n--- Procesando caso " << caso << " ---" << endl;

        char nombreEnc[64], nombrePista[64];
        sprintf(nombreEnc, "Encriptado%d.txt", caso);
        sprintf(nombrePista, "pista%d.txt", caso);

        int lenEnc = 0, lenPista = 0;
        char* enc = leerArchivo(nombreEnc, lenEnc);
        char* pista = leerArchivo(nombrePista, lenPista);

        if (!enc || !pista) {
            cout << "Error al leer archivos del caso " << caso << endl;
            if (enc) delete[] enc;
            if (pista) delete[] pista;
            continue;
        }

        char* resultado = procesarCaso(caso, enc, lenEnc, pista, lenPista);

        cout << "Texto final del caso " << caso << ":\n";
        if (resultado) {
            cout << resultado << endl;
            delete[] resultado;
        } else {
            cout << "No se pudo resolver el caso." << endl;
        }

        delete[] enc;
        delete[] pista;
    }
    return 0;
}
