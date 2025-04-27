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
![image](https://github.com/user-attachments/assets/a8593829-45e0-448a-8c64-5895f32b35e6)
![image](https://github.com/user-attachments/assets/8b259440-c43f-47b4-9ca9-df4736e60884)
![image](https://github.com/user-attachments/assets/1e139440-9f5c-4741-9c16-b8dd40bef1b9)


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




