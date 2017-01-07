CXX = g++
CXXFLAGS = -std=c++14 -MMD
EXEC = cc3k
OBJECTS = character.o object.o player.o enemy.o door.o hwall.o vwall.o potion.o treasure.o space.o stair.o tile.o passage.o chamber.o floor.o textdisplay.o cc3k.o
DEPENDENS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

-include ${DEPENDENS}

./PHONY: clean

clean:
	rm ${EXEC} ${OBJECTS} ${DEPENDENS}
