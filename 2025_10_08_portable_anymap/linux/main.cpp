#include<iostream>

using namespace std;

enum class FileType
{
    PBM_ASCII,
    PGM_ASCII,
    PPM_ASCII,
    PBM,
    PGM,
    PPM
};

class PortableAnymapConverter
{
    unsigned int sizex, sizey;
    FileType fileType;
    u_int8_t **pixels;

    public:
    PortableAnymapConverter(unsigned int _size_x, unsigned int _size_y, FileType _file_type);
    PortableAnymapConverter(const PortableAnymapConverter& portableAnymapConverter);
};

PortableAnymapConverter::PortableAnymapConverter(unsigned int _size_x, unsigned int _size_y, FileType _file_type)
{
    this->sizex = _size_x;
    this->sizey = _size_y;
    this->fileType = _file_type;

    this->pixels = new u_int8_t*[sizey];

    for(unsigned int i = 0; i < sizey; i++)
    {
        this->pixels[i] = new u_int8_t[sizex];

        for(unsigned int j = 0; j < sizex; j++)
        {
            this->pixels[i][j] = portableAnymapConverter.pixels[i][j];
        }
    }
};

PortableAnymapConverter::PortableAnymapConverter(const PortableAnymapConverter& portableAnymapConverter)
{
    this->sizex = portableAnymapConverter.sizex;
    this->sizey = portableAnymapConverter.sizey;
    this->fileType = portableAnymapConverter.fileType;

    this->pixels = new u_int8_t*[sizey];

    for(unsigned int i = 0; i < sizey; i++)
    {
        this->pixels[i] = new u_int8_t[sizex];

        for(unsigned int j = 0; j < sizex; j++)
        {
            this->pixels[i][j] = portableAnymapConverter.pixels[i][j];
        }
    }
};

int main()
{
    
    return 0;
}