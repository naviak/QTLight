QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += core gui widgets opengl

CONFIG += c++17

LIBS += -lopengl32

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    cube.cpp \
    cubewidget.cpp \
    main.cpp \
    mainwindow.cpp \
    square.cpp \
    transformable.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    cube.h \
    cubewidget.h \
    globject.h \
    mainwindow.h \
    plainglobject.h \
    square.h \
    transformable.h

RESOURCES += \
    shaders.qrc

DISTFILES += \
    vertex.vsh \
    fragment.fsh

FORMS += \
    mainwindow.ui
