LIBS_LINUX = -lSDL2main -lSDL2 -lSDL2_image -lGLU -lGL -lGLEW -lm
LIBS_WIN = -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lopengl32 -lUser32 -lShell32 -lglew32 -lm

SRC = *.c entity/*.c
OBJ = *.o
OUT = game

linux:
	gcc -c -I../gln/includes $(SRC)
	gcc -o $(OUT) $(OBJ) -L../gln/bin -lgln $(LIBS_LINUX)
	rm *.o
	./$(OUT)

win:
	gcc -I../opengl/include -I../gln/includes -c $(SRC) 
	gcc -o $(OUT).exe $(OBJ) -L../opengl/lib -L../gln/bin -lgln $(LIBS_WIN)
	erase *.o
	$(OUT).exe

