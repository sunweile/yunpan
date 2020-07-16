QT       += core gui webengine webenginewidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11 debug

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    BaiDuClient.cpp \
    DetailedFileView.cpp \
    DiskClient.cpp \
    DiskHandleClient.cpp \
    FileButton.cpp \
    FileStreamItem.cpp \
    FileStreamView.cpp \
    FileStringTools.cpp \
    FileWebManager.cpp \
    FileWorker.cpp \
    FilesTreeButton.cpp \
    FilesTreeView.cpp \
    FtpClient.cpp \
    GCManager.cpp \
    JianGuoClient.cpp \
    LocalDiskClient.cpp \
    LocationView.cpp \
    LoginDialog.cpp \
    LoginView.cpp \
    MainWindows.cpp \
    ReadDataFile.cpp \
    TopMainMenu.cpp \
    TopMenuView.cpp \
    User.cpp \
    UserHandle.cpp \
    VirtualDisk.cpp \
    WebView.cpp \
    YpButton.cpp \
    YpLine.cpp \
    YpList.cpp \
    fileSenceView.cpp \
    main.cpp

HEADERS += \
    BaiDuClient.h \
    DetailedFileView.h \
    DiskClient.h \
    DiskHandleClient.h \
    FileButton.h \
    FileStreamItem.h \
    FileStreamView.h \
    FileStringTools.h \
    FileWebManager.h \
    FileWorker.h \
    FilesTreeButton.h \
    FilesTreeView.h \
    FtpClient.h \
    GCManager.h \
    JianGuoClient.h \
    LocalDiskClient.h \
    LocationView.h \
    LoginDialog.h \
    LoginView.h \
    MainWindows.h \
    ReadDataFile.h \
    TopMainMenu.h \
    TopMenuView.h \
    User.h \
    UserHandle.h \
    VirtualDisk.h \
    WebView.h \
    YpButton.h \
    YpLine.h \
    YpList.h \
    fileSenceView.h

FORMS += \
    LoginView.ui \
    MainWindows.ui

TRANSLATIONS += \
    untitled_zh_CN.ts

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    LoginView.qrc
