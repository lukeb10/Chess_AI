all: bin/play 

clean:
	rm -f bin/*.o
	rm -f bin/play
	rm -f bin/server
	rm -f bin/gui

bin/Functions.o: src/Functions.c src/Functions.h src/Display.h src/AI.h src/Definitions.h
	gcc -Wall -ansi -std=c99 -c src/Functions.c -o bin/Functions.o
bin/Display.o: src/Display.c src/Display.h src/Definitions.h
	gcc -Wall -ansi -std=c99 -c src/Display.c -o bin/Display.o
bin/AI.o: src/AI.c src/AI.h
	gcc -Wall -ansi -std=c99 -c src/AI.c -o bin/AI.o
bin/Main.o: src/Functions.h src/Display.h src/AI.h src/Definitions.h src/Main.c
	gcc -Wall -ansi -std=c99 -c src/Main.c -o bin/Main.o
bin/play: bin/Main.o bin/Functions.o bin/Display.o bin/AI.o
	gcc -Wall -ansi -std=c99 -lm bin/Functions.o bin/Display.o bin/AI.o bin/Main.o -o bin/play
test: bin/play
	bin/./play
gui: src/ClientApp.c src/ClientApp.h src/friends.glade src/chat.glade src/login.glade
	gcc -Wall -ansi -std=c99 -g -o bin/gui src/ClientApp.c `pkg-config --cflags gtk+-2.0` `pkg-config --libs gtk+-2.0`
server: src/server.c src/server.h
	gcc -Wall -ansi -std=c99 -g -o bin/server src/server.c
