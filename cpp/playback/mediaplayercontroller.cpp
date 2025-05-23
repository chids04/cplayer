#include "mediaplayercontroller.h"

#include <QMediaPlayer>
#include <QAudioOutput>
#include <QTextStream>
#include <QMediaDevices>
#include <QAudioDevice>
#include <QMediaMetaData>

#include "nowplaying.h"

// Constructor and Destructor
MediaPlayerController::MediaPlayerController(QObject *parent)
    : QObject(parent) {
    player = new QMediaPlayer;
    output = new QAudioOutput;
    mediaDevices = new QMediaDevices;

    setAudioDeviceModel(new AudioDeviceModel);

    connect(player, &QMediaPlayer::positionChanged, this, &MediaPlayerController::onPositionChanged);
    connect(player, &QMediaPlayer::durationChanged, this, &MediaPlayerController::durationChanged);
    connect(mediaDevices, &QMediaDevices::audioOutputsChanged, this, &MediaPlayerController::onAudioDeviceChanged);
    connect(m_audioDeviceModel, &AudioDeviceModel::audioDeviceChanged, this, &MediaPlayerController::setAudioDevice);

    connect(this, &MediaPlayerController::playingChanged, this, &MediaPlayerController::onPlayingChanged);
    connect(player, &QMediaPlayer::mediaStatusChanged, this, &MediaPlayerController::onMediaStatusChanged);


    m_volume = 0.2;
    output->setVolume(m_volume);
    player->setAudioOutput(output);
}

MediaPlayerController &MediaPlayerController::instance()
{
    static MediaPlayerController mediaPlayerController;
    return mediaPlayerController;
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

        case QMediaPlayer::LoadedMedia:
            //only set position if this is the first song that has been loaded
            if(firstSong){
                player->setPosition(posFromFile);
                firstSong = false;
                break;
            }
        }
}

void MediaPlayerController::onAudioDeviceChanged(){
    if(player->playbackState() == QMediaPlayer::PlayingState){
        m_playing = false;
        emit playingChanged();
        emit updateUI();
    }

    const QList<QAudioDevice> audioDevices = QMediaDevices::audioOutputs();

    if(!audioDevices.isEmpty()){
        QAudioDevice default_device = QMediaDevices::defaultAudioOutput();
        output->setDevice(default_device);

    }

}

void MediaPlayerController::setAudioDevice(const QAudioDevice &device)
{
    output->setDevice(device);
}

void MediaPlayerController::onPlayingChanged() {
    if (m_playing) {
        //check if there are items in queue to play if no song loaded
        if(player->source() == QUrl()){
            emit checkQueue();
        }
        else{
            player->play();
        }
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

void MediaPlayerController::setTrackTitle(const QString &title) {
    if (m_trackTitle != title) {
        m_trackTitle = title;
        emit trackTitleChanged();
    }
}

void MediaPlayerController::setLeadingArtist(const QString &leadingArtist) {
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

void MediaPlayerController::updateSong(Song *song)
{
    setTrackTitle(song->m_title);
    setLeadingArtist(song->m_artist);
    setAlbum(song->m_album);
    setFeatures(song->m_featuringArtists);
    setAlbumArtists(song->m_albumArtists);

}

void MediaPlayerController::onPlaySong(Song* song) {
    player->stop();

    player->setSource(QUrl::fromLocalFile(song->m_filePath));
    setTrackTitle(song->m_title);
    setLeadingArtist(song->m_artist);
    setFilePath(song->m_filePath);
    setAlbum(song->m_album);
    setFeatures(song->m_featuringArtists);
    setAlbumArtists(song->m_albumArtists);

    emit coverArtChanged();
    emit leadingArtistChanged();

    m_playing = true;
    emit updateUI();
    player->play();
}

void MediaPlayerController::onSongLoaded(Song* song)
{

    player->setSource(QUrl::fromLocalFile(song->m_filePath));

    setTrackTitle(song->m_title);
    setLeadingArtist(song->m_artist);
    setFilePath(song->m_filePath);
    setAlbum(song->m_album);
    setFeatures(song->m_featuringArtists);
    setAlbumArtists(song->m_albumArtists);

    emit coverArtChanged();
    emit leadingArtistChanged();
    emit updateUI();
    emit positionChanged();

}

void MediaPlayerController::onRepeatChanged(bool repeat)
{
    if(repeat){
        player->setLoops(QMediaPlayer::Infinite);
        m_repeat = true;
    }
    else{
        player->setLoops(QMediaPlayer::Once);
        m_repeat = false;
    }
}

void MediaPlayerController::onPositionLoaded(qint64 position)
{
    posFromFile = position;
}

void MediaPlayerController::onRemoveCurrentPlaying(const QString &filePath)
{
    if(filePath == m_filePath){
        player->setSource(QUrl());

        QString str = " ";
        setTrackTitle(str);
        setLeadingArtist(str);
        setFilePath(str);
        setAlbum(str);
        setFeatures(QStringList());
        m_duration = 0;

        emit coverArtChanged();
        emit leadingArtistChanged();
        emit updateUI();
        emit resetDuration();
    }
}

void MediaPlayerController::nextClicked()
{
    if(m_repeat){
        player->setPosition(0);
    }
    else{
        emit nextSong();
    }
}

void MediaPlayerController::previousClicked()
{
    if(m_repeat){
        player->setPosition(0);
    }
    else{
        emit previousSong(player->position());
    }
}

void MediaPlayerController::onJumpToEnd(){
    m_playing = false;
    emit updateUI();
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



bool MediaPlayerController::repeat() const
{
    return m_repeat;
}

void MediaPlayerController::setRepeat(bool newRepeat)
{
    if (m_repeat == newRepeat)
        return;
    m_repeat = newRepeat;
    emit repeatChanged();
}

void MediaPlayerController::onDurationChanged(qint64 newDuration)
{
    if (m_duration == newDuration)
        return;
    m_duration = newDuration;
    emit durationChanged();
}

AudioDeviceModel *MediaPlayerController::audioDeviceModel() const
{
    return m_audioDeviceModel;
}

void MediaPlayerController::setAudioDeviceModel(AudioDeviceModel *newAudioDeviceModel)
{
    if (m_audioDeviceModel == newAudioDeviceModel)
        return;
    m_audioDeviceModel = newAudioDeviceModel;
    emit audioDeviceModelChanged();
}


QStringList MediaPlayerController::albumArtists() const
{
    return m_albumArtists;
}

void MediaPlayerController::setAlbumArtists(const QStringList &newAlbumArtists)
{
    if (m_albumArtists == newAlbumArtists)
        return;
    m_albumArtists = newAlbumArtists;
    emit albumArtistsChanged();
}
