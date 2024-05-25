#include "mediaplayercontroller.h"
#include <QFileDialog>
#include <QUrl>

MediaPlayerController::MediaPlayerController(const CoverArtHolder *coverArtHolder, QObject *parent) : coverArtHolder(coverArtHolder), QObject(parent) {
    player = new QMediaPlayer;
    output = new QAudioOutput;

    connect(player, &QMediaPlayer::positionChanged, this, &MediaPlayerController::onPositionChanged);
    connect(player, &QMediaPlayer::durationChanged, this, &MediaPlayerController::durationChanged);

    connect(this, &MediaPlayerController::playingChanged, this, &MediaPlayerController::onPlayingChanged);

    m_volume = 0.2;
    output->setVolume(m_volume);
    //emit volumeChanged();

    player->setAudioOutput(output);
}



int MediaPlayerController::currentSongIndex() const
{
    return m_currentSongIndex;
}


void MediaPlayerController::nextSong()
{
    m_currentSongIndex++;
    emit currentSongIndexChanged();
}

QString MediaPlayerController::leadingArtist() const
{
    return m_leadingArtist;
}

QString MediaPlayerController::trackTitle() const
{
    return m_trackTitle;
}


QPixmap MediaPlayerController::coverArt() const
{
    return m_coverArt;
}

void MediaPlayerController::setTrackTitle(QString &title){
    if(m_trackTitle != title){
        m_trackTitle = title;
        emit trackTitleChanged();
    }
}

void MediaPlayerController::setCoverArt(QPixmap coverArt){
    m_coverArt = coverArt;
    emit coverArtChanged();
}

void MediaPlayerController::setLeadingArtist(QString &leadingArtist){
    if(m_leadingArtist != leadingArtist){
        m_leadingArtist = leadingArtist;
        emit leadingArtistChanged();
    }
}

qint64 MediaPlayerController::position() const
{
    return player->position();
}

void MediaPlayerController::setPosition(qint64 newPosition)
{
    if(player->position() != newPosition){
        player->setPosition(newPosition);
    }
}

qint64 MediaPlayerController::duration() const
{
    return player->duration();
}

void MediaPlayerController::onPositionChanged(){
    emit positionChanged();
}


QString MediaPlayerController::filePath() const
{
    return m_filePath;
}

void MediaPlayerController::setFilePath(const QString &newFilePath)
{
    if (m_filePath == newFilePath)
        return;
    m_filePath = newFilePath;
    emit filePathChanged();
}

void MediaPlayerController::setSong(QString filePath, QString title, QString artist, QString album, QStringList features)
{
    player->stop();

    player->setSource(QUrl::fromLocalFile(filePath));
    setTrackTitle(title);
    setLeadingArtist(artist);
    setFilePath(filePath);
    setAlbum(album);
    setFeatures(features);
    emit coverArtChanged();
    emit leadingArtistChanged();

    m_playing = true;
    emit updateUI();
    player->play();

}

QPixmap MediaPlayerController::getCoverFromUrl(const char *filePath) const{
    TagLib::FileRef f(filePath);
    QPixmap loadedCover;


    if(!f.isNull() && f.tag()){
        TagLib::Tag *tag = f.tag();

        QStringList features;
        QString leadingArtist;

        QString title = QString::fromStdWString(tag->title().toWString());
        QString album = QString::fromStdWString(tag->album().toWString());

        TagLib::PropertyMap props = f.properties();
        TagLib::StringList artistList = props["ARTIST"];
        bool firstIter = true;

        for (const auto &artist : artistList){
            QString feature = QString::fromStdWString(artist.toWString());

            if(firstIter){
                leadingArtist = feature;
                firstIter = false;
            }
            else{
                qDebug() << "Featuring Artist:" << feature;
                features << feature;
            }
        }

        TagLib::StringList names = f.complexPropertyKeys();
        for(const auto &name : names){
            const auto& properties = f.complexProperties(name);
            for(const auto &property : properties){
                for(const auto &[key, value] : property){
                    if(value.type() == TagLib::Variant::ByteVector){
                        loadedCover.loadFromData(QByteArray::fromRawData(value.value<TagLib::ByteVector>().data(),value.value<TagLib::ByteVector>().size()));
                        loadedCover = loadedCover.scaled(80, 80, Qt::KeepAspectRatio, Qt::SmoothTransformation);
                    }
                }
            }
        }
    }

    return loadedCover;
}

void MediaPlayerController::playPause(bool newPlaying)
{
    m_playing = !m_playing;
    qDebug() << m_playing;
    emit playingChanged();
    emit updateUI();
}

void MediaPlayerController::onPlayingChanged(){
    qDebug() << "hello";
    if(m_playing){
        player->play();
    }
    else{
        player->pause();
    }
}

void MediaPlayerController::togglePlayState()
{
    playPause(true);
}

bool MediaPlayerController::playing() const{
    return m_playing;
}

QString MediaPlayerController::album() const
{
    return m_album;
}

void MediaPlayerController::setAlbum(const QString &newAlbum)
{
    if (m_album == newAlbum)
        return;
    m_album = newAlbum;
    emit albumChanged();
}

float MediaPlayerController::volume() const
{
    return m_volume;
}

void MediaPlayerController::setVolume(float newVolume)
{
    if (m_volume != newVolume){
        m_volume = newVolume;
        qDebug() << m_volume;
        output->setVolume(newVolume);
        emit volumeChanged();
    }
}

QStringList MediaPlayerController::features() const
{
    return m_features;
}

void MediaPlayerController::setFeatures(const QStringList &newFeatures)
{
    if (m_features == newFeatures)
        return;
    m_features = newFeatures;
    emit featuresChanged();
}
