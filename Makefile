OBJ = display.o
OB1 = test_local/actions.o test_local/main.o
OB2 = test_map/actions.o test_map/main.o

CXXF = -std=c++11 -I.
LDF  = -lsfml-graphics -lsfml-window -lsfml-system

.PHONY: all
all: test.local test.map Makefile

.PHONY: clean
clean:
	rm $(OBJ) $(OB1)

test.local: $(OBJ) $(OB1)
	$(CXX) $(LDF) $(LDFLAGS) $(OBJ) $(OB1) -o test.local

test.map: $(OBJ) $(OB2)
	$(CXX) $(LDF) $(LDFLAGS) $(OBJ) $(OB2) -o test.map

%.o: %.cpp Makefile
	$(CXX) $(CXXF) $(CXXFLAGS) $(CPPFLAGS) -c $< -o $@

particle_filter.o: particle_filter.hpp
display.o: display.hpp

test_local/actions.o: test_local/actions.hpp test_local/robot.hpp
test_local/main.o: display.hpp particle_filter.hpp particle_filter.tpp test_local/actions.hpp test_local/robot.hpp

test_map/actions.o: test_map/actions.hpp test_map/robot.hpp
test_map/main.o: display.hpp particle_filter.hpp particle_filter.tpp test_map/actions.hpp test_map/robot.hpp
