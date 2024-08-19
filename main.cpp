#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QFontDatabase>

#include "mediaplayercontroller.h"
#include "mediaimageprovider.h"
#include "songlistmodel.h"
#include "coverartholder.h"
#include "albumlistmodel.h"
#include "viewcontroller.h"
#include "albumfilterproxymodel.h"
#include "folderlistmodel.h"
#include "albumsongsview.h"
#include "folderview.h"
#include "songview.h"
#include "albumview.h"
#include "playlistmodel.h"
#include "playlistmanager.h"
#include "nowplaying.h"
#include "songfilterproxymodel.h"
#include "albumsearchfilter.h"

#include "modelhandler.h"
#include "musichandler.h"
#include "viewcontroller.h"

int main(int argc, char *argv[])
{
    //implement serilzation
    //for now i just get list of folders and re-scan the directory

    QGuiApplication app(argc, argv);

    int fontId = QFontDatabase::addApplicationFont(":/resource/ui/fonts/Satoshi-Medium.otf");

    if (fontId != -1) {
        QString fontFamily = QFontDatabase::applicationFontFamilies(fontId).at(0);
        // Set the application-wide font
        QGuiApplication::setFont(QFont(fontFamily));
    }

    QQmlApplicationEngine engine;

    auto modelHandler = engine.singletonInstance<ModelHandler *>("cplayer", "ModelHandler");
    modelHandler->setSongList(&SongFilterProxyModel::instance());
    modelHandler->setAlbumList(&AlbumSearchFilter::instance());
    modelHandler->setAlbumSongs(&AlbumFilterProxyModel::instance());
    modelHandler->setPlaylistList(&PlaylistModel::instance());
    modelHandler->setFolderList(&FolderListModel::instance());


    auto musicHandler = engine.singletonInstance<MusicHandler *>("cplayer", "MusicHandler");
    musicHandler->setMediaPlayerController(&MediaPlayerController::instance());
    musicHandler->setNowPlaying(&NowPlaying::instance());
    musicHandler->setPlaylistManager(&PlaylistManager::instance());

    auto viewController = engine.singletonInstance<ViewController *>("cplayer", "ViewController");
    viewController->setAlbumSongsView(&AlbumSongsView::instance());
    viewController->setPlaylistSongsView(&PlaylistSongsView::instance());
    viewController->setFolderView(&FolderView::instance());

    qRegisterMetaType<std::shared_ptr<Song>>();

//    CoverArtHolder *coverArtHolder = new CoverArtHolder;

//    SongListModel *songModel = new SongListModel;
//    qmlRegisterSingletonInstance("com.c.SongModel", 1, 0, "SongModel", songModel);

//    SongFilterProxyModel *songFilterProxyModel = new SongFilterProxyModel;
//    songFilterProxyModel->setSourceModel(songModel);
//    songFilterProxyModel->setDynamicSortFilter(true);
//    songFilterProxyModel->sort(0, Qt::AscendingOrder);
//    qmlRegisterSingletonInstance("com.c.SongFilterProxyModel", 1,0 , "SongFilter", songFilterProxyModel);

//    AlbumListModel *albumListModel = new AlbumListModel;
//    //AlbumHolder *albumHolder = new AlbumHolder(albumListModel, songModel);
//    qmlRegisterSingletonInstance("com.c.AlbumListModel", 1, 0, "AlbumModel", albumListModel);

//    AlbumSearchFilter *albumSearchFilter = new AlbumSearchFilter;
//    albumSearchFilter->setSourceModel(albumListModel);
//    albumSearchFilter->sort(0, Qt::AscendingOrder);
//    albumSearchFilter->setDynamicSortFilter(true);
//    qmlRegisterSingletonInstance("com.c.AlbumSearchFilter",1, 0, "AlbumSearchModel", albumSearchFilter);

//    AlbumView *albumView = new AlbumView();
//    qmlRegisterSingletonInstance("com.c.AlbumView", 1, 0, "AlbumView", albumView);

//    AlbumSongsView *albumSongsView = new AlbumSongsView;
//    qmlRegisterSingletonInstance("com.c.AlbumSongsView", 1, 0, "AlbumSongsView", albumSongsView);

//    PlaylistModel *playlistModel = new PlaylistModel;
//    qmlRegisterSingletonInstance("com.c.PlaylistModel", 1, 0, "PlaylistModel", playlistModel);
//    PlaylistManager *playlistView = new PlaylistManager(playlistModel, songModel);
//    qmlRegisterSingletonInstance("com.c.PlaylistView", 1, 0, "PlaylistView", playlistView);

//    //SongHolder *songHolder = new SongHolder(songModel);
//    SongView *songView = new SongView();
//    qmlRegisterSingletonInstance("com.c.SongView", 1, 0, "SongView", songView);

//    FolderListModel *folderListModel = new FolderListModel;
//    qmlRegisterSingletonInstance("com.c.FolderModel", 1, 0, "FolderModel", folderListModel);

//    FolderView *folderView = new FolderView(songModel, albumListModel, folderListModel, coverArtHolder, QUrl::fromLocalFile("/Users/chids/Library/CloudStorage/OneDrive-UniversityofReading/Yeat - Up 2 Më"));
//    qmlRegisterSingletonInstance("com.c.FolderView", 1, 0, "FolderView", folderView);

//    AlbumFilterProxyModel *albumFilterProxyModel = new AlbumFilterProxyModel;
//    qmlRegisterSingletonInstance("com.c.AlbumFilterProxyModel", 1, 0,"AlbumFilterModel", albumFilterProxyModel);
//    albumFilterProxyModel->setSourceModel(songModel);
//    albumFilterProxyModel->sort(0, Qt::AscendingOrder);
//    albumFilterProxyModel->setDynamicSortFilter(true);

//    //NowPlaying *nowPlaying = new NowPlaying(songModel, albumListModel);
//    //qmlRegisterSingletonInstance("com.c.NowPlaying", 1, 0, "NowPlaying", nowPlaying);

//    //MediaPlayerController *controller = new MediaPlayerController(coverArtHolder, nowPlaying);
//    //qmlRegisterSingletonInstance("com.c.MediaController", 1, 0,"MediaPlayerController", controller);

//    //MusicLibrary *musicLibrary = new MusicLibrary(songModel, coverArtHolder, albumHolder);
//    //qmlRegisterSingletonInstance("com.c.MusicLibrary", 1, 0, "MusicLibrary", musicLibrary);

//    ViewController *viewController = new ViewController;
//    qmlRegisterSingletonInstance("com.c.ViewController", 1, 0, "ViewController", viewController);


    MediaImageProvider *mediaImageProvider = new MediaImageProvider;
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
