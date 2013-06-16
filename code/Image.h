#ifndef IMAGE_H
#define IMAGE_H

#include "Binary.h"

class Image: public Binary{
    Image(Image& i);
    void operator=(const Image& i);
    void load();
public:
    Image(const QString& id, const QString& title, const QString& desc="", const QString& path=""):Binary("Image", id, title, desc, path){}
    QTextStream& save(QTextStream& f);
    NoteEditor* getEditor(QWidget* parent = NULL);

    void makehtmlbody(QXmlStreamWriter* qw);
    QString toTEX();
    QString toTEXT();
};

class ImageEditor: public BinaryEditor{
Q_OBJECT
    QLabel *image;

public:
    ImageEditor(Image* i, QWidget* parent=0);
    ~ImageEditor(){}

    QString selectFile();
    void updateBin();
};

#endif // IMAGE_H

