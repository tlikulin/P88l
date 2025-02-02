CXXFLAGS=-Wall -Wextra -pedantic
SFML-LIB=-lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
SRCS=$(wildcard src/*.cpp)
OBJS=$(patsubst src/%.cpp,src/%.o,$(SRCS))

.PHONY: clean depend

P88l: $(OBJS)
	$(CXX) -o $@ $(OBJS) $(SFML-LIB)

clean:
	rm P88l src/*.o
depend:
	makedepend  $(SRCS) -Y
# DO NOT DELETE THIS LINE

src/Ball.o: src/Ball.hpp src/Specs.hpp
src/FPSCounter.o: src/FPSCounter.hpp
src/Game.o: src/Game.hpp src/Ball.hpp src/Trajectory.hpp src/Table.hpp
src/Game.o: src/FPSCounter.hpp src/Specs.hpp
src/main.o: src/Game.hpp src/Ball.hpp src/Trajectory.hpp src/Table.hpp
src/main.o: src/FPSCounter.hpp
src/Table.o: src/Table.hpp src/Specs.hpp
src/Trajectory.o: src/Trajectory.hpp src/Specs.hpp
