QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

CONFIG += qwt
INCLUDEPATH += /usr/local/qwt-6.3.0/include
include ( /usr/local/qwt-6.3.0/features/qwt.prf )
LIBS += -L/usr/local/qwt-6.3.0/lib -lqwt

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    src/eigenvalueode.cpp \
    src/main.cpp \
    src/mainwindow.cpp \
    src/plot.cpp

HEADERS += \
    include/mainwindow.h \
    include/eigenvalueode.h \
    include/plot.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
