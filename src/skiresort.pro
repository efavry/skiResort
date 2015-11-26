QMAKE_CXXFLAGS += -std=c++11 -Wall -Wextra
 HEADERS += \
         view/edge.h \
         view/node.h \
         view/graphwidget.h \
         view/graphpathwidget.h \
         view/rightwidget.h \
        mc/mc_readdb.h \
        mc/mc_node.h \
        mc/mc_edge.h \
        mc/mc_graph.h \
        mc_type.h \
        mc/mc_talker.h

 SOURCES += \
         view/edge.cpp \
         view/node.cpp \
         view/graphwidget.cpp \
         view/graphpathwidget.cpp \
         view/rightwidget.cpp \
        main.cpp \
        mc/mc_readdb.cpp \
        mc/mc_node.cpp \
        mc/mc_edge.cpp \
        mc/mc_graph.cpp \
        mc/mc_talker.cpp

