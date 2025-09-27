#include "encriptacion.h"
#include <cstdint>

uint8_t rotar_izquierda(uint8_t byte, unsigned int pasos)
{
    pasos = pasos % 8;
    if (pasos != 0) {
        uint16_t temp = byte;
        return (uint8_t)(((temp << pasos) | (temp >> (8 - pasos))) & 0xFF);
    }
    return byte;
}

uint8_t rotar_derecha(uint8_t byte, unsigned int pasos)
{
    pasos = pasos % 8;
    if (pasos != 0) {
        uint16_t temp = byte;
        return (uint8_t)(((temp >> pasos) | (temp << (8 - pasos))) & 0xFF);
    }
    return byte;
}

uint8_t aplicar_clave(uint8_t byte, uint8_t clave)
{
    return byte ^ clave;
}

void procesar_mensaje(uint8_t *mensaje, int largo, uint8_t clave, bool desencriptar, unsigned int pasos) {
    for (int i = 0; i < largo; i= i + 1) {
        uint8_t byte = mensaje[i];
        if (desencriptar) {
            byte =byte ^ clave;
            byte = rotar_derecha(byte, pasos);
        } else {
            byte = rotar_izquierda(byte, pasos);
            byte = byte ^ clave;
        }
        mensaje[i] = byte;
    }
}

