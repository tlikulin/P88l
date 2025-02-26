CXXFLAGS=-Wall -Wextra -pedantic -std=c++20
SFML-LIB=-lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
SRCS=$(wildcard src/*.cpp)
OBJS=$(patsubst src/%.cpp,src/%.o,$(SRCS))

.PHONY: clean depend

P88l: $(OBJS)
	$(CXX) -o bin/$@ $(OBJS) $(SFML-LIB)

clean:
	rm bin/P88l src/*.o
depend:
	makedepend  $(SRCS) -Y
# DO NOT DELETE THIS LINE

src/Ball.o: src/Ball.hpp src/Spec.hpp
src/FPSCounter.o: src/FPSCounter.hpp
src/Game.o: src/Game.hpp src/Ball.hpp src/Trajectory.hpp src/Table.hpp
src/Game.o: src/Pockets.hpp src/Spec.hpp src/FPSCounter.hpp src/UI.hpp
src/Game.o: src/Menu.hpp
src/main.o: src/Game.hpp src/Ball.hpp src/Trajectory.hpp src/Table.hpp
src/main.o: src/Pockets.hpp src/Spec.hpp src/FPSCounter.hpp src/UI.hpp
src/main.o: src/Menu.hpp
src/Menu.o: src/Menu.hpp
src/Pockets.o: src/Pockets.hpp src/Spec.hpp src/Ball.hpp
src/Table.o: src/Table.hpp src/Spec.hpp
src/Trajectory.o: src/Trajectory.hpp src/Spec.hpp
src/UI.o: src/UI.hpp src/Ball.hpp src/Spec.hpp
