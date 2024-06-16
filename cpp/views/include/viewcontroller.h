#ifndef VIEWCONTROLLER_H
#define VIEWCONTROLLER_H

#include <QObject>
#include <QDebug>

class ViewController : public QObject
{
    Q_OBJECT

public:
    explicit ViewController(QObject *parent = nullptr);

signals:
    void songViewSelected();
    void albumViewSelected();
    void foldersViewSelected();
    void albumSelected();
    void playlistsViewSelected();
    void playlistSelected();


public slots:
    void songView();
    void albumView();
    void selectAlbum();
    void foldersView();
    void playlistsView();
    void selectPlaylist();
};

#endif // VIEWCONTROLLER_H
