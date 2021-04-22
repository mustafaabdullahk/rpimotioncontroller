
!loguru_include_guard{
    CONFIG += loguru_include_guard

    DEFINES += LOGURU_WITH_STREAMS

    SOURCES += $$PWD/loguru.cpp $$PWD/debug.cpp
    HEADERS += $$PWD/loguru.hpp $$PWD/debug.h

    INCLUDEPATH += $$PWD/../

    LIBS += -ldl -lpthread
}
