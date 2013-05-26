#ifndef IMAGE_H
#define IMAGE_H

#include "Binary.h"

class Image: public Binary{
    Image(const Image& i):Binary(0, i.title){}
    void operator=(const Image& i);
    //void load();
public:
    Image(unsigned int id, const QString& title, const QString& desc, const QString& path):Binary(id, title, desc, path){}
};

#endif // IMAGE_H

