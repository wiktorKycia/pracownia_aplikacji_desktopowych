#include <iostream>
#include <cstdlib>
using namespace std;



int main()
{
    srand(time(NULL));
    int tab[2]; // statyczna alokacja

    int tab1[2][3];
    
    /*
    tab[0] === *tab
    tab[1] === *(tab+1)
    tab[1][1] === *(*(tab+1)+1)
    */
    
    int *tab2; // dynamiczna alokacja
    tab2 = new int[2];

    int **tab3; // adres tablicy adresów, === (int *)*
    tab3 = new int*[2]; //2-elementowa tablica na adresy do intów
    tab3[0] = new int[3];
    tab3[1] = new int[3];

    int tab4[2][3][4];


    int a = 21500;
    int b = 40 * 27;
    cout << a/b <<endl;



}