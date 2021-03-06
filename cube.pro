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
    mainwindow.cpp \
    channel.cpp \
    animationloader.cpp \
    animationplayer.cpp \
    cloth.cpp \
    particle.cpp \
    springdamper.cpp \
    environment.cpp \
    triangle.cpp \
    plane.cpp \
    fluidsystem.cpp

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
    mainwindow.h \
    channel.hpp \
    animationloader.hpp \
    animationplayer.hpp \
    cloth.hpp \
    particle.hpp \
    springdamper.hpp \
    environment.hpp \
    triangle.hpp \
    plane.hpp \
    fluidsystem.hpp \
    sphere.hpp

RESOURCES += \
    shaders.qrc \
    textures.qrc

# install
target.path =
INSTALLS += target

DISTFILES += \
    anim_vertex.glsl \
    instanced_render.vsh \
    instanced.vert

FORMS += \
    mainwindow.ui

QMAKE_CXXFLAGS+= -fopenmp
QMAKE_LFLAGS +=  -fopenmp
