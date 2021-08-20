SRC = ..\H\*.cpp ..\CPP\*.cpp 
INCLUDES = ..\H\*.h ..\CPP\*.h 
LIBS = ..\*.lib 
INCLUDEPATH = C:\bc31\include;..\H;..\CPP;
LIBSPATH = C:\bc31\lib;..\;
TARGET = komp.exe
$(TARGET):	$(SRC) $(INCLUDES) configuration.xmi
	bcc.exe -mh -v -e$(TARGET) -I$(INCLUDEPATH) -L$(LIBSPATH) $(SRC) $(LIBS)
all:	$(TARGET)
clean:
	-del *.obj
	-del $(TARGET)
	-del *.asm
configuration.xmi:	
	configuration.xmi