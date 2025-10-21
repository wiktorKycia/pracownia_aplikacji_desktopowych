#include<iostream>
#include<fstream>
#include<string>
using namespace std;

/*
PPM (P3)
*/
class PortablePixMapASCII
{
    static const int numberOfColors = {3};
    unsigned int sizex, sizey;
    u_int8_t ***pixels;

    void allocate_pixels();
    
    public:

    PortablePixMapASCII()
    {
        sizex = 0;
        sizey = 0;
        pixels = nullptr;
    }
    PortablePixMapASCII(unsigned int _sizex, unsigned int _sizey)
    {
        sizex = _sizex;
        sizey = _sizey;
        this->allocate_pixels();
    }
    PortablePixMapASCII(const PortablePixMapASCII &obj)
    {
        sizex = obj.sizex;
        sizey = obj.sizey;
        pixels = new u_int8_t**[sizey];

        for(unsigned int i = 0; i < sizey; i++)
        {
            pixels[i] = new u_int8_t*[sizex];

            for(unsigned int j = 0; j < sizex; j++)
            {
                pixels[i][j] = new u_int8_t[numberOfColors]{
                    obj.getPixel(i, j, 0),
                    obj.getPixel(i, j, 1),
                    obj.getPixel(i, j, 2)
                };
            }
        }
    }
    ~PortablePixMapASCII()
    {
        sizex = 0;
        sizey = 0;
        delete pixels;
    }
    u_int8_t getPixel(unsigned int x, unsigned int y, unsigned int color) const
    {
        return this->pixels[y][x][color];
    }
    void readFile(string fileName);
    void writeFile(string fileName);
};

void PortablePixMapASCII::allocate_pixels()
{
    this->pixels = new u_int8_t**[this->sizey];

    for(unsigned int i = 0; i < this->sizey; i++)
    {
        this->pixels[i] = new u_int8_t*[this->sizex];

        for(unsigned int j = 0; j < this->sizex; j++)
        {
            this->pixels[i][j] = new u_int8_t[numberOfColors]{0,0,0};
        }
    }
}

void PortablePixMapASCII::readFile(string fileName)
{
    ifstream file;
    file.open(fileName, ios::in);

    if(!file.good())
    {
        cout << "Error reading file: " << fileName << endl;
        exit(1);
    }

    string line;

    getline(file, line); // pierwsza linia
    
    if(line != "P3")
    {
        cout << "The file is not a ppm format!" << endl;
    }
    getline(file, line); // linia z komentarzem

    if (line[0] == '#') // jeśli ta linia ma komentarz, to przeczytaj następną
    {
        getline(file, line);
    }
    // wczytaj szer i wys
    int idx_space = line.find(' ');
    this->sizex = stoi(line.substr(0, idx_space));
    this->sizey = stoi(line.substr(idx_space+1));
    cout << "sizex = " << this->sizex << endl << "sizey = " << this->sizey << endl;
    // cout << "Type of sizex: " << typeid(this->sizex).name() << endl; // prints: j
    // cout << "Type of sizey: " << typeid(this->sizey).name() << endl; // prints: j

    getline(file, line); // upewnij się, że max color to 255

    if(line != "255")
    {
        cout << "Maximum color value does not equal 255" << endl;
    }

    if(this->pixels == nullptr)
    {
        this->allocate_pixels();
    }

    for(unsigned int i = 0; i < sizey; i++)
    {
        for(unsigned int j = 0; j < sizex; j++)
        {
            for(int color = 0; color < this->numberOfColors; color++)
            {
                // cout << i << ' '<< j << ' ' << color<< endl;
                string value;
                file >> value;
                this->pixels[i][j][color] = stoi(value);
                // cout << value << "\t" << stoi(value)<< "\t" << this->pixels[i][j][color] << endl;
            }
        }
    }

    file.close();
}
void PortablePixMapASCII::writeFile(string fileName)
{
    ofstream file;
    file.open(fileName, ios::out | ios::trunc);

    if(!file.good())
    {
        cout << "Error opening file: " << fileName << endl;
        exit(1);
    }

    file << "P3" << endl; // nagłówek
    file << "# Created with C++" << endl; // komentarz
    file << this->sizex << " " << this->sizey << endl; // rozmiary szer i wys
    file << "255" << endl; // max color

    cout << "zaczynam zapisywać dane" << endl;

    for(unsigned int i = 0; i < sizey; i++)
    {
        for(unsigned int j = 0; j < sizex; j++)
        {
            for(int color = 0; color < this->numberOfColors; color++)
            {
                // cout << static_cast<int>(this->pixels[i][j][color]) << endl;
                file << static_cast<int>(this->pixels[i][j][color]) << endl;
            }
        }
    }

    file.close();
}
class PortablePixMap{};

/*
PGM (P2)
*/
class PortableGrayMapASCII
{

};
class PortableGrayMap{};
class PortableBitMapASCII{};
class PortableBitMap{};




int main()
{
    setlocale(LC_ALL, "pl_PL.UTF-8");
    PortablePixMapASCII ppm;
    ppm.readFile("wol.ppm");
    ppm.writeFile("output.ppm");
    return 0;
}