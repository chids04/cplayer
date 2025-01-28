# cplayer

a simple, fast cross platform music player written with Qt (wip)

## build
1) Install Qt 6.8 from [here](https://doc.qt.io/qt-6/qt-online-installation.html)
2) clone into this repo
3) run `git submodule --init` to fetch all submodules

### windows
- use MSVC compiler kit in qt creator
build [taglib](https://github.com/taglib/taglib/blob/master/INSTALL.md#build-options)
  - follow the MSVC build and install instructions, including the installtion of vcpkg and zlib
  - makes sure `-DENABLE_STATIC_RUNTIME=ON` `-DBUILD_SHARED_LIBS=OFF` are added to the cmake build command
  - ammend the line `set(TagLib_DIR "C:\\pkg_static\\lib\\cmake\\taglib")` in CMakeLists.txt to match directoy of where you installed taglib

### mac
1. install [homebrew](https://brew.sh/)
2. install zlib and utf8cpp `brew install zlib utf8cpp`
3. install taglib `brew install taglib --HEAD`
4. make sure you have added your brew library install directory to the PATH variable

### linux
not tested on linux yet but if taglib is not in your fav package manager, you may need to [build from source](https://github.com/taglib/taglib/blob/master/INSTALL.md)

## screenshots
ui is bad i know, will do a full redesign
![image](https://github.com/user-attachments/assets/df0ef2a6-75e6-4c5e-841d-2faaabc3364f)
![image](https://github.com/user-attachments/assets/886f402f-c569-4b21-8312-1a42755db632)
![image](https://github.com/user-attachments/assets/123d7c0c-7aad-418d-9b8c-f5499338694d)

### todo
- save song edits to song file metadata (using tagreader)
- allow drag and drop into window to add songs to library
- allow batch adding songs to album/batch metadata editing
- implement deemix web ui using QWebEngine to allow downloading songs within application
- create iphone app and android app to allow syncing songs between computer and phone
- last-fm integration to allow tracking listening history
- discord rpc support to show song being currently listened to
- revamp ui so it doesnt look like shit




