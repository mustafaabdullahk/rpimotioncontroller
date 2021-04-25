!drivers_include_guard {
	CONFIG +=  drivers_include_guard
	SOURCES += \


	HEADERS += \

	INCLUDEPATH += $$PWD

} 

HEADERS += \
    $$PWD/dac8532.h \
    $$PWD/config.h  \
    $$PWD/spidriver.h \
    $$PWD/ads1256.h \
    $$PWD/gpiodriver.h

SOURCES += \
    $$PWD/dac8532.cpp \
    $$PWD/config.cpp  \
    $$PWD/spidriver.cpp \
    $$PWD/ads1256.cpp \
    $$PWD/gpiodriver.cpp
