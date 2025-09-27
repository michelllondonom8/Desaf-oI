#include "compresion.h"
#include <cstring>
#include <cctype>
#include <cstdint>
#include "encriptacion.h"
#include <iostream>

using namespace std;

char* descomprimir_rle(const char* comprimido) {
    if (!comprimido) return nullptr;

    int total = 0;
    for (int i = 0; comprimido[i] != '\0'; ) {
        int veces = 0;
        bool anyDigit = false;
        while (comprimido[i] != '\0' && comprimido[i] >= '0' && comprimido[i] <= '9') {
            anyDigit = true;
            veces = veces * 10 + (comprimido[i] - '0');
            i = i + 1;
        }
        if (!anyDigit) {
            return nullptr;
        }
        if (comprimido[i] == '\0') return nullptr; // falta letra
        i = i + 1;
        total = total + veces;
    }

    char* resultado = new char[total + 1];
    int pos = 0;
    for (int i = 0; comprimido[i] != '\0'; ) {
        int veces = 0;
        while (comprimido[i] != '\0' && comprimido[i] >= '0' && comprimido[i] <= '9') {
            veces = veces * 10 + (comprimido[i] - '0');
            i = i + 1;
        }
        if (comprimido[i] == '\0') break;
        char letra = comprimido[i];
        i = i + 1;
        for (int j = 0; j < veces; j = j + 1) {
            resultado[pos] = letra;
            pos = pos + 1;
        }
    }
    resultado[pos] = '\0';
    return resultado;
}

Datos* convertirLZ78(const char* texto, int largo, int& cantidad) {
    if (!texto || largo <= 0 || (largo % 3) != 0) {
        cantidad = 0;
        return nullptr;
    }

    cantidad = largo / 3;
    Datos* arreglo = new Datos[cantidad];

    for (int i = 0; i < cantidad; i = i + 1) {
        unsigned char hi = (unsigned char) texto[i*3];
        unsigned char lo = (unsigned char) texto[i*3 + 1];
        arreglo[i].numero = (hi << 8) | lo;
        arreglo[i].letra = texto[i*3 + 2];
    }
    return arreglo;
}

char* descomprimir_lz78(Datos* arreglo, int cantidad) {
    if (!arreglo || cantidad <= 0) return nullptr;

    char** diccionario = new char*[cantidad + 1];
    diccionario[0] = new char[1];
    diccionario[0][0] = '\0';

    int total = 0;
    for (int i = 0; i < cantidad; i = i + 1) {
        int idx = arreglo[i].numero;
        char letra = arreglo[i].letra;

        if (idx < 0 || idx > i) {
            for (int k = 0; k <= i; k = k + 1) delete[] diccionario[k];
            delete[] diccionario;
            return nullptr;
        }

        int largo_prefijo = 0;
        while (diccionario[idx][largo_prefijo] != '\0') largo_prefijo = largo_prefijo + 1;

        char* palabra = new char[largo_prefijo + 2]; // prefijo + letra + '\0'
        for (int j = 0; j < largo_prefijo; j = j + 1) palabra[j] = diccionario[idx][j];
        palabra[largo_prefijo] = letra;
        palabra[largo_prefijo + 1] = '\0';

        diccionario[i + 1] = palabra;
        total = total + (largo_prefijo + 1);
    }

    char* salida = new char[total + 1];
    int pos = 0;
    for (int i = 0; i < cantidad; i = i + 1) {
        int idx = arreglo[i].numero;
        if (idx < 0 || idx > cantidad) {
            for (int k = 0; k <= cantidad; k = k + 1) delete[] diccionario[k];
            delete[] diccionario;
            delete[] salida;
            return nullptr;
        }

        int j = 0;
        while (diccionario[idx][j] != '\0') {
            salida[pos] = diccionario[idx][j];
            pos = pos + 1;
            j = j + 1;
        }
        salida[pos] = arreglo[i].letra;
        pos = pos + 1;
    }
    salida[pos] = '\0';

    for (int i = 0; i <= cantidad; i = i + 1) {
        delete[] diccionario[i];
    }
    delete[] diccionario;

    return salida;
}

char* descomprimir_rle_binario(const char* texto, int largo) {
    if (!texto || largo <= 0 || (largo % 2) != 0) return nullptr;

    int tamano = 0;
    for (int i = 0; i < largo; i = i + 2) {
        unsigned char count = (unsigned char) texto[i];
        if (count == 0) return nullptr;
        tamano = tamano + count;

        if (tamano > 50 * 1024 * 1024) {
            return nullptr;
        }
    }

    char* salida = new char[tamano + 1];
    int k = 0;

    for (int i = 0; i < largo; i = i + 2) {
        unsigned char count = (unsigned char) texto[i];
        char c = texto[i + 1];
        for (int j = 0; j < count; j = j + 1) {
            salida[k] = c;
            k = k + 1;
        }
    }

    salida[k] = '\0';
    return salida;
}

char* descomprimir_rle_binario16(const char* texto, int largo) {
    if (largo % 3 != 0) return nullptr;

    int tamano = 0;
    for (int i = 0; i < largo; i = i + 3) {
        unsigned char hi = (unsigned char)texto[i];
        unsigned char lo = (unsigned char)texto[i+1];
        int count = (hi << 8) | lo;
        tamano = tamano + count;
    }

    char* salida = new char[tamano + 1];
    int k = 0;

    for (int i = 0; i < largo; i = i + 3) {
        unsigned char hi = (unsigned char)texto[i];
        unsigned char lo = (unsigned char)texto[i+1];
        int count = (hi << 8) | lo;
        char c = texto[i+2];

        for (int j = 0; j < count; j = j + 1) {
            salida[k] = c;
            k = k + 1;
        }
    }

    salida[k] = '\0';
    return salida;
}

char *procesarCaso(int caso, char *encriptado, int largoEncriptado, char *pista, int largoPista)
{
    bool encontrado = false;
    char* textoFinal = nullptr;

    unsigned int rotaciones[] = {1, 2, 3, 4, 5, 6, 7};
    unsigned int claves[] = {199, 143, 87, 90, 64};

    for (unsigned int r = 0; r < sizeof(rotaciones)/sizeof(rotaciones[0]) && !encontrado; ++r) {
        for (unsigned int k = 0; k < sizeof(claves)/sizeof(claves[0]) && !encontrado; ++k) {
            unsigned int rot = rotaciones[r];
            unsigned int K = claves[k];

            char* copia = new char[largoEncriptado + 1];
            memcpy(copia, encriptado, largoEncriptado);
            copia[largoEncriptado] = '\0';

            procesar_mensaje((uint8_t*)copia, largoEncriptado, (uint8_t)K, true, rot);

            //  Probar RLE binario 16
            if (!encontrado && (largoEncriptado % 3 == 0)) {
                char* salida = descomprimir_rle_binario16(copia, largoEncriptado);
                if (salida && strstr(salida, pista)) {
                    cout << "Metodo: RLE (binario16)" << endl;
                    textoFinal = salida;
                    encontrado = true;
                } else if (salida) delete[] salida;
            }

            //  Probar LZ78
            if (!encontrado && (largoEncriptado % 3 == 0)) {
                int cantidad = 0;
                Datos* comp = convertirLZ78(copia, largoEncriptado, cantidad);
                if (comp) {
                    char* salidaLZ = descomprimir_lz78(comp, cantidad);
                    if (salidaLZ && strstr(salidaLZ, pista)) {
                        cout << "Metodo: LZ78" << endl;
                        textoFinal = salidaLZ;
                        encontrado = true;
                    } else if (salidaLZ) delete[] salidaLZ;
                    delete[] comp;
                }
            }

            delete[] copia;
        }
    }

    if (!encontrado)
        cout << "No se pudo desencriptar el caso." << endl;

    return textoFinal;
}
