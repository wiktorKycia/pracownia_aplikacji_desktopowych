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

int main()
{
    /*
    Dana jest tablica 2D zawierająca próbki wysokości terenu o wymiarach 5 x 4 (kilometry) na regularnej siatce z krokiem 1m. 
    Oblicz pole powierzchni terenu, zakładając, że zakres jego wysokości wynosi [1200, 3500] (metry). 
    Tablicę wygeneruj używając funkcji rand() (#incude <stdlib>) 
    */
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
*/
double pythagorean(int a, int b)
{
    return (double)sqrt(pow((double)abs(a), 2) + pow((double)abs(b), 2));
}