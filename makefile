CXX      = g++
INCLUDES = -Isrc/core -Isrc/sfml -Isrc/io -Isrc/app
CXXFLAGS = -std=c++17 -g -Wall $(INCLUDES)
LIBS     = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

SRCS = src/main.cpp \
       src/core/game_logic.cpp \
       src/core/timer.cpp \
       src/core/util.cpp \
       src/io/position_io.cpp \
       src/sfml/input_handlers.cpp \
       src/sfml/input_mapping.cpp \
       src/sfml/ui_render.cpp \
       src/sfml/scene_setup.cpp \
       src/sfml/runtime_ui.cpp \
       src/sfml/render_frame.cpp \
       src/sfml/game_loop.cpp

all: circaminx.out

circaminx.out: $(SRCS)
	$(CXX) $(CXXFLAGS) -o $@ $(SRCS) $(LIBS)
