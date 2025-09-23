#ifndef ENCRIPTACION_H
#define ENCRIPTACION_H
#include <cstdint>

class Encriptacion
{
public:
    Encriptacion();
    uint8_t rotate_left_byte(uint8_t b, unsigned int n);
    uint8_t rotate_right_byte(uint8_t b, unsigned int n);
    uint8_t aplicar_clave(uint8_t b, uint8_t key);
    void procesar_mensaje(uint8_t* mensaje, int longitud, uint8_t key, bool rotar_izq, unsigned int n);
};

#endif // ENCRIPTACION_H
