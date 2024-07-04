#include "mediaplayercontroller.h"

// Constructor and Destructor
MediaPlayerController::MediaPlayerController(const CoverArtHolder *coverArtHolder, NowPlaying *nowPlaying, QObject *parent)
    : coverArtHolder(coverArtHolder), nowPlaying(nowPlaying), QObject(parent) {
    player = new QMediaPlayer;
    output = new QAudioOutput;

    connect(player, &QMediaPlayer::positionChanged, this, &MediaPlayerController::onPositionChanged);
    connect(player, &QMediaPlayer::durationChanged, this, &MediaPlayerController::durationChanged);
    connect(this, &MediaPlayerController::playingChanged, this, &MediaPlayerController::onPlayingChanged);
    connect(this, &MediaPlayerController::nextSong, nowPlaying, &NowPlaying::onNextClicked);
    connect(this, &MediaPlayerController::previousSong, nowPlaying, &NowPlaying::onPreviousClicked);

    connect(nowPlaying, &NowPlaying::playSong, this, &MediaPlayerController::onPlaySong);
    connect(nowPlaying, &NowPlaying::jumpToEnd, this, &MediaPlayerController::onJumpToEnd);

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
            nextClicked();
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

    emit positionChanged();
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

void MediaPlayerController::onPlaySong(std::shared_ptr<Song> song) {
    player->stop();

    player->setSource(QUrl::fromLocalFile(song->filePath));
    setTrackTitle(song->title);
    setLeadingArtist(song->artist);
    setFilePath(song->filePath);
    setAlbum(song->album);
    setFeatures(song->featuringArtists);

    emit coverArtChanged();
    emit leadingArtistChanged();

    m_playing = true;
    emit updateUI();
    player->play();
}


void MediaPlayerController::nextClicked()
{
    emit nextSong();
}

void MediaPlayerController::previousClicked()
{
    emit previousSong(player->position());
}

void MediaPlayerController::onJumpToEnd(){
    player->setPosition(player->duration());
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


