#ifndef ENCRIPTACION_H
#define ENCRIPTACION_H
#include <cstdint>

class Encriptacion
{
public:
    Encriptacion();
    uint8_t rotate_left_byte(uint8_t b, unsigned int n);
};

#endif // ENCRIPTACION_H
