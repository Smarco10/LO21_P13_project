#ifndef AUDIO_H
#define AUDIO_H

#include "Binary.h"

class Audio: public Binary{
    Audio(const Audio& a):Binary(0, a.title){}
    void operator=(const Audio& a);
    void load();
public:
    Audio(const QString& id, const QString& title, const QString& desc, const QString& path):Binary(id, title, desc, path){}

    QString toHTML();
    QString toTEX();
    QString toTEXT();

    QTextStream& save(QTextStream& f);
};

class AudioEditor: public BinaryEditor{
Q_OBJECT

public:
    AudioEditor(Audio* a, QWidget* parent=0);
    ~AudioEditor(){}

signals:
    void updateS(QString);

public slots:
    void update(QString s="");
};

#endif // AUDIO_H

