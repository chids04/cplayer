#ifndef SONGVIEW_H
#define SONGVIEW_H

#include <QObject>

#include "songholder.h"

class SongView : public QObject
{
    Q_OBJECT

public:
    explicit SongView(SongHolder *songHolder, QObject *parent = nullptr);

public slots:
    void loadSongs();

private:
    SongHolder *songHolder;
};



#endif // SONGVIEW_H
