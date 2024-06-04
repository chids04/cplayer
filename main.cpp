#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QFontDatabase>

#include "cpp/mediaplayercontroller.h"
#include "cpp/mediaimageprovider.h"
#include "cpp/musiclibrary.h"
#include "cpp/songlistmodel.h"
#include "cpp/coverartholder.h"
#include "cpp/albumholder.h"
#include "cpp/albumlistmodel.h"
#include "cpp/viewcontroller.h"
#include "cpp/albumfilterproxymodel.h"
#include "cpp/albumsongsview.h"
#include "cpp/playlistmanager.h"
#include "cpp/folderview.h"
#include "cpp/songholder.h"
#include "cpp/songview.h"
#include "cpp/albumview.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    int fontId = QFontDatabase::addApplicationFont(":/resource/ui/fonts/Satoshi-Medium.otf");

    if (fontId != -1) {
        QString fontFamily = QFontDatabase::applicationFontFamilies(fontId).at(0);
        // Set the application-wide font
        QGuiApplication::setFont(QFont(fontFamily));
    }

    QQmlApplicationEngine engine;

    CoverArtHolder *coverArtHolder = new CoverArtHolder;

    AlbumListModel *albumListModel = new AlbumListModel;
    AlbumHolder *albumHolder = new AlbumHolder(albumListModel);
    qmlRegisterSingletonInstance("com.c.AlbumListModel", 1, 0, "AlbumModel", albumListModel);

    AlbumView *albumView = new AlbumView(albumHolder);
    qmlRegisterSingletonInstance("com.c.AlbumView", 1, 0, "AlbumView", albumView);

    AlbumSongsView *albumSongsView = new AlbumSongsView;
    qmlRegisterSingletonInstance("com.c.AlbumSongsView", 1, 0, "AlbumSongsView", albumSongsView);

    PlaylistManager *playlistManager = new PlaylistManager(albumHolder);
    qmlRegisterSingletonInstance("com.c.PlaylistManager", 1, 0, "PlaylistManager", playlistManager);

    SongListModel *songModel = new SongListModel;
    qmlRegisterSingletonInstance("com.c.SongModel", 1, 0, "SongModel", songModel);

    SongHolder *songHolder = new SongHolder(songModel);
    SongView *songView = new SongView(songHolder);
    qmlRegisterSingletonInstance("com.c.SongView", 1, 0, "SongView", songView);

    FolderView *folderView = new FolderView(songHolder, albumHolder, coverArtHolder);
    qmlRegisterSingletonInstance("com.c.FolderView", 1, 0, "FolderView", folderView);

    AlbumFilterProxyModel *albumFilterProxyModel = new AlbumFilterProxyModel;
    qmlRegisterSingletonInstance("com.c.AlbumFilterProxyModel", 1, 0,"AlbumFilterModel", albumFilterProxyModel);
    albumFilterProxyModel->setSourceModel(songModel);
    albumFilterProxyModel->setDynamicSortFilter(true);


    MediaPlayerController *controller = new MediaPlayerController(coverArtHolder, playlistManager, songModel);
    qmlRegisterSingletonInstance("com.c.MediaController", 1, 0,"MediaPlayerController", controller);

    MusicLibrary *musicLibrary = new MusicLibrary(songModel, coverArtHolder, albumHolder);
    qmlRegisterSingletonInstance("com.c.MusicLibrary", 1, 0, "MusicLibrary", musicLibrary);

    ViewController *viewController = new ViewController;
    qmlRegisterSingletonInstance("com.c.ViewController", 1, 0, "ViewController", viewController);


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
