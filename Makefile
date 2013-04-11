TARGET=land_generator
BUILDFOLDER=Build
SOURCES=$(wildcard $(TARGET)/*.cpp)
OBJECTS=$(SOURCES:%.cpp=%.o)
UNAME=$(shell uname)
CC=g++

ifeq ($(UNAME),Linux)
CFLAGS+=
LDFLAGS+= -lGL -lGLEW -lglfw
FRAMEWORKS=
else
CFLAGS+=
LDFLAGS+= -lGLEW -lglfw
FRAMEWORKS= -framework OpenGL
endif


all: $(TARGET)

$(OBJECTS): $(SOURCES)

$(TARGET): $(OBJECTS)
		mkdir -p $(BUILDFOLDER)
		$(CC) -o $(BUILDFOLDER)/$(TARGET) $(OBJECTS) $(LOADLIBES) $(LDLIBS) $(FRAMEWORKS) $(LDFLAGS)

clean:
		$(RM) $(OBJECTS) $(BUILDFOLDER)/$(TARGET)
		$(RM) -r $(BUILDFOLDER)
.PHONY: all clean
