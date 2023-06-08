#include <iostream>
#include "Functions.h"
#include "Solver.h"

int main()
{
	Solver s;
	SimpleGrid_1 sg_1;
	s.grid_method(sg_1, func_3, 1, 5, { 0, 16 });
}   
