#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

constexpr int width = 50, length = 40, height = 27;
constexpr short min_temp = 18, max_temp = 25;

int*** create_3D_table(int _size_x, int _size_y, int _size_z);
void print_3D_table(int*** tab, int _size_x, int _size_y, int _size_z);

int get_random_int(int a, int b);
double get_random_double(double a, double b);
void print_2D_table(int **tab, int &_size_x, int &_size_y);
double get_average_from_2D_table(int **tab, int &_size_x, int &_size_y);
int** extract_2D_section_1(int*** tab, int x, int &_size_y, int &_size_z);
int** extract_2D_section_2(int*** tab, int y, int &_size_x, int &_size_z);
int** allocate_2D_table(int &_size_x, int &_size_y);

int main()
{
    srand(time(NULL));
    setlocale(LC_ALL, "pl_PL.UTF-8");
    /*
    Dana jest tablica 3D zawierająca próbki temperatury pobrane w pokoju o wymiarach 5 x 4 x 2.7 (metry)
     na regularnej siatce z krokiem 10cm. 
    Znajdź przekrój pionowy pokoju z największą średnią temperaturą. 
    Załóż, że zakres temperatury w pokoju to [18,25] stopni. 
    Tablicę wygeneruj używając funkcji rand() (#incude <stdlib>)
    */
    int size_x = width;
    int size_y = length;
    int size_z = height;

    int ***room = create_3D_table(size_x, size_y, size_z);

    double biggest_avg = 0;
    int idx_of_biggest_avg{};
    bool is_avg_for_x = true;


    // najpierw iteracja po x-ach, czyli szukanie przekroju "wgłąb"
    for(int i = 0; i < width; i++)
    {
        int **arr = extract_2D_section_1(room, i, size_y, size_z);
        double avg_for_i = get_average_from_2D_table(arr, size_y, size_z);

        if (biggest_avg < avg_for_i)
        {
            biggest_avg = avg_for_i;
            idx_of_biggest_avg = i;
        }
    }

    // teraz iteracja po y-kach, czyli szukanie przekroju "wskroś" (warstwami ściennymi)
    for(int i = 0; i < length; i++)
    {
        int **arr = extract_2D_section_2(room, i, size_x, size_z);
        double avg_for_i = get_average_from_2D_table(arr, size_x, size_z);

        if (biggest_avg < avg_for_i)
        {
            biggest_avg = avg_for_i;
            idx_of_biggest_avg = i;
            is_avg_for_x = false;
        }
    }

    cout << "Największa średnia temperratura to: " << biggest_avg << endl;
    cout << "Przekrój z największą średnią temperaturą to: " << endl;

    if(is_avg_for_x)
    {
        int **arr = extract_2D_section_1(room, biggest_avg, size_y, size_z);
        print_2D_table(arr, size_y, size_z);
    }
    else
    {
        int **arr = extract_2D_section_2(room, biggest_avg, size_x, size_z);
        print_2D_table(arr, size_x, size_z);
    }

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
                tab[i][j][k] = get_random_int(min_temp, max_temp);
            }
        }
    }

    return tab;
}

int get_random_int(int a, int b) // nie można dać &, bo nie przyjmie typu const
{
    int result = a + rand()%(b-a+1);
    return result;
}

double get_random_double(double a, double b)
{
    double result = a + (double)rand()/RAND_MAX * (b - a);
    return result;
}


/*
tab - 3D array
x - which x
size_y - length of array
size_z - height of array
*/
int** extract_2D_section_1(int*** tab, int x, int &_size_y, int &_size_z)
{
    int **extracted_table = allocate_2D_table(_size_y, _size_z);

    for(int i = 0; i < _size_z; i++)
    {
        for(int j = 0; j < _size_y; j++)
        {
            extracted_table[i][j] = tab[i][j][x];
        }
    }
    return extracted_table;
}

/*
tab - 3D array
y - which y
size_x - width of array
size_z - height of array
*/
int** extract_2D_section_2(int*** tab, int y, int &_size_x, int &_size_z)
{
    int **extracted_table = allocate_2D_table(_size_x, _size_z);

    for(int i = 0; i < _size_z; i++)
    {
        for(int k = 0; k < _size_x; k++)
        {
            extracted_table[i][k] = tab[i][y][k];
        }
    }
    return extracted_table;
}



int** allocate_2D_table(int &_size_x, int &_size_y)
{
    int** tab = new int*[_size_y];

    for(int i = 0; i < _size_y; i++)
    {
        tab[i] = new int[_size_x];
    }
    return tab;
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
    return (double)suma/(double)(_size_x * _size_y);
}

