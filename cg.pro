QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    component/bezier.cpp \
    component/myslider.cpp \
    include/camera.cpp \
    include/skybox.cpp \
    resourcemangager/model.cpp \
    resourcemangager/resourcemanager.cpp \
    resourcemangager/shader.cpp \
    resourcemangager/texture2d.cpp \
    component/component.cpp \
    widget/mainwindow.cpp \
    widget/paintingboard.cpp \
    main.cpp \
    widget/renderScene.cpp

HEADERS += \
    component/bezier.h \
    component/myslider.h \
    include/camera.h \
    include/skybox.h \
    resourcemangager/model.h \
    resourcemangager/resourcemanager.h \
    resourcemangager/shader.h \
    resourcemangager/texture2d.h \
    component/component.h \
    widget/mainwindow.h \
    widget/paintingboard.h \
    widget/renderScene.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource/res.qrc
