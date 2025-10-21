#include<iostream>

using namespace std;

/*
PPM (P3)
*/
class PortablePixMapASCII
{
    static const int numberOfColors = {3};
    unsigned int sizex, sizey;
    u_int8_t ***pixels;
    
    public:
    PortablePixMapASCII(unsigned int _sizex, unsigned int _sizey)
    {
        sizex = _sizex;
        sizey = _sizey;
        pixels = new u_int8_t**[sizey];

        for(unsigned int i = 0; i < sizey; i++)
        {
            pixels[i] = new u_int8_t*[sizex];

            for(unsigned int j = 0; j < sizex; j++)
            {
                pixels[i][j] = new u_int8_t[numberOfColors]{0,0,0};
            }
        }
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
    u_int8_t getPixel(unsigned int x, unsigned int y, unsigned int color) const
    {
        return this->pixels[y][x][color];
    }
};
class PortablePixMap{};
class PortableGrayMapASCII{};
class PortableGrayMap{};
class PortableBitMapASCII{};
class PortableBitMap{};




int main()
{
    
    return 0;
}