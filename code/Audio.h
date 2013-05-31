#ifndef AUDIO_H
#define AUDIO_H

#include "Binary.h"

class Audio: public Binary{
    Audio(const Audio& a):Binary(0, a.title){}
    void operator=(const Audio& a);
    void load();
public:
    Audio(const QString& id, const QString& title, const QString& desc, const QString& path):Binary(id, title, desc, path){}

    QTextStream& save(QTextStream& f);
};

#endif // AUDIO_H

