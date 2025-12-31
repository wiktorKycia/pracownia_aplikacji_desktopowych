#include<iostream>
#include<fstream>
#include<string>
#include "ppm.cpp"
#include "pgm_ascii.cpp"
#include "functions.hpp"

using namespace std;




class PortableGrayMap{};
class PortableBitMapASCII{};
class PortableBitMap{};




int main()
{
    setlocale(LC_ALL, "pl_PL.UTF-8");

    // cout << static_cast<int>(pixel_functions::enlighten(150));

    PortablePixMap ppm;

    ppm.readBinaryFile("./input_images/input_binary.ppm");

    ppm.writeBinaryFilePPM("./output_images/output1ppm.ppm");
    ppm.writeBinaryFilePGM("./output_images/output1pgm.pgm");
    ppm.writeBinaryFilePBM("./output_images/output1pbm.pbm");


    // ppm.readBitFile("./binary_output.ppm");
    // ppm.writeFilePPM("./output_images/output_from_binary.ppm");

    // ppm.readAsciiFile("input.ppm");
    // ppm.convert_to_negative();
    // ppm.writeFilePPM("./output_images/negative.ppm");

    // ppm.readAsciiFile("input.ppm");
    // ppm.enlighten(4.0);
    // ppm.writeFilePPM("./output_images/light.ppm");

    // ppm.readAsciiFile("input.ppm");
    // ppm.darken(4.0);
    // ppm.writeFilePPM("./output_images/dark.ppm");

    // ppm.readAsciiFile("input.ppm");
    // ppm.contrast(1.0);
    // ppm.writeFilePPM("./output_images/contrast.ppm");

    // ppm.readAsciiFile("input.ppm");
    // ppm.decontrast(20.0);
    // ppm.writeFilePPM("./output_images/decontrast.ppm");

    // ppm.writeFilePPM("output.ppm");
    // ppm.writeFilePGM("output.pgm");
    // ppm.writeFilePBM("output.pbm");

    // PortableGrayMapASCII pgm;
    // pgm.readAsciiFile("output.pgm");
    // pgm.writeFilePPM("output-from-pgm.ppm");
    // pgm.writeFilePGM("pgm-to-pgm.pgm");
    // pgm.writeFilePBM("pgm-to-pbm.pbm");


    return 0;
}