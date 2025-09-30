#include<iostream>

using namespace std;

int*** create_3D_table(int _size_x, int _size_y, int _size_z);
void print_3D_table(int*** tab, int _size_x, int _size_y, int _size_z);

int main()
{

    int z = 27;
    int x = 50;
    int y = 40;

    int*** tab = create_3D_table(x, y, z);
    print_3D_table(tab, x, y, z);

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
                tab[i][j][k] = i;
            }
        }
    }

    return tab;
}