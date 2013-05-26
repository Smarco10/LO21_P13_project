#ifndef VIDEO_H
#define VIDEO_H

#include "Binary.h"

class Video: public Binary{
    Video(const Video& v):Binary(0, v.title){}
    void operator=(const Video& v);
    //void load();
public:
    Video(unsigned int id, const QString& title, const QString& desc, const QString& path):Binary(id, title, desc, path){}
};

#endif // VIDEO_H

