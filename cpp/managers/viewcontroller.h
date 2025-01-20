#ifndef VIEWCONTROLLER_H
#define VIEWCONTROLLER_H

#include <QtQml>
#include <QObject>
#include <QDebug>


class ViewController : public QObject
{
    Q_OBJECT
    QML_ANONYMOUS


public:
    explicit ViewController(QObject *parent = nullptr);


signals:
    void albumSelected();
    void songViewSelected();
    void playlistSelected();
    void albumViewSelected();
    void folderViewChanged();
    void foldersViewSelected();
    void settingsViewSelected();
    void playlistsViewSelected();
    void albumSongsViewChanged();
    void playlistSongsViewChanged();
    void showMsg(const QString &message);

public slots:
    void songView();
    void albumView();
    void selectAlbum();
    void foldersView();
    void settingsView();
    void playlistsView();
    void selectPlaylist();
private:
};

#endif // VIEWCONTROLLER_H
