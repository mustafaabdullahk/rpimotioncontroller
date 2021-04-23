!drivers_include_guard {
	CONFIG +=  drivers_include_guard
	SOURCES += \


	HEADERS += \

	INCLUDEPATH += $$PWD

} 

HEADERS += \
    $$PWD/dac8532.h \
    $$PWD/config.h  \
    $$PWD/c_gpio.h  \
    $$PWD/c_spi.h \
    $$PWD/spidriver.h \
    $$PWD/ads1256.h

SOURCES += \
    $$PWD/dac8532.cpp \
    $$PWD/config.cpp  \
    $$PWD/c_gpio.c    \
    $$PWD/c_spi.c \
    $$PWD/spidriver.cpp \
    $$PWD/ads1256.cpp
