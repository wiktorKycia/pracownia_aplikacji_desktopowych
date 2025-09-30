#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>

using namespace std;

typedef short height_t; // tu deklarujemy jakiego typu ma być wysokość
typedef short terrain_t; // deklaracja typu wielkości terenu

// data (in meters)
constexpr terrain_t terrain_width = 5000, terrain_length = 4000; 
constexpr short step = 1; 
constexpr height_t min_height = 1200, max_height = 3500; 

int get_random_int(int a, int b);
height_t** create_2D_table(terrain_t size_x, terrain_t size_y);
double pythagorean(double a, double b);
double calculate_edge_length(double x1, double y1, double z1, double x2, double y2, double z2);
double calculate_triangle_area(double a, double b, double c);

int main()
{
    /*
    Dana jest tablica 2D zawierająca próbki wysokości terenu o wymiarach 5 x 4 (kilometry) na regularnej siatce z krokiem 1m. 
    Oblicz pole powierzchni terenu, zakładając, że zakres jego wysokości wynosi [1200, 3500] (metry). 
    Tablicę wygeneruj używając funkcji rand() (#incude <stdlib>) 
    */

    height_t **terrain = create_2D_table(terrain_width, terrain_length);

}


height_t get_random_int(height_t a, height_t b) // nie można dać &, bo nie przyjmie typu const
{
    height_t result = a + rand()%(b-a+1);
    return result;
}

height_t** create_2D_table(terrain_t size_x, terrain_t size_y)
{
    height_t **tab = new height_t*[size_y];

    for(terrain_t i = 0; i < size_y; i++)
    {
        tab[i] = new height_t[size_x];
    }

    for(terrain_t i = 0; i < size_y; i++)
    {
        for(terrain_t j = 0; j < size_x; j++)
        {
            tab[i][j] = get_random_int(min_height, max_height);
        }
    }
    return tab;
}

/*
a - length of side a (cathetus) przyprostokątna
b - length of side b (cathetus) przyprostokątna
a and b should be an absulute values
*/
double pythagorean(double a, double b)
{
    return (double)sqrt(pow(a, 2) + pow(b, 2));
}

double calculate_edge_length(double x1, double y1, double z1, double x2, double y2, double z2)
{
    double x_length = abs(x1-x2);
    double y_length = abs(y1-y2);
    double z_length = abs(z1-z2);

    double d1 = pythagorean(x_length, y_length);
    double d2 = pythagorean(z_length, d2);

    return d2;
}

/*
this function uses Heron formula
*/
double calculate_triangle_area(double a, double b, double c)
{
    double p = (a+b+c)/2;

    return sqrt(p*(p-a)*(p-b)*(p-c));
}