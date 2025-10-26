#include<iostream>
#include<fstream>
#include<string>
#include "ppm_ascii.cpp"
#include "pgm_ascii.cpp"
#include "functions.hpp"

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

    // cout << static_cast<int>(pixel_functions::enlighten(150));

    PortablePixMapASCII ppm;

    ppm.readFile("input.ppm");
    ppm.convert_to_negative();
    ppm.writeFilePPM("./output_images/negative.ppm");

    ppm.readFile("input.ppm");
    ppm.enlighten(4.0);
    ppm.writeFilePPM("./output_images/light.ppm");

    ppm.readFile("input.ppm");
    ppm.darken(4.0);
    ppm.writeFilePPM("./output_images/dark.ppm");

    ppm.readFile("input.ppm");
    ppm.contrast();
    ppm.writeFilePPM("./output_images/contrast.ppm");

    ppm.readFile("input.ppm");
    ppm.decontrast(20.0);
    ppm.writeFilePPM("./output_images/decontrast.ppm");

    // ppm.writeFilePPM("output.ppm");
    // ppm.writeFilePGM("output.pgm");
    // ppm.writeFilePBM("output.pbm");

    // PortableGrayMapASCII pgm;
    // pgm.readFile("output.pgm");
    // pgm.writeFilePPM("output-from-pgm.ppm");
    // pgm.writeFilePGM("pgm-to-pgm.pgm");
    // pgm.writeFilePBM("pgm-to-pbm.pbm");


    return 0;
}