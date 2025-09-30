#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;


int losuj(int a, int b)
{
    int result = a + rand()%(b-a+1);
    return result;
}

double losuj(double a, double b)
{
    double result = a + (double)rand()/RAND_MAX * (b - a);
    return result;
}


void wyswietl_przekroj(int **tab, int &rozmiar_x, int &rozmiar_y)
{

    for(int y = 0; y < rozmiar_y; y++)
    {
        for(int x = 0; x < rozmiar_x; x++)
        {
            cout << tab[y][x] << " ";
        }
        cout << endl;
    }

}

int sumuj_przekroj(int **tab, int &rozmiar_x, int &rozmiar_y)
{
    int suma = 0;
    for(int y = 0; y < rozmiar_y; y++)
    {
        for(int x = 0; x < rozmiar_x; x++)
        {
            suma += tab[y][x];
        }
    }
    return suma;
}

double srednia_przekroju(int &suma_przekroju, int &rozmiar_x, int &rozmiar_y)
{
    return (double)(suma_przekroju / (rozmiar_x * rozmiar_y)); 
}

constexpr int dlugosc = 50, szerokosc = 40, wysokosc = 27;
constexpr short min_temp = 18, max_temp = 25;

int main()
{
    srand(time(NULL));
    setlocale(LC_ALL, "pl_PL.UTF-8");
    /*
    Dana jest tablica 3D zawierająca próbki temperatury pobrane w pokoju o wymiarach 5 x 4 x 2.7 (metry) na regularnej siatce z krokiem 10cm. 
    Znajdź przekrój pionowy pokoju z największą średnią temperaturą. 
    Załóż, że zakres temperatury w pokoju to [18,25] stopni. 
    Tablicę wygeneruj używając funkcji rand() (#incude <stdlib>)
    */

    int ***pokoj;

    pokoj = new int**[dlugosc];

    for(int x = 0; x < dlugosc; x++)
    {
        pokoj[x] = new int*[szerokosc];
        
        for(int y = 0; y < szerokosc; y++)
        {
            pokoj[x][y] = new int[wysokosc];

            for (int z = 0; z < wysokosc; z++)
            {
                pokoj[x][y][z] = {losuj(min_temp, max_temp)};
            }
        } 
    }

    int dl = dlugosc;
    int szer = szerokosc;
    int wys = wysokosc;
    double najw_srednia = 0;
    int idx_najw_sredniej{};

    for(int i = 0; i < dl; i++)
    {
        int suma_i = sumuj_przekroj(pokoj[i], wys, szer);
        double srednia_i = srednia_przekroju(suma_i, wys, szer);

        if (najw_srednia < srednia_i)
        {
            najw_srednia = srednia_i;
        }
        cout << srednia_i << endl;
    }
    cout << "Największa średnia to: " << najw_srednia << endl;
    wyswietl_przekroj(pokoj[idx_najw_sredniej], wys, szer);



    return 0;
}