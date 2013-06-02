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

    QString toHTML();
    QString toTEX();
    QString toTEXT();
};

class ImageEditor: public BinaryEditor{
Q_OBJECT
    QImage *image;

public:
    ImageEditor(Image* i, QWidget* parent=0);
    ~ImageEditor(){}

signals:
    void updateS(QString);

public slots:
    void update(QString s="");
};

#endif // IMAGE_H

