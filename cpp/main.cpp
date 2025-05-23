#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QFontDatabase>
#include <QDebug>

#include "globalsingleton.h"
#include <pybind11/pybind11.h>

#if defined(Q_OS_WIN)
#include <windows.h>
#include <dwmapi.h>
#include <QQuickWindow>
#pragma comment(lib, "Dwmapi.lib")
#endif

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QCoreApplication::setOrganizationName("tecstars");
    QCoreApplication::setApplicationName("cplayer");

    QSettings settings;

    py::scoped_interpreter guard{};
    pybind11::gil_scoped_release release;

    int fontId = QFontDatabase::addApplicationFont(":/resource/ui/fonts/Satoshi-Medium.otf");

    if (fontId != -1) {
        QString fontFamily = QFontDatabase::applicationFontFamilies(fontId).at(0);
        // Set the application-wide font
        QGuiApplication::setFont(QFont(fontFamily));
    }

    PlaylistImageProvider *playlistProvider = new PlaylistImageProvider;
    CoverImgProvider *coverProvider = new CoverImgProvider;

    QQmlApplicationEngine engine;

    //for custom types used in signal/slots or that need to be written to and from QVariant
    qRegisterMetaType<QList<Folder>>();
    qRegisterMetaType<QList<int>>();
    qRegisterMetaType<QList<SongData>>();
    qRegisterMetaType<QList<Playlist>>();

    auto globalSingleton = engine.singletonInstance<GlobalSingleton*>("cplayer", "GlobalSingleton");

    engine.addImageProvider(QLatin1String("coverArt"), coverProvider);
    engine.addImageProvider(QLatin1String("playlistCovers"), playlistProvider);

    globalSingleton->init(coverProvider, playlistProvider);
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.loadFromModule("cplayer", "Main");

//changing color of titlebar on windows
#if defined(Q_OS_WIN)
    QQuickWindow *rootWindow = (QQuickWindow*)engine.rootObjects().first();
    HWND hwnd = reinterpret_cast<HWND>(rootWindow->winId());
    COLORREF titlebarColor = RGB(30, 30, 30); // Dark gray

    DwmSetWindowAttribute(hwnd, DWMWA_CAPTION_COLOR, &titlebarColor, sizeof(titlebarColor));
#endif

    return app.exec();
}
