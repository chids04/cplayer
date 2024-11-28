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
#include "utilitysingleton.h"
#include "playlistfilter.h"
#include "playlistimageprovider.h"

#include <QDebug>

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

    //for custom types used in signal/slots or that need to be written to and from QVariant
    qRegisterMetaType<std::shared_ptr<Song>>();
    qRegisterMetaType<QList<Folder>>();
    qRegisterMetaType<QList<int>>();
    qRegisterMetaType<QList<Song>>();
    qRegisterMetaType<QList<Playlist>>();

    auto modelHandler = engine.singletonInstance<ModelHandler *>("cplayer", "ModelHandler");
    modelHandler->setSongList(&SongFilterProxyModel::instance());
    modelHandler->setAlbumList(&AlbumSearchFilter::instance());
    modelHandler->setAlbumSongs(&AlbumFilterProxyModel::instance());
    modelHandler->setPlaylistList(&PlaylistModel::instance());
    modelHandler->setFolderList(&FolderListModel::instance());
    modelHandler->setSettingsManager(&SettingsManager::instance());
    modelHandler->setPlaylistFilter(&PlaylistFilter::instance());


    auto musicHandler = engine.singletonInstance<MusicHandler *>("cplayer", "MusicHandler");
    musicHandler->setMediaPlayerController(&MediaPlayerController::instance());
    musicHandler->setNowPlaying(&NowPlaying::instance());
    musicHandler->setPlaylistManager(&PlaylistManager::instance());

    auto viewController = engine.singletonInstance<ViewController *>("cplayer", "ViewController");
    viewController->setAlbumSongsView(&AlbumSongsView::instance());
    viewController->setPlaylistSongsView(&PlaylistSongsView::instance());
    viewController->setFolderView(&FolderView::instance());

    auto utilitySingleton = engine.singletonInstance<UtilitySingleton *>("cplayer", "UtilitySingleton");
    utilitySingleton->setSettingsManager(&SettingsManager::instance());

    MediaImageProvider *mediaImageProvider = new MediaImageProvider;

    engine.addImageProvider(QLatin1String("coverArt"), mediaImageProvider);
    engine.addImageProvider(QLatin1String("playlistCovers"), &PlaylistImageProvider::instance());

    if(SettingsManager::instance().hasFolder()){
        SettingsManager::instance().setup();
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
