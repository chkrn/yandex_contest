all: z_bonus_calc.cpp
	g++ --std=c++11 z_bonus_calc.cpp -o calc

clean:
	rm calc
