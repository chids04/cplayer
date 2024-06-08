#ifndef MUSICLIBRARY_H
#define MUSICLIBRARY_H

#include <QUrl>
#include <QtQml>
#include <QDebug>
#include <QObject>
#include <QPixmap>
#include <QStringList>
#include <QDirIterator>
#include <QQmlListProperty>

#include <vector>
#include <taglib/tag.h>
#include <taglib/fileref.h>
#include <taglib/mpegfile.h>
#include <taglib/tstringlist.h>
#include <taglib/tpropertymap.h>
#include <taglib/id3v2tag.h>
#include <taglib/attachedpictureframe.h>

#include "songlistmodel.h"
#include "coverartholder.h"
#include "albumholder.h"

class MusicLibrary : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QUrl musicPath READ musicPath WRITE setMusicPath NOTIFY musicPathChanged)
    //Q_PROPERTY(QQmlListProperty<SongInfo> songsModel READ songsModel NOTIFY songsModelChanged)

public:
    explicit MusicLibrary(SongListModel *songModel, CoverArtHolder *coverArtHolder, AlbumHolder *albumHolder, QObject *parent=nullptr);
    QUrl musicPath() const;
    void setMusicPath(const QUrl &newMusicPath);

    //QQmlListProperty<Song> songsModel() ;

signals:
    void musicPathChanged(const QUrl &dirPath);

    //void songsModelChanged();

private slots:
    void onMusicPathChanged(const QUrl &dirPath);

private:
    //std::vector<Song> songs;
    QUrl m_musicPath;
    SongListModel *songModel;
    CoverArtHolder *coverArtHolder;
    AlbumHolder *albumHolder;

    //static qsizetype songsCount(QQmlListProperty<Song> *list);
    //static Song* songAt(QQmlListProperty<Song>* list, qsizetype index);
};

#endif // MUSICLIBRARY_H
