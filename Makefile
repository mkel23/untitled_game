INCLUDE=-I/usr/local/Cellar/sdl2/2.0.12_1/include -I/usr/local/Cellar/sdl2_image/2.0.5/include -I/usr/local/Cellar/sdl2_ttf/2.0.15/include -I/usr/local/Cellar/cereal/1.3.0/include
LIB=-L/usr/local/Cellar/sdl2/2.0.12_1/lib -L/usr/local/Cellar/sdl2_image/2.0.5/lib -L/usr/local/Cellar/sdl2_ttf/2.0.15/lib
CC=g++
CPPFLAGS=-c -std=c++11
OBJS=main.o texture.o player.o collision_manager.o tile.o game.o input_handler.o play_state.o game_state_manager.o main_menu_state.o menu_button.o pause_menu_state.o save_state_manager.o
PROG=play

game: clean $(OBJS)
	$(CC) -g -o $(PROG) $(OBJS) $(INCLUDE) $(LIB) -lSDL2-2.0.0 -lSDL2_image -lSDL2_ttf

main.o:
	$(CC) $(CPPFLAGS) main.cpp

texture.o:
	$(CC) $(CPPFLAGS) src/texture.cpp

player.o:
	$(CC) $(CPPFLAGS) src/player.cpp

collision_manager.o:
	$(CC) $(CPPFLAGS) src/collision_manager.cpp

tile.o:
	$(CC) $(CPPFLAGS) src/tile.cpp

game.o:
	$(CC) $(CPPFLAGS) src/game.cpp

input_handler.o:
	$(CC) $(CPPFLAGS) src/input_handler.cpp

play_state.o:
	$(CC) $(CPPFLAGS) src/play_state.cpp

game_state_manager.o:
	$(CC) $(CPPFLAGS) src/game_state_manager.cpp

main_menu_state.o:
	$(CC) $(CPPFLAGS) src/main_menu_state.cpp

menu_button.o:
	$(CC) $(CPPFLAGS) src/menu_button.cpp

pause_menu_state.o:
	$(CC) $(CPPFLAGS) src/pause_menu_state.cpp

save_state_manager.o:
	$(CC) $(CPPFLAGS) src/save_state_manager.cpp

clean:
	rm -f *.o play
