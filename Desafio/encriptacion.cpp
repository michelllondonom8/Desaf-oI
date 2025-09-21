#include "encriptacion.h"

Encriptacion::Encriptacion() {}

uint8_t Encriptacion::rotate_left_byte(uint8_t b, unsigned int n)
{
    n &= 7u;

    if (n == 0) return b;



    unsigned int tmp = (unsigned int)b;


    unsigned int res = ((tmp << n) | (tmp >> (8 - n))) & 0xFFu;


    return (uint8_t)res;
}
