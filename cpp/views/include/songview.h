#ifndef SONGVIEW_H
#define SONGVIEW_H

#include <QObject>


class SongView : public QObject
{
    Q_OBJECT

public:
    explicit SongView(QObject *parent = nullptr);

public slots:
    void loadSongs();

private:
};



#endif // SONGVIEW_H
