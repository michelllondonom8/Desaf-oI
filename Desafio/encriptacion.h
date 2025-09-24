#ifndef ENCRIPTACION_H
#define ENCRIPTACION_H
#include <cstdint>

uint8_t rotar_izquierda(uint8_t b, unsigned int pasos);
uint8_t rotar_derecha(uint8_t b, unsigned int pasos);
uint8_t aplicar_clave(uint8_t b, uint8_t clave);
void procesar_mensaje(uint8_t* mensaje, int largo, uint8_t clave, bool hacia_izq, unsigned int pasos);

#endif // ENCRIPTACION_H
