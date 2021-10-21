# NOTE: LIBS and ./shared was added to path variables
# TODO: make a release version
LIBS     = C:\Users\kobim\Desktop\cppDependencies\libs\debug
OPENGL   = C:\MinGW\lib

LIBS_INCLUDE  = C:\Users\kobim\Desktop\cppDependencies\include
HEADERS_INCLUDE  = .
# NOTE: not in LIBS_INCLUDE since it is still under development
GLMATH_INCLUDE   = C:\Users\kobim\Desktop\kobi\projects\graphicsMath\headers

INCLUDES = -I$(LIBS_INCLUDE) -I$(HEADERS_INCLUDE) -I$(GLMATH_INCLUDE)
EXT_LIBS = -L$(OPENGL) -L$(LIBS) -lglMath -llibfreetype -lglfw3 -lglew32 -llibgdi32 -llibopengl32
MY_LIBS  = -L./shared -lgeometry -lGUIElements
ALL_LIBS = $(EXT_LIBS) $(MY_LIBS)

CPP_FILES = $(wildcard src/*.cpp)
OBJECTS   = $(patsubst src/%.cpp, object/%.o, $(CPP_FILES))
DEP_FILES = $(patsubst object/%.o, depFiles/%.d, $(OBJECTS))

# TODO: make a seperate file for dlls
GEOMETRY       = circle color line point rectangle shader events nonInclusiveRange
GEOMETRY_O     = $(patsubst %,object/%.o,$(GEOMETRY))

GUI_ELEMENTS   = button checkbox container graph input text element utility
GUI_ELEMENTS_O = $(patsubst %,object/%.o,$(GUI_ELEMENTS))

vpath %.dll shared
vpath %.d depFiles

main.exe: allObj
	@echo building $@...
	@g++ -g $(OBJECTS) $(INCLUDES) $(EXT_LIBS) -o main.exe

$(OBJECTS): object/%.o : src/%.cpp
	@echo building $@...
	@g++ -g -c -fPIC $< $(INCLUDES) -o $@ -MMD -MP -MF depFiles/$*.d

allObj: $(OBJECTS)

allLibs: geometry.dll GUIElements.dll

geometry.dll:  $(GEOMETRY_O)
	@echo building $@...
	@g++ -g -shared -fPIC $(GEOMETRY_O) $(EXT_LIBS) -o shared/geometry.dll
GUIElements.dll:  $(GUI_ELEMENTS_O)
	@echo building $@...
	@g++ -g -shared -fPIC $(GUI_ELEMENTS_O) $(EXT_LIBS) -L./shared -lgeometry -o shared/GUIElements.dll

.PHONY: cleanObj cleanLibs cleanAll
cleanObj:
	-rm object/*.o & rm depFiles/*.d
cleanLibs:
	-rm shared/*.dll;
cleanAll: cleanObj cleanLibs
	-rm main.exe;

-include $(DEP_FILES)