#include "mediaplayercontroller.h"
#include <QFileDialog>
#include <QUrl>

// Constructor and Destructor
MediaPlayerController::MediaPlayerController(const CoverArtHolder *coverArtHolder, PlaylistManager *playlistManager, SongListModel *songModel, QObject *parent)
    : coverArtHolder(coverArtHolder), playlistManager(playlistManager), songModel(songModel), QObject(parent) {
    player = new QMediaPlayer;
    output = new QAudioOutput;

    connect(player, &QMediaPlayer::positionChanged, this, &MediaPlayerController::onPositionChanged);
    connect(player, &QMediaPlayer::durationChanged, this, &MediaPlayerController::durationChanged);
    connect(this, &MediaPlayerController::playingChanged, this, &MediaPlayerController::onPlayingChanged);

    connect(playlistManager, &PlaylistManager::playlistQueued, this, &MediaPlayerController::queueNext);
    connect(player, &QMediaPlayer::mediaStatusChanged, this, &MediaPlayerController::onMediaStatusChanged);

    m_volume = 0.2;
    output->setVolume(m_volume);
    player->setAudioOutput(output);
}

// Playback Control
void MediaPlayerController::playPause(bool newPlaying) {
    m_playing = !m_playing;
    emit playingChanged();
    emit updateUI();
}

void MediaPlayerController::togglePlayState() {
    playPause(true);
}

void MediaPlayerController::onMediaStatusChanged(QMediaPlayer::MediaStatus status){
    switch(status){

        case QMediaPlayer::EndOfMedia:
            //getNext song
            queueNext();
            break;
    }
}

void MediaPlayerController::onPlayingChanged() {
    if (m_playing) {
        player->play();
    } else {
        player->pause();
    }
}

bool MediaPlayerController::playing() const {
    return m_playing;
}

// Track Information
QString MediaPlayerController::leadingArtist() const {
    return m_leadingArtist;
}

QString MediaPlayerController::trackTitle() const {
    return m_trackTitle;
}

void MediaPlayerController::setTrackTitle(QString &title) {
    if (m_trackTitle != title) {
        m_trackTitle = title;
        emit trackTitleChanged();
    }
}

void MediaPlayerController::setLeadingArtist(QString &leadingArtist) {
    if (m_leadingArtist != leadingArtist) {
        m_leadingArtist = leadingArtist;
        emit leadingArtistChanged();
    }
}



// Player Position and Duration
qint64 MediaPlayerController::position() const {
    return player->position();
}

void MediaPlayerController::setPosition(qint64 newPosition) {
    if (player->position() != newPosition) {
        player->setPosition(newPosition);
    }
}

qint64 MediaPlayerController::duration() const {
    return player->duration();
}

void MediaPlayerController::onPositionChanged() {
    emit positionChanged();
}

// File and Album Management
QString MediaPlayerController::filePath() const {
    return m_filePath;
}

void MediaPlayerController::setFilePath(const QString &newFilePath) {
    if (m_filePath == newFilePath)
        return;
    m_filePath = newFilePath;
    emit filePathChanged();
}

QString MediaPlayerController::album() const {
    return m_album;
}

void MediaPlayerController::setAlbum(const QString &newAlbum) {
    if (m_album == newAlbum)
        return;
    m_album = newAlbum;
    emit albumChanged();
}

QStringList MediaPlayerController::features() const {
    return m_features;
}

void MediaPlayerController::setFeatures(const QStringList &newFeatures) {
    if (m_features != newFeatures) {
        m_features = newFeatures;
        emit featuresChanged();
    }
}

void MediaPlayerController::setSong(QString filePath, QString title, QString artist, QString album, QStringList features) {
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


void MediaPlayerController::queueNext()
{
    QString nextSongFilePath = playlistManager->getNextSong();

    if(nextSongFilePath != QString()){
        setSong(nextSongFilePath, songModel->getSongTitle(nextSongFilePath), songModel->getSongArtist(nextSongFilePath), songModel->getSongAlbum(nextSongFilePath), songModel->getSongFeatures(nextSongFilePath));
    }
}

void MediaPlayerController::queuePrevious()
{
    qDebug() << player->position();
    if(player->position() <= 4000){
        QString previousSongFilePath = playlistManager->getPreviousSong();

        if(previousSongFilePath != QString()){
            setSong(previousSongFilePath, songModel->getSongTitle(previousSongFilePath), songModel->getSongArtist(previousSongFilePath), songModel->getSongAlbum(previousSongFilePath), songModel->getSongFeatures(previousSongFilePath));
        }
    }
    else{
        player->setPosition(0);
    }
}


// Volume Control
float MediaPlayerController::volume() const {
    return m_volume;
}

void MediaPlayerController::setVolume(float newVolume) {
    if (m_volume != newVolume) {
        m_volume = newVolume;
        output->setVolume(newVolume);
        emit volumeChanged();
    }
}

// Utility Methods
QString MediaPlayerController::genTime(qint64 currentTime)
{
    int seconds = (currentTime / 1000) % 60;
    int minutes = (currentTime / (1000 * 60)) % 60;

    //formatting the result
    QString formattedTime;
    QTextStream stream(&formattedTime);

    if(minutes < 10){
        stream.setFieldWidth(2);
        stream.setPadChar('0');
        stream << minutes;
    }
    else if(minutes > 10){
        stream << minutes;
    }

    stream.setFieldWidth(0);
    stream << ":";
    stream.setFieldWidth(2);
    stream.setPadChar('0');
    stream << seconds;


    return formattedTime;
}


