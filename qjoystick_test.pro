
CONFIG += c++11

HEADERS += \
	qjoystick.h \
    	JoystickMonitor.h 
    


SOURCES += \
	qjoystick.cpp \
        JoystickMonitor.cpp \
        main.cpp 

target.path = /home/qgnk/github/qjoystick
INSTALLS += target
