#-------------------------------------------------
#
# Project created by QtCreator 2024-11-25T20:39:31
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MultiFun_Cabinet
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        mainwindow.cpp \
    DeviceIo/bluetooth.c

HEADERS  += mainwindow.h \
    DeviceIo/bluetooth.h \
    DeviceIo/bt_manager_1s2.h \
    DeviceIo/DeviceIo.h \
    DeviceIo/InfoLed.h \
    DeviceIo/Memory.h \
    DeviceIo/NetLinkWrapper.h \
    DeviceIo/Properties.h \
    DeviceIo/Rk_audio.h \
    DeviceIo/Rk_battery.h \
    DeviceIo/RK_encode.h \
    DeviceIo/Rk_key.h \
    DeviceIo/Rk_led.h \
    DeviceIo/RK_log.h \
    DeviceIo/RK_property.h \
    DeviceIo/Rk_shell.h \
    DeviceIo/Rk_socket_app.h \
    DeviceIo/Rk_softap.h \
    DeviceIo/Rk_system.h \
    DeviceIo/RK_timer.h \
    DeviceIo/Rk_wake_lock.h \
    DeviceIo/Rk_wifi.h \
    DeviceIo/RkBle.h \
    DeviceIo/RkBleClient.h \
    DeviceIo/RkBtBase.h \
    DeviceIo/RkBtHfp.h \
    DeviceIo/RkBtObex.h \
    DeviceIo/RkBtPan.h \
    DeviceIo/RkBtSink.h \
    DeviceIo/RkBtSource.h \
    DeviceIo/RkBtSpp.h \
    DeviceIo/ScanResult.h \
    DeviceIo/WifiInfo.h \
    DeviceIo/WifiManager.h

FORMS    += mainwindow.ui
LIBS += -lm  -lpaho-mqtt3cs -lcurl
LIBS += -L$$PWD/lib/ -lrtsp -lDeviceIo -leasymedia -lrkaiq  -lrockx -lrknn_api -lm -lrga -Wl,-rpath-link,$$PWD/lib/
