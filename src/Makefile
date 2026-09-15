CC = C:/mingw64/bin/gcc.exe

CFLAGS = -fdiagnostics-color=always -g -std=c23 \
         -I"C:/Program Files/SDL3-3.4.14/SDL3/include" \
         -I"C:/Program Files/SDL3-3.4.14/SDL3_Image/include" \
         -I"C:/Program Files/SDL3-3.4.14/SDL3_ttf/include"

LDFLAGS = -L"C:/Program Files/SDL3-3.4.14/SDL3/lib" \
          -L"C:/Program Files/SDL3-3.4.14/SDL3_Image/lib" \
          -L"C:/Program Files/SDL3-3.4.14/SDL3_ttf/lib"

LIBS = -lSDL3 -lSDL3_image -lSDL3_ttf

TARGET = programa.exe
SOURCE = main.c

all:
	$(CC) $(CFLAGS) $(SOURCE) -o $(TARGET) $(LDFLAGS) $(LIBS)

clean:
	del /Q $(TARGET) 2>NUL
