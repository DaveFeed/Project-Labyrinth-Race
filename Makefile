output: Labyrinth.o Player.o Human.o RookieBot.o Fire.o Game.o UI.o Project\ Labyrinth\ Race.o
	g++ Labyrinth.o Player.o Human.o RookieBot.o Fire.o Game.o UI.o Project\ Labyrinth\ Race.o -o output

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

Game.o: Game.cpp Game.h
	g++ -c Game.cpp

UI.o: UI.cpp UI.h
	g++ -c UI.cpp

Fire.o: Fire.cpp Fire.h
	g++ -c fire.cpp

clean:
	rm output *.o

pretty:
	rm *.o