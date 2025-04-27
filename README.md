# cplayer

a simple, fast cross platform music player written with Qt (wip)

## reqs
1) Qt 6.8 [here](https://doc.qt.io/qt-6/qt-online-installation.html)
   - Make sure you select QMediaPlayer in the installer
2) vcpkg [here](https://learn.microsoft.com/en-us/vcpkg/get_started/get-started?pivots=shell-bash)
   - May want to add it to your path
3) cmake

## build
1) Install Qt 6.8 from [here](https://doc.qt.io/qt-6/qt-online-installation.html)
2) clone into this repo
3) run `git submodule --init` to fetch all submodules
4) build with cmake in ur fav ide or from command line


## screenshots
ui is bad i know, will do a full redesign
![image](https://github.com/user-attachments/assets/df0ef2a6-75e6-4c5e-841d-2faaabc3364f)
![image](https://github.com/user-attachments/assets/886f402f-c569-4b21-8312-1a42755db632)
![image](https://github.com/user-attachments/assets/123d7c0c-7aad-418d-9b8c-f5499338694d)

### todo
- save song edits to song file metadata (using tagwriter from taglib)
- allow drag and drop into window to add songs to library
- allow batch adding songs to album/batch metadata editing
- implement deemix web ui using QWebEngine to allow downloading songs within application
- create iphone app and android app to allow syncing songs between computer and phone
- last-fm integration to allow tracking listening history
- discord rpc support to show song being currently listened to on discord
- revamp ui so it doesnt look like shit
- write unit tests (i keep putting this off lol)




