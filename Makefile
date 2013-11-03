OBJ = particle_filter.o testactions.o display.o
TST = test

CXXF = -std=c++11
LDF  = -lsfml-graphics -lsfml-window -lsfml-system

.PHONY: all
all: $(TST) Makefile

.PHONY: clean
clean:
	rm $(OBJ)

$(TST): $(OBJ) $(TST).o
	$(CXX) $(LDF) $(LDFLAGS) $(OBJ) $(TST).o -o $(TST)

%.o: %.cpp Makefile
	$(CXX) $(CXXF) $(CXXFLAGS) $(CPPFLAGS) -c $< -o $@

particle_filter.o: particle_filter.hpp
testactions.o: testactions.hpp testrobot.hpp
display.o: display.hpp
test.o: particle_filter.hpp testactions.hpp testrobot.hpp display.hpp particle_filter.tpp
