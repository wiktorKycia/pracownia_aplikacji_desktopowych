#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

constexpr int width = 50, length = 40, height = 27;
constexpr short min_temp = 18, max_temp = 25;

int*** create_3D_table(int _size_x, int _size_y, int _size_z);
void print_3D_table(int*** tab, int _size_x, int _size_y, int _size_z);

int randomize(int &a, int &b);
double randomize(double &a, double &b);
void print_2D_table(int **tab, int &_size_x, int &_size_y);
double get_average_from_2D_table(int **tab, int &_size_x, int &_size_y)

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
    int size_x = width;
    int size_y = length;
    int size_z = height;

    int ***pokoj = create_3D_table(size_x, size_y, size_z);

    double najw_srednia = 0;
    int idx_najw_sredniej{};

    for(int i = 0; i < dl; i++)
    {
        int suma_i = 
        double srednia_i = get_average_from_2D_table(pokoj[i], wys, szer);

        if (najw_srednia < srednia_i)
        {
            najw_srednia = srednia_i;
        }
        cout << srednia_i << endl;
    }
    cout << "Największa średnia to: " << najw_srednia << endl;
    print_2D_table(pokoj[idx_najw_sredniej], wys, szer);



    return 0;
}

void print_3D_table(int*** tab, int _size_x, int _size_y, int _size_z)
{
    for (int i = 0; i < _size_z; i++)
    {
        cout << "Warstwa " << i << ": "<< endl << endl;
        for(int j = 0; j < _size_y; j++)
        {
            for(int k = 0; k < _size_x; k++)
            {
                cout << tab[i][j][k] << " ";
            }
            cout << endl;
        }
    }
}


/*
x = width
y = length
z = height, iteracja po z: plastry poziome
*/
int*** create_3D_table(int _size_x, int _size_y, int _size_z)
{
    // tablica 3D jako tablica tablic 2-wymiarowych
    int*** tab = new int**[_size_z]; // alokacja adresów dla plastrów (poziomych)

    // alokacja pamięci dla pionowych rzędów (w głąb)
    for(int i = 0; i < _size_z; i++)
    {
        tab[i] = new int*[_size_y];

        for(int j = 0; j < _size_y; j++)
        {
            tab[i][j] = new int[_size_x];
        }
    }

    for(int i = 0; i < _size_z; i++)
    {
        for(int j = 0; j < _size_y; j++)
        {
            for(int k = 0; k < _size_x; k++)
            {
                tab[i][j][k] = randomize(min_temp, max_temp);
            }
        }
    }

    return tab;
}

int randomize(int &a, int &b)
{
    int result = a + rand()%(b-a+1);
    return result;
}

double randomize(double &a, double &b)
{
    double result = a + (double)rand()/RAND_MAX * (b - a);
    return result;
}


void print_2D_table(int **tab, int &_size_x, int &_size_y)
{
    for(int j = 0; j < _size_y; j++)
    {
        for(int k = 0; k < _size_x; k++)
        {
            cout << tab[j][k] << " ";
        }
        cout << endl;
    }
}

double get_average_from_2D_table(int **tab, int &_size_x, int &_size_y)
{
    int suma = 0;
    for(int j = 0; j < _size_y; j++)
    {
        for(int k = 0; k < _size_x; k++)
        {
            suma += tab[j][k];
        }
    }
    return (double)(suma/(_size_x * _size_y));
}

