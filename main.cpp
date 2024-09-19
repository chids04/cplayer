#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QFontDatabase>

#include "mediaplayercontroller.h"
#include "mediaimageprovider.h"
#include "viewcontroller.h"
#include "albumfilterproxymodel.h"
#include "folderlistmodel.h"
#include "albumsongsview.h"
#include "folderview.h"
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

    QCoreApplication::setOrganizationName("tecstars");
    QCoreApplication::setApplicationName("cplayer");

    int fontId = QFontDatabase::addApplicationFont(":/resource/ui/fonts/Satoshi-Medium.otf");

    if (fontId != -1) {
        QString fontFamily = QFontDatabase::applicationFontFamilies(fontId).at(0);
        // Set the application-wide font
        QGuiApplication::setFont(QFont(fontFamily));
    }

    QQmlApplicationEngine engine;

    qRegisterMetaType<std::shared_ptr<Song>>();
    qRegisterMetaType<QList<Folder>>();

    auto modelHandler = engine.singletonInstance<ModelHandler *>("cplayer", "ModelHandler");
    modelHandler->setSongList(&SongFilterProxyModel::instance());
    modelHandler->setAlbumList(&AlbumSearchFilter::instance());
    modelHandler->setAlbumSongs(&AlbumFilterProxyModel::instance());
    modelHandler->setPlaylistList(&PlaylistModel::instance());
    modelHandler->setFolderList(&FolderListModel::instance());
    modelHandler->setSettingsManager(&SettingsManager::instance());


    auto musicHandler = engine.singletonInstance<MusicHandler *>("cplayer", "MusicHandler");
    musicHandler->setMediaPlayerController(&MediaPlayerController::instance());
    musicHandler->setNowPlaying(&NowPlaying::instance());
    musicHandler->setPlaylistManager(&PlaylistManager::instance());

    auto viewController = engine.singletonInstance<ViewController *>("cplayer", "ViewController");
    viewController->setAlbumSongsView(&AlbumSongsView::instance());
    viewController->setPlaylistSongsView(&PlaylistSongsView::instance());
    viewController->setFolderView(&FolderView::instance());

    MediaImageProvider *mediaImageProvider = new MediaImageProvider;
    engine.addImageProvider(QLatin1String("coverArt"), mediaImageProvider);

    if(SettingsManager::instance().hasFolder()){
        SettingsManager::instance().readFolders();
    }


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
