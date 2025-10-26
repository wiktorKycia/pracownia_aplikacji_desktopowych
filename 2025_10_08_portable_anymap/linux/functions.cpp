#include "functions.hpp"
#include <cmath>
#include <cstdint>

namespace pixel_functions
{

const double e = std::exp(1.0);

uint8_t negativ(uint8_t color)
{
    return 255-color;
}

uint8_t enlighten(uint8_t color, double a)
{
    return static_cast<uint8_t>(round(255.0 * pow(color / 255.0, (1.0 / a))));
}

uint8_t darken(uint8_t color, double a)
{
    return static_cast<uint8_t>(round(255.0 * pow(color / 255.0, a)));
}

uint8_t contrast(uint8_t color, double a)//(1/sqrt(255)))
{
    return static_cast<uint8_t>(round(255.0 * (1.0 / (1.0 + pow(e, -a * (color - 127.5))))));
}

uint8_t decontrast(uint8_t color, double a)
{
    double b = atan(127.5 / a) / 127.5;
    return static_cast<uint8_t>(round(a * tan(b * (color - 127.5)) + 127.5));
}

}