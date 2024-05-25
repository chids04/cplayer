#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "cpp/mediaplayercontroller.h"
#include "cpp/mediaimageprovider.h"
#include "cpp/musiclibrary.h"
#include "cpp/songlistmodel.h"
#include "cpp/coverartholder.h"
#include "cpp/albumholder.h"
#include "cpp/albumlistmodel.h"
#include "cpp/viewcontroller.h"
#include "cpp/albumfilterproxymodel.h"
#include "cpp/albumview.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    CoverArtHolder *coverArtHolder = new CoverArtHolder;

    AlbumListModel *albumListModel = new AlbumListModel;
    AlbumHolder *albumHolder = new AlbumHolder(albumListModel);
    qmlRegisterSingletonInstance("com.c.AlbumListModel", 1, 0, "AlbumModel", albumListModel);

    SongListModel *songModel = new SongListModel;
    qmlRegisterSingletonInstance("com.c.SongModel", 1, 0, "SongModel", songModel);

    AlbumFilterProxyModel *albumFilterProxyModel = new AlbumFilterProxyModel;
    qmlRegisterSingletonInstance("com.c.AlbumFilterProxyModel", 1, 0,"AlbumFilterModel", albumFilterProxyModel);
    albumFilterProxyModel->setSourceModel(songModel);
    albumFilterProxyModel->setDynamicSortFilter(true);


    MediaPlayerController *controller = new MediaPlayerController(coverArtHolder);
    qmlRegisterSingletonInstance("com.c.MediaController", 1, 0,"MediaPlayerController", controller);

    MusicLibrary *musicLibrary = new MusicLibrary(songModel, coverArtHolder, albumHolder);
    qmlRegisterSingletonInstance("com.c.MusicLibrary", 1, 0, "MusicLibrary", musicLibrary);

    ViewController *viewController = new ViewController;
    qmlRegisterSingletonInstance("com.c.ViewController", 1, 0, "ViewController", viewController);

    AlbumView *albumView = new AlbumView;
    qmlRegisterSingletonInstance("com.c.AlbumViewController", 1, 0, "AlbumController", albumView);

    MediaImageProvider *mediaImageProvider = new MediaImageProvider(coverArtHolder);
    engine.addImageProvider(QLatin1String("coverArt"), mediaImageProvider);


    const QUrl url(QStringLiteral("qrc:/cplayer/Main.qml"));
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
