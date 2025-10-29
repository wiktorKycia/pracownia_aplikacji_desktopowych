#include<iostream>
#include<fstream>
#include<string>
#include<cstdint>
#include "functions.hpp"
using namespace std;

/*
PPM (P3 and P6)
*/
class PortablePixMap
{
    static const int numberOfColors = {3};
    unsigned int sizex, sizey;
    uint8_t ***pixels;

    void allocate_pixels();
    
    public:

    PortablePixMap()
    {
        sizex = 0;
        sizey = 0;
        pixels = nullptr;
    }
    PortablePixMap(unsigned int _sizex, unsigned int _sizey)
    {
        sizex = _sizex;
        sizey = _sizey;
        this->allocate_pixels();
    }
    PortablePixMap(const PortablePixMap &obj)
    {
        sizex = obj.sizex;
        sizey = obj.sizey;
        pixels = new uint8_t**[sizey];

        for(unsigned int i = 0; i < sizey; i++)
        {
            pixels[i] = new uint8_t*[sizex];

            for(unsigned int j = 0; j < sizex; j++)
            {
                pixels[i][j] = new uint8_t[numberOfColors]{
                    obj.getPixel(i, j, 0),
                    obj.getPixel(i, j, 1),
                    obj.getPixel(i, j, 2)
                };
            }
        }
    }
    ~PortablePixMap()
    {
        sizex = 0;
        sizey = 0;
        delete pixels;
    }
    uint8_t getPixel(unsigned int x, unsigned int y, unsigned int color) const
    {
        return this->pixels[y][x][color];
    }
    void readFile(string fileName);
    void readBinaryFile(string fileName);
    void writeFilePPM(string fileName);
    void writeFilePGM(string fileName);
    void writeFilePBM(string fileName);
    void writeBinaryFilePPM(string fileName);
    void writeBinaryFilePGM(string fileName);
    void writeBinaryFilePBM(string fileName);
    void convert_to_negative();
    void enlighten(double a);
    void darken(double a);
    void contrast(double a);
    void decontrast(double a);
};

void PortablePixMap::allocate_pixels()
{
    this->pixels = new uint8_t**[this->sizey];

    for(unsigned int i = 0; i < this->sizey; i++)
    {
        this->pixels[i] = new uint8_t*[this->sizex];

        for(unsigned int j = 0; j < this->sizex; j++)
        {
            this->pixels[i][j] = new uint8_t[numberOfColors]{0,0,0};
        }
    }
}

void PortablePixMap::readFile(string fileName)
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
    // cout << "sizex = " << this->sizex << endl << "sizey = " << this->sizey << endl;
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
void PortablePixMap::readBinaryFile(string fileName)
{
    ifstream file;
    file.open(fileName, ios::in | ios::binary);
    if(!file.good())
    {
        cout << "Error reading file: " << fileName << endl;
        exit(1);
    }

    string line;

    getline(file, line);

    if(line != "P6")
    {
        cout << "The file is not in a PPM format!" << endl;
    }
    getline(file, line);

    if (line[0] == '#') // jeśli ta linia ma komentarz, to przeczytaj następną
    {
        getline(file, line);
    }

    // wczytaj szer i wys
    int idx_space = line.find(' ');
    this->sizex = stoi(line.substr(0, idx_space));
    this->sizey = stoi(line.substr(idx_space+1));

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
                file.read((char *)&this->pixels[i][j][color], sizeof(uint8_t));
            }
        }
    }

    file.close();
}

void PortablePixMap::writeFilePPM(string fileName)
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
void PortablePixMap::writeFilePGM(string fileName)
{
    ofstream file;
    file.open(fileName, ios::out | ios::trunc);

    if(!file.good())
    {
        cout << "Error opening file: " << fileName << endl;
        exit(1);
    }

    file << "P2" << endl; // nagłówek
    file << "# Created with C++" << endl; // komentarz
    file << this->sizex << " " << this->sizey << endl; // rozmiary szer i wys
    file << "255" << endl; // max color

    cout << "zaczynam zapisywać dane" << endl;

    for(unsigned int i = 0; i < sizey; i++)
    {
        for(unsigned int j = 0; j < sizex; j++)
        {
            int sum = 0;
            for(int color = 0; color < this->numberOfColors; color++)
            {
                sum += static_cast<int>(this->pixels[i][j][color]);
            }
            file << (int)(sum/3) << endl;
        }
    }

    file.close();
}
void PortablePixMap::writeFilePBM(string fileName)
{
    ofstream file;
    file.open(fileName, ios::out | ios::trunc);

    if(!file.good())
    {
        cout << "Error opening file: " << fileName << endl;
        exit(1);
    }

    file << "P1" << endl; // nagłówek
    file << "# Created with C++" << endl; // komentarz
    file << this->sizex << " " << this->sizey << endl; // rozmiary szer i wys
    // file << "255" << endl; // max color

    // cout << "zaczynam zapisywać dane" << endl;

    // basic quantization: sum up all the colors and calculate the average
    unsigned long long sum = 0;
    for(unsigned int i = 0; i < sizey; i++)
    {
        for(unsigned int j = 0; j < sizex; j++)
        {
            for(int color = 0; color < this->numberOfColors; color++)
            {
                sum += static_cast<int>(this->pixels[i][j][color]);
            }
            // file << (int)(sum/3) << endl;
        }
    }
    int avg = (sum)/(sizex*sizey*numberOfColors);
    cout << avg << endl;


    for(unsigned int i = 0; i < sizey; i++)
    {
        for(unsigned int j = 0; j < sizex; j++)
        {
            int sum_local = 0;
            for(int color = 0; color < this->numberOfColors; color++)
            {
                sum_local += static_cast<int>(this->pixels[i][j][color]);
            }
            if (sum_local > avg)
            {
                file << 0 << endl;
            }
            else
            {
                file << 1 << endl;
            }
        }
    }
    file.close();
}

void PortablePixMap::writeBinaryFilePPM(string fileName)
{
    ofstream file;

    file.open(fileName, ios::out | ios::trunc | ios::binary);

    if(!file.good())
    {
        cout << "Error opening file " << fileName << endl;
        exit(1);
    }

    file << "P6" << endl;
    file << this->sizex << " " << this->sizey << endl;
    file << "255" << endl;

    for(unsigned int i = 0; i < sizey; i++)
    {
        for(unsigned int j = 0; j < sizex; j++)
        {
            for(int color = 0; color < this->numberOfColors; color++)
            {
                file.write((char *)&this->pixels[i][j][color], sizeof(uint8_t));
            }
        }
    }

    file.close();
}

void PortablePixMap::convert_to_negative()
{
    for(unsigned int i = 0; i < this->sizey; i++)
    {
        for(unsigned int j = 0; j < this->sizex; j++)
        {
            for(uint8_t color = 0; color < this->numberOfColors; color++)
            {
                this->pixels[i][j][color] = pixel_functions::negativ(this->pixels[i][j][color]);
            }
        }
    }
}
void PortablePixMap::enlighten(double a = 1.5)
{
    for(unsigned int i = 0; i < this->sizey; i++)
    {
        for(unsigned int j = 0; j < this->sizex; j++)
        {
            for(uint8_t color = 0; color < this->numberOfColors; color++)
            {
                this->pixels[i][j][color] = pixel_functions::enlighten(this->pixels[i][j][color], a);
            }
        }
    }
}
void PortablePixMap::darken(double a = 1.5)
{
    for(unsigned int i = 0; i < this->sizey; i++)
    {
        for(unsigned int j = 0; j < this->sizex; j++)
        {
            for(uint8_t color = 0; color < this->numberOfColors; color++)
            {
                this->pixels[i][j][color] = pixel_functions::darken(this->pixels[i][j][color], a);
            }
        }
    }
}
void PortablePixMap::contrast(double a = 0.062622429)
{
    for(unsigned int i = 0; i < this->sizey; i++)
    {
        for(unsigned int j = 0; j < this->sizex; j++)
        {
            for(uint8_t color = 0; color < this->numberOfColors; color++)
            {
                this->pixels[i][j][color] = pixel_functions::contrast(this->pixels[i][j][color], a);
            }
        }
    }
}
void PortablePixMap::decontrast(double a = 100.0)
{
    for(unsigned int i = 0; i < this->sizey; i++)
    {
        for(unsigned int j = 0; j < this->sizex; j++)
        {
            for(uint8_t color = 0; color < this->numberOfColors; color++)
            {
                this->pixels[i][j][color] = pixel_functions::decontrast(this->pixels[i][j][color], a);
            }
        }
    }
}