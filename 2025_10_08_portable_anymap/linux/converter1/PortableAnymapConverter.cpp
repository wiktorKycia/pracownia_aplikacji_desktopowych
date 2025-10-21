#include "PortableAnymapConverter.h"
#include <iostream>
#include <string>
using namespace std;

void PortableAnymapConverter::convertASCII(string fileName, FileType typeToSave)
{
    int dot_idx = fileName.find('.');
    string name = fileName.substr(0, dot_idx); // to może się zepsuć
    string fileExtension = fileName.substr(dot_idx); // to też bo nwm jak konkretnie działa substr

    if(fileExtension == "ppm")
    {
        if(typeToSave == FileType::PPM_ASCII)
        {
            return;
        }
        
    }



}