#ifndef COMPRESION_H
#define COMPRESION_H
struct Datos {
    int numero;
    char letra;
};
char* descomprimir_rle(const char* comprimido);
Datos* convertirLZ78(const char* texto, int& cantidad);
char* descomprimir_lz78(Datos* arreglo, int cantidad);


#endif // COMPRESION_H
