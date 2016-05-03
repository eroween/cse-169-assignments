QT       += core gui widgets

TARGET = cube
TEMPLATE = app

SOURCES += main.cpp \
    node.cpp \
    transform.cpp \
    animation.cpp \
    entity.cpp \
    object.cpp \
    skeleton_loader.cpp \
    skeleton.cpp \
    joint.cpp \
    balljoint.cpp \
    mesh.cpp \
    cube.cpp \
    skin_loader.cpp \
    skin.cpp \
    mainwindow.cpp

SOURCES += \
    mainwidget.cpp \
    geometryengine.cpp

HEADERS += \
    mainwidget.h \
    geometryengine.h \
    node.hpp \
    transform.hpp \
    animation.hpp \
    entity.hpp \
    object.hpp \
    skeleton_loader.hpp \
    skeleton.hpp \
    joint.hpp \
    balljoint.hpp \
    mesh.hpp \
    cube.hpp \
    skin_loader.hpp \
    skin.hpp \
    mainwindow.h

RESOURCES += \
    shaders.qrc \
    textures.qrc

# install
target.path =
INSTALLS += target

DISTFILES += \
    anim_vertex.glsl

FORMS += \
    mainwindow.ui
