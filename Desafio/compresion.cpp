#include "compresion.h"

char* descomprimir_rle(const char* comprimido) {

    int total = 0;
    for (int i = 0; comprimido[i] != '\0'; i = i + 2) {
        char letra = comprimido[i];
        int veces = comprimido[i + 1] - '0';
        total = total + veces;
    }

    char* resultado = new char[total + 1];
    int pos = 0;

    for (int i = 0; comprimido[i] != '\0'; i = i + 2) {
        char letra = comprimido[i];
        int veces = comprimido[i + 1] - '0';
        for (int j = 0; j < veces; j = j + 1) {
            resultado[pos] = letra;
            pos = pos + 1;
        }
    }

    resultado[pos] = '\0';
    return resultado;
}
Datos* convertirLZ78(const char* texto, int& cantidad) {
    int tam = 0;
    for (int i = 0; texto[i] != '\0'; i = i + 1) {
        if (texto[i] < '0' || texto[i] > '9') {
            tam = tam + 1;
        }
    }

    Datos* arreglo = new Datos[tam];
    cantidad = 0;

    int i = 0;
    while (texto[i] != '\0') {
        int num = 0;
        while (texto[i] >= '0' && texto[i] <= '9') {
            num = num * 10 + (texto[i] - '0');
            i = i + 1;
        }
        if (texto[i] != '\0') {
            arreglo[cantidad].numero = num;
            arreglo[cantidad].letra = texto[i];
            cantidad = cantidad + 1;
            i = i + 1;
        }
    }

    return arreglo;
}

char* descomprimir_lz78(Datos* arreglo, int cantidad) {
    char** diccionario = new char*[cantidad + 1];
    diccionario[0] = new char[1];
    diccionario[0][0] = '\0';

    int total = 0;
    for (int i = 0; i < cantidad; i = i + 1) {
        int idx = arreglo[i].numero;
        char letra = arreglo[i].letra;

        int largo = 0;
        while (diccionario[idx][largo] != '\0') {
            largo = largo + 1;
        }

        char* palabra = new char[largo + 2];
        for (int j = 0; j < largo; j = j + 1) {
            palabra[j] = diccionario[idx][j];
        }
        palabra[largo] = letra;
        palabra[largo + 1] = '\0';

        diccionario[i + 1] = palabra;
        total = total + largo + 1;
    }

    char* salida = new char[total + 1];
    int pos = 0;

    for (int i = 0; i < cantidad; i = i + 1) {
        int j = 0;
        while (diccionario[arreglo[i].numero][j] != '\0') {
            salida[pos] = diccionario[arreglo[i].numero][j];
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
