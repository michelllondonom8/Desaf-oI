#include "encriptacion.h"

Encriptacion::Encriptacion() {}

uint8_t Encriptacion::rotate_left_byte(uint8_t b, unsigned int n)
{
    n = n % 8;
    if (n != 0) {
        uint16_t tmp = b;
        return (uint8_t)(((tmp << n) | (tmp >> (8 - n))) & 0xFF);
    }
    return b;
}

uint8_t Encriptacion::rotate_right_byte(uint8_t b, unsigned int n)
{
    n = n % 8;
    if (n != 0) {
        uint16_t tmp = b;
        return (uint8_t)(((tmp >> n) | (tmp << (8 - n))) & 0xFF);
    }
    return b;
}

uint8_t Encriptacion::aplicar_clave(uint8_t b, uint8_t key)
{
    return b ^ key;
}

void Encriptacion::procesar_mensaje(uint8_t *mensaje, int longitud, uint8_t key, bool rotar_izq, unsigned int n)
{
    for (int i = 0; i < longitud; i= i+1) {
        uint8_t b = mensaje[i]; // aqui agarro el byte actual

        // primero se rota, segun lo que digamos
        if (rotar_izq) {
            b = rotate_left_byte(b, n);
        } else {
            b = rotate_right_byte(b, n);
        }

        // despues de rotar se aplica la clave con XOR
        b = aplicar_clave(b, key);

        // guardo el resultado otra vez en el mensaje
        mensaje[i] = b;
    }
}
