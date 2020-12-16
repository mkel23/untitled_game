INCLUDE=-I/usr/local/Cellar/sdl2/2.0.12_1/include -I/usr/local/Cellar/sdl2_image/2.0.5/include -I/usr/local/Cellar/sdl2_ttf/2.0.15/include
LIB=-L/usr/local/Cellar/sdl2/2.0.12_1/lib -L/usr/local/Cellar/sdl2_image/2.0.5/lib -L/usr/local/Cellar/sdl2_ttf/2.0.15/lib
CC=g++
OBJS=main.o ltexture.o player.o
PROG=play

game: $(OBJS)
	$(CC) -g -o $(PROG) $(OBJS) $(INCLUDE) $(LIB) -lSDL2-2.0.0 -lSDL2_image -lSDL2_ttf

main.o:
	$(CC) -c main.cpp

ltexture.o:
	$(CC) -c ltexture.cpp

player.o:
	$(CC) -c player.cpp

clean:
	rm -f *.o
