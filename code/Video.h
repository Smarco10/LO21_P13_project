#ifndef VIDEO_H
#define VIDEO_H

#include "Binary.h"

class Video: public Binary{
    Video(const Video& v):Binary(0, v.title){}
    void operator=(const Video& v);
    void load();
public:
    Video(const QString& id, const QString& title, const QString& desc, const QString& path):Binary(id, title, desc, path){}
    QTextStream& save(QTextStream& f);

    QString toHTML();
    QString toTEX();
    QString toTEXT();
};

class VideoEditor: public BinaryEditor{
Q_OBJECT
    QMovie *movie;
    QLabel *frame;
    QWidget *control;
    QHBoxLayout *controlLay;
    QPushButton *play_bt;
    QPushButton *stop_bt;

public:
    VideoEditor(Video* v, QWidget* parent=0);
    ~VideoEditor(){}

signals:
    void updateS(QString);

public slots:
    void update(QString s="");
};

#endif // VIDEO_H

