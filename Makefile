# setup
TARGET = main.exe
SOURCE_FOLDER = source
INCLUDE_FOLDER = include

SOURCES = $(SOURCE_FOLDER)/*.cpp
CXX = g++
DEBUG_FLAGS = -O0 -g
CXXFLAGS = -Wall -Wextra

# raylib things
LIBS = -lraylib -lgdi32 -lwinmm

# main command
$(TARGET): $(SOURCES)
	$(CXX) $(DEBUG_FLAGS) $(CXXFLAGS) -o $(TARGET) -I$(INCLUDE_FOLDER) $(SOURCES) $(LIBS)

# clean up command
clean:
	rm -f $(TARGET)
