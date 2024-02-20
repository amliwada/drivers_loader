QT += quick

CONFIG += c++17

SOURCES += \
    sources/main.cpp \
    sources/application.cpp \
    sources/application_attributes_setter.cpp \
    sources/application_translator.cpp \
    sources/qml_engine.cpp \
    sources/command.cpp \
    sources/sc.cpp \
    sources/shell_execute.cpp \
    sources/shell_execute_exception.cpp

HEADERS += \
    include/drivers_loader/application.hpp \
    include/drivers_loader/application_attributes_setter.hpp \
    include/drivers_loader/application_translator.hpp \
    include/drivers_loader/qml_engine.hpp \
    include/drivers_loader/sc.hpp \
    include/drivers_loader/command.hpp \
    include/drivers_loader/shell_execute.hpp \
    include/drivers_loader/shell_execute_exception.hpp

INCLUDEPATH += \
    include/

RESOURCES += \
    qml/qml.qrc

CONFIG += lrelease

QML_IMPORT_PATH =

QML_DESIGNER_IMPORT_PATH =

qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target