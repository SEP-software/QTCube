INCLUDEPATH += . .. ../base ../gui ${SEP}/include
TEMPLATE = app
SOURCES += main.cpp
CONFIG+=staticlib
LIBS+= -L../base -L../gui -L${SEP}/lib -lgui -lbase  -lsep3d -lsep
TARGET= ../qt_cube
RESOURCES=qt_cube.qrc
ICON=qt_cube.icns
