﻿#ifndef VIDEO_H
#define VIDEO_H

#include "Binary.h"
///\class Video
///Correspond à la spécification de Binary pour contenir:
///une Video
///un type d'éditeur i.e. un graphisme spécifique
///et des exports HTML,Tex,TEXT correspondants
class Video: public Binary{
    Video(Video& v);
    void operator=(const Video& v);
    void load();
public:
    Video(const QString& id, const QString& title, const QString& desc="", const QString& path=""):Binary("Video", id, title, desc, path){}
    QTextStream& save(QTextStream& f);
    NoteEditor* getEditor(QWidget* parent = NULL);

    void makehtmlbody(QXmlStreamWriter* qw);
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
    QPushButton *pause_bt;
    QPushButton *stop_bt;

public:
    VideoEditor(Video* v, QWidget* parent=0);
    ~VideoEditor(){}

    QString selectFile();
    void updateBin();
};

#endif // VIDEO_H

