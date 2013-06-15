#ifndef AUDIO_H
#define AUDIO_H

#include "Binary.h"

class Audio: public Binary{
    Audio(Audio& a);
    void operator=(const Audio& a);
    void load();
public:
    Audio(const QString& id, const QString& title, const QString& desc="", const QString& path=""):Binary("Audio", id, title, desc, path){}

    QString toHTML();
    QString toTEX();
    QString toTEXT();

    QTextStream& save(QTextStream& f);
};

class AudioEditor: public BinaryEditor{
Q_OBJECT
    QSound *sound;
    QWidget *control;
    QHBoxLayout *controlLay;
    QPushButton *play_bt;
    QPushButton *stop_bt;

public:
    AudioEditor(Audio* a, QWidget* parent=0);
    ~AudioEditor(){}

    QString selectFile();
};

#endif // AUDIO_H

