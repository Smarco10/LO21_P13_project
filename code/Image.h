#ifndef IMAGE_H
#define IMAGE_H

#include "Binary.h"

class Image: public Binary{
    Image(const Image& i):Binary(0, i.title){}
    void operator=(const Image& i);
    void load();
public:
    Image(const QString& id, const QString& title, const QString& desc, const QString& path):Binary(id, title, desc, path){}
    QTextStream& save(QTextStream& f);
};

#endif // IMAGE_H

