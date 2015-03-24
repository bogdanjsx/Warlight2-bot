######################################################################
# Automatically generated by qmake (3.0) So. Nov. 23 21:57:54 2014
######################################################################

QT -= core gui
TEMPLATE = app
TARGET = starterbot
INCLUDEPATH = .
CONFIG += c++11 debug
QMAKE_CXXFLAGS_DEBUG +=  -DSTARTERBOT_DEBUG

# add tagret to zip your bot
zip.target = zip
zip.commands = rm -f bot.zip && mkdir -p target \
	&& cp -r $$PWD/*.h target/ \
	&& cp -r $$PWD/*.cpp  target/ \
	&& cp -r $$PWD/tools/ target/ \
	&& cd target \
	&& zip -r ../bot.zip ./* \
	&& cd .. \
	&& rm -r target
zip.depends = starterbot

QMAKE_EXTRA_TARGETS += zip

# Input
SOURCES += Bot.cpp main.cpp Parser.cpp Region.cpp SuperRegion.cpp Movement.cpp Project.cpp MapSearch.cpp

