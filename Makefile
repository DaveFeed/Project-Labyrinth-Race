output: Helpers.o UI.o Labyrinth.o Player.o Human.o RookieBot.o Fire.o EasyBot.o MediumBot.o HardBot.o Game.o Project\ Labyrinth\ Race.o
	g++ Helpers.o UI.o Labyrinth.o Player.o Human.o RookieBot.o Fire.o EasyBot.o MediumBot.o HardBot.o Game.o Project\ Labyrinth\ Race.o -o output

Helpers.o: Helpers.cpp Helpers.h
	g++ -c Helpers.cpp

UI.o: UI.cpp UI.h
	g++ -c UI.cpp

Labyrinth.o: Labyrinth.cpp Labyrinth.h
	g++ -c Labyrinth.cpp

Player.o: Player.cpp Player.h
	g++ -c Player.cpp

Human.o: Human.cpp Human.h
	g++ -c Human.cpp

Project\ Labyrinth\ Race.o: Project\ Labyrinth\ Race.cpp
	g++ -c Project\ Labyrinth\ Race.cpp

RookieBot.o: RookieBot.cpp RookieBot.h
	g++ -c RookieBot.cpp

EasyBot.o: EasyBot.cpp EasyBot.h
	g++ -c EasyBot.cpp

MediumBot.o: MediumBot.cpp MediumBot.h
	g++ -c MediumBot.cpp

HardBot.o: HardBot.cpp HardBot.h
	g++ -c HardBot.cpp

Game.o: Game.cpp Game.h
	g++ -c Game.cpp

Fire.o: Fire.cpp Fire.h
	g++ -c Fire.cpp

clean:
	rm output *.o

pretty:
	rm *.o