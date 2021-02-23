QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets# 3dcore

CONFIG += c++11

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
    application.cpp \
    camera.cpp \
    geometry.cpp \
    geometry2.cpp \
    inputmanager.cpp \
    main.cpp \
    mainwindow.cpp \
    material.cpp \
    memorypool.cpp \
    mesh.cpp \
    navigationtool.cpp \
    object3d.cpp \
    scene.cpp \
    scenetreemodel.cpp \
    selectiontool.cpp \
    splitedgetool.cpp \
    tool.cpp \
    transform3d.cpp \
    transformtool.cpp \
    vertex.cpp \
    viewport.cpp \
    viewportaxis.cpp \
    viewportgrid.cpp

HEADERS += \
    application.h \
    camera.h \
    geometry.h \
    geometry2.h \
    inputmanager.h \
    mainwindow.h \
    material.h \
    memorypool.h \
    mesh.h \
    navigationtool.h \
    object3d.h \
    scene.h \
    scenetreemodel.h \
    selectiontool.h \
    splitedgetool.h \
    tool.h \
    transform3d.h \
    transformtool.h \
    vertex.h \
    viewport.h \
    viewportaxis.h \
    viewportgrid.h

FORMS += \
    mainwindow.ui


win32 {
    LIBS += opengl32.lib
}

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    shaders.qrc
