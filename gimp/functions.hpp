#pragma once
#include <cstdint>

namespace pixel_functions {
extern const double e;

uint8_t negativ(uint8_t color);
uint8_t enlighten(uint8_t color, double a = 1.5);
uint8_t darken(uint8_t color, double a = 1.5);
uint8_t contrast(uint8_t color, double a = 0.062622429);
uint8_t decontrast(uint8_t color, double a = 100.0);
}