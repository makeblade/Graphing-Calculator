TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

CONFIG += c++11

#WINDOWS
# put SFML file in the same location as project
LIBS += -L"..\..\SFML-2.5.1\lib" #change this
LIBS += -L"..\..\SFML-2.5.1\bin" #change this

#MAC
#LIBS += -L"/usr/local/lib"

CONFIG(release, debug|release): LIBS += -lsfml-audio -lsfml-graphics -lsfml-system -lsfml-network -lsfml-window
CONFIG(debug  , debug|release): LIBS += -lsfml-audio -lsfml-graphics -lsfml-system -lsfml-network -lsfml-window

#WINDOWS
INCLUDEPATH += "..\..\SFML-2.5.1\include" #change this
DEPENDPATH  += "..\..\SFML-2.5.1\include" #change this

#MAC
#INCLUDEPATH += "/usr/local/include"
#DEPENDPATH += "/usr/local/include"

#To Here


SOURCES += main.cpp \
    anime.cpp \
    button.cpp \
    graph.cpp \
    graph_infor.cpp \
    plot.cpp \
    rec_button.cpp \
    sidebar.cpp \
    text_button.cpp \
    ../../../RPN/RPN/number.cpp \
    ../../../RPN/RPN/operator.cpp \
    ../../../RPN/RPN/rpn.cpp \
    ../../../RPN/RPN/shunting_yard.cpp \
    ../../../RPN/RPN/token.cpp \
    ../../../RPN/RPN/variable.cpp

HEADERS += \
    graph_infor.h \
    plot.h \
    ../../../include/myqueue.h \
    ../../../include/MyStack.h \
    ../../../include/myvector.h \
    ../../../RPN/RPN/number.h \
    ../../../RPN/RPN/operator.h \
    ../../../RPN/RPN/rpn.h \
    ../../../RPN/RPN/shunting_yard.h \
    ../../../RPN/RPN/token.h \
    ../../../RPN/RPN/variable.h \
    anime.h \
    ../../../RPN/RPN/shunting_yard.h \
    sidebar.h \
    graph.h \
    constant.h \
    button.h \
    rec_button.h \
    text_button.h \
    z_readme.h \
    z_workreport.h

DISTFILES += \
    ../Font/PlayfairDisplay-Black.otf \
    ../Data/History.txt \
    ../Data/delete_icon.png \
    ../Data/Backup.txt \
    ../Data/Setting.txt \
    ../Share_Font/Share-Tech.otf
