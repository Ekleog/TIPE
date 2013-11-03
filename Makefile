OBJ = display.o
OB1 = test1/actions.o test1/main.o

CXXF = -std=c++11 -I.
LDF  = -lsfml-graphics -lsfml-window -lsfml-system

.PHONY: all
all: test.1 Makefile

.PHONY: clean
clean:
	rm $(OBJ) $(OB1)

test.1: $(OBJ) $(OB1)
	$(CXX) $(LDF) $(LDFLAGS) $(OBJ) $(OB1) -o test.1

%.o: %.cpp Makefile
	$(CXX) $(CXXF) $(CXXFLAGS) $(CPPFLAGS) -c $< -o $@

particle_filter.o: particle_filter.hpp
test1/actions.o: test1/actions.hpp test1/robot.hpp
display.o: display.hpp
test1/main.o: display.hpp particle_filter.hpp particle_filter.tpp test1/actions.hpp test1/robot.hpp
