TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp

HEADERS += \
    token.h \
    number.h \
    operator.h \
    variable.h \
    rpn.h \
    shunting_yard.h \
    ../../include/MyStack.h \
    ../../include/myvector.h \
    ../../include/myqueue.h
