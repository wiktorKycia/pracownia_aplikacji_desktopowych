#include<iostream>
#include<fstream>
#include<string>
using namespace std;

/*
PGM (P2)
*/
class PortableGrayMapASCII
{
    unsigned int sizex, sizey;
    u_int8_t **pixels;
    void allocate_pixels();

    public:

    PortableGrayMapASCII()
    {
        sizex = 0;
        sizey = 0;
        pixels = nullptr;
    }
    PortableGrayMapASCII(unsigned int _sizex, unsigned int _sizey)
    {
        sizex = _sizex;
        sizey = _sizey;
        this->allocate_pixels();
    }
    PortableGrayMapASCII(const PortableGrayMapASCII &obj)
    {
        sizex = obj.sizex;
        sizey = obj.sizey;
        pixels = new u_int8_t*[sizey];

        for(unsigned int i = 0; i < sizey; i++)
        {
            pixels[i] = new u_int8_t[sizex];

            for(unsigned int j = 0; j < sizex; j++)
            {
                pixels[i][j] = obj.getPixel(i, j);
            }
        }
    }
    ~PortableGrayMapASCII()
    {
        sizex = 0;
        sizey = 0;
        delete pixels;
    }
    u_int8_t getPixel(unsigned int x, unsigned int y) const
    {
        return this->pixels[y][x];
    }
    void readFile(string fileName);
    void writeFilePPM(string fileName);
    void writeFilePGM(string fileName);
    void writeFilePBM(string fileName);
};
void PortableGrayMapASCII::allocate_pixels()
{
    this->pixels = new u_int8_t*[sizey];

    for(unsigned int i = 0; i < sizey; i++)
    {
        this->pixels[i] = new u_int8_t[sizex];

        for(unsigned int j = 0; j < sizex; j++)
        {
            this->pixels[i][j] = {0};
        }
    }
}
void PortableGrayMapASCII::readFile(string fileName)
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
    
    if(line != "P2")
    {
        cout << "The file is not a pgm format!" << endl;
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
            string value;
            file >> value;
            this->pixels[i][j] = stoi(value);
        }
    }

    file.close();
}

void PortableGrayMapASCII::writeFilePPM(string fileName)
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
            for(int color = 0; color < 3; color++)
            {
                file << static_cast<int>(this->pixels[i][j]) << endl;
            }
        }
    }

    file.close();
}

void PortableGrayMapASCII::writeFilePGM(string fileName)
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
            file << static_cast<int>(this->pixels[i][j]) << endl;
        }
    }

    file.close();
}

void PortableGrayMapASCII::writeFilePBM(string fileName)
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
            sum += static_cast<int>(this->pixels[i][j]);
        }
    }
    int avg = (sum)/(sizex*sizey);
    cout << avg << endl;


    for(unsigned int i = 0; i < sizey; i++)
    {
        for(unsigned int j = 0; j < sizex; j++)
        {
            if (static_cast<int>(this->pixels[i][j]) > avg)
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