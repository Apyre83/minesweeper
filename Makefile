CXX = g++
TARGET = Minesweeper

SOURCES = srcs/main.cpp \
          srcs/model/Cell.cpp \
          srcs/model/Grid.cpp \
          srcs/controller/GameController.cpp \
          srcs/view/CellButton.cpp \
          srcs/view/MainWindow.cpp \
          srcs/utils/Command.cpp

INCLUDE = include/

OBJECTS = $(SOURCES:.cpp=.o)

PKG_CONFIG = pkg-config
GTKMM_CFLAGS = $(shell $(PKG_CONFIG) gtkmm-3.0 --cflags)
GTKMM_LIBS = $(shell $(PKG_CONFIG) gtkmm-3.0 --libs)

CXXFLAGS = -Wall -Wextra -std=c++17 -I $(INCLUDE) $(GTKMM_CFLAGS)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECTS) $(GTKMM_LIBS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS)

fclean: clean
	rm -f $(TARGET)

re: fclean all

