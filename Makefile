TARGET=LandGenerator
SOURCEFOLDER=Land\ Generator
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


all: .FORCE  		#Maybe this part should be refactored
	make clean		
	make move_src
	make $(TARGET)

move_src:
	mkdir -p $(TARGET)

	ln -s $(PWD)/$(SOURCEFOLDER)/*.cpp $(PWD)/$(SOURCEFOLDER)/*.hpp  $(TARGET)
	ln -s $(PWD)/$(SOURCEFOLDER)/*/*.cpp $(PWD)/$(SOURCEFOLDER)/*/*.hpp $(TARGET)


$(TARGET): $(OBJECTS) .FORCE
		mkdir -p $(BUILDFOLDER)
		$(CC) -o $(BUILDFOLDER)/$(TARGET) $(OBJECTS) $(LOADLIBES) $(LDLIBS) $(FRAMEWORKS) $(LDFLAGS)
		cp ./$(SOURCEFOLDER)/*.fragmentshader ./$(SOURCEFOLDER)/*.vertexshader ./$(BUILDFOLDER)

$(OBJECTS): $(SOURCES) .FORCE

clean:
		$(RM) $(OBJECTS) $(BUILDFOLDER)/$(TARGET)
		$(RM) -r $(TARGET)
		$(RM) -r $(BUILDFOLDER)

run:
	$(shell cd ./$(BUILDFOLDER); ./$(TARGET))

.PHONY: all move_src clean
.FORCE:
