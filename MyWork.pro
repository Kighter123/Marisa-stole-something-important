QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    GameWindow.cpp \
    Ground.cpp \
    HorizontalObstacle.cpp \
    Obstacle.cpp \
    Player.cpp \
    RewardBlock.cpp \
    main.cpp

HEADERS += \
    GameWindow.h \
    Ground.h \
    HorizontalObstacle.h \
    Obstacle.h \
    Player.h \
    RewardBlock.h

FORMS += \
    GameWindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
