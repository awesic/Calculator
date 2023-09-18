QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

CONFIG += c++11
CONFIG += sdk_no_version_check
QMAKE_CFLAGS_WARN_ON -= -Wextra
QMAKE_CXXFLAGS_WARN_ON -= -Wextra

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../Calculator/QCustomPlotLib/qcustomplot.cpp \
    ../Calculator/calculation.c \
    ../Calculator/creditmodel.cpp \
    ../Calculator/depositmodel.cpp \
    ../Calculator/main.cpp \
    ../Calculator/mainwindow.cpp \
    ../Calculator/parsing.c \
    ../Calculator/plotgraphic.cpp \
    ../Calculator/queue.c \
    ../Calculator/stack.c \
    ../Calculator/validator.c

HEADERS += \
    ../Calculator/QCustomPlotLib/qcustomplot.h \
    ../Calculator/creditmodel.h \
    ../Calculator/defines.h \
    ../Calculator/depositmodel.h \
    ../Calculator/mainwindow.h \
    ../Calculator/plotgraphic.h \
    ../Calculator/queue_stack.h \
    ../Calculator/calc.h \
    ../Calculator/validator.h

FORMS += \
    ../Calculator/mainwindow.ui \
    ../Calculator/plotgraphic.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

