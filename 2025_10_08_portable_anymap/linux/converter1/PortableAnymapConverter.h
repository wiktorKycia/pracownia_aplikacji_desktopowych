#include "../FileType.h"

class PortableAnymapConverter
{
    unsigned int sizex, sizey;
    FileType fileType;
    u_int8_t **pixels;

    public:
    PortableAnymapConverter(unsigned int _size_x, unsigned int _size_y, FileType _file_type);
    PortableAnymapConverter(const PortableAnymapConverter& portableAnymapConverter);
};