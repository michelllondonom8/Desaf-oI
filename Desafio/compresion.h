#ifndef COMPRESION_H
#define COMPRESION_H
struct Datos {
    int numero;
    char letra;
};
char* descomprimir_rle(const char* comprimido);
Datos* convertirLZ78(const char* texto, int largo, int& cantidad);
char* descomprimir_lz78(Datos* arreglo, int cantidad);
char* descomprimir_rle_binario(const char* texto, int largo);
char* descomprimir_rle_binario16(const char* texto, int largo);
char* procesarCaso(int caso, char* encriptado, int largoEncriptado, char* pista, int largoPista);
#endif // COMPRESION_H
