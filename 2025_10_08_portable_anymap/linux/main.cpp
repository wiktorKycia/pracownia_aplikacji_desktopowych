#include<iostream>
#include<fstream>
#include<string>
#include "ppm_ascii.cpp"
#include "pgm_ascii.cpp"

using namespace std;


class PortablePixMap
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
    ppm.writeFilePPM("output.ppm");
    ppm.writeFilePGM("output.pgm");
    ppm.writeFilePBM("output.pbm");
    return 0;
}