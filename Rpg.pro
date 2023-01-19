QT += quick\
        svg\
        network\


SOURCES += \
    firebasehandler.cpp \
    main.cpp \

resources.files = main.qml
resources.prefix = /$${TARGET}
RESOURCES += resources

TRANSLATIONS += \
    Rpg_pt_BR.ts
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    firebasehandler.h

android: include(android_openssl-master/openssl.pri)
