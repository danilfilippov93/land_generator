COMPILER=G++

# todo: object files into output path, processing c / c++ files in the same time (?), nested directories for source files (?)
C = cpp
OUTPUT_PATH = Build/
SOURCE_PATH = src/
EXE = $(OUTPUT_PATH)land_generator
UNAME := $(shell uname)

ifeq ($(UNAME),Linux)
OBJ = o
COPT = -O2
CCMD = g++
OBJFLAG = -o
EXEFLAG = -o
INCLUDES =
LIBS = -lGLEW -lglfw -lGL
FRAMEWORKS =
LIBPATH =
CPPFLAGS = $(COPT) -g $(INCLUDES)
LDFLAGS = $(LIBPATH) -g $(LIBS)
DEP = dep
else
OBJ = o
COPT = -O2
CCMD = g++
OBJFLAG = -o
EXEFLAG = -o
INCLUDES =
LIBS = -lGLEW -lglfw
FRAMEWORKS = -framework OpenGL
LIBPATH =
CPPFLAGS = $(COPT) -g $(INCLUDES)
LDFLAGS = $(LIBPATH) -g $(LIBS)
DEP = dep
endif

OBJS := $(patsubst %.$(C),%.$(OBJ),$(wildcard $(SOURCE_PATH)*.$(C)))

%.$(OBJ):%.$(C)
	@echo Compiling $(basename $<)...
	$(CCMD) -c $(CPPFLAGS) $(CXXFLAGS) $< $(OBJFLAG)$@

all: $(OBJS)
	@echo Linking...
	@echo $(OS)
	$(CCMD) $(LDFLAGS) $^ $(LIBS) $(FRAMEWORKS) $(EXEFLAG) $(EXE)

clean:
	rm -rf $(SOURCE_PATH)*.$(OBJ) $(EXE)

rebuild: clean all
#rebuild is not entirely correct