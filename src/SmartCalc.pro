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
    ../SmartCalc/QCustomPlotLib/qcustomplot.cpp \
    ../SmartCalc/calculation.c \
    ../SmartCalc/creditmodel.cpp \
    ../SmartCalc/depositmodel.cpp \
    ../SmartCalc/main.cpp \
    ../SmartCalc/mainwindow.cpp \
    ../SmartCalc/parsing.c \
    ../SmartCalc/plotgraphic.cpp \
    ../SmartCalc/queue.c \
    ../SmartCalc/stack.c \
    ../SmartCalc/validator.c

HEADERS += \
    ../SmartCalc/QCustomPlotLib/qcustomplot.h \
    ../SmartCalc/creditmodel.h \
    ../SmartCalc/defines.h \
    ../SmartCalc/depositmodel.h \
    ../SmartCalc/mainwindow.h \
    ../SmartCalc/plotgraphic.h \
    ../SmartCalc/queue_stack.h \
    ../SmartCalc/smartcalc.h \
    ../SmartCalc/validator.h

FORMS += \
    ../SmartCalc/mainwindow.ui \
    ../SmartCalc/plotgraphic.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

