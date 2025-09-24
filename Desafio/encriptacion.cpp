#include "encriptacion.h"

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

void procesar_mensaje(uint8_t *mensaje, int largo, uint8_t clave, bool hacia_izq, unsigned int pasos)
{
    for (int i = 0; i < largo; i= i+1) {
        uint8_t byte = mensaje[i]; // aqui agarro el byte actual

        // primero se rota, segun lo que digamos
        if (hacia_izq) {
            byte = rotar_izquierda(byte, pasos);
        } else {
            byte = rotar_derecha(byte, pasos);
        }

        // despues de rotar se aplica la clave con XOR
        byte = aplicar_clave(byte, clave);

        // guardo el resultado otra vez en el mensaje
        mensaje[i] = byte;
    }
}
