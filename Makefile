CXXFLAGS=-Wall -Wextra -pedantic
SFML-LIB=-lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
SRCS=$(wildcard *.cpp)
OBJS=$(patsubst %.cpp,%.o,$(SRCS))

.PHONY: clean depend

P88l: $(OBJS)
	$(CXX) -o $@ $(OBJS) $(SFML-LIB)

clean:
	rm P88l *.o
depend:
	makedepend  $(SRCS) -Y
# DO NOT DELETE THIS LINE

Ball.o: Ball.hpp Specs.hpp
FPSCounter.o: FPSCounter.hpp
Game.o: Game.hpp Ball.hpp Trajectory.hpp Table.hpp FPSCounter.hpp Specs.hpp
main.o: Game.hpp Ball.hpp Trajectory.hpp Table.hpp FPSCounter.hpp
Table.o: Table.hpp Specs.hpp
Trajectory.o: Trajectory.hpp Specs.hpp
