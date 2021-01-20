	CC = g++ -g
	DEBUG = -ggdb
	OPTIONS = -Wall

	SRC_grid = src/Grid.h

	grid_CPP = src/Grid.cpp
	M_CPP = src/main.cpp

	OBJETS = obj/Grid.o obj/main.o


all : bin/main

bin/main :  $(OBJETS)
	$(CC) $(DEBUG) $(OPTIONS) $^ -o $@

obj/main.o : $(M_CPP) $(SRC_CLE) $(SRC_element_A) $(SRC_element) $(SRC_TAB) $(SRC_grid)
	$(CC) $(DEBUG) $(OPTIONS) -o $@ -c $<

obj/Grid.o : $(grid_CPP) $(SRC_grid) $(SRC_element)
	$(CC) $(DEBUG) $(OPTIONS) -o $@ -c $<


clean :
	rm obj/*
	rm bin/*
