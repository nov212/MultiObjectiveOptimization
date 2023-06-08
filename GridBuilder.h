#pragma once
#include <vector>
#include <list>
#include <stdint.h>

using Point = std::vector<double>;
using Grid = std::list<Point>;

class GridBuilder
{
public:
	// step - шаг сетки
	// dimention - размерность сетки
	virtual Grid generate_grid(uint8_t dimentions, uint16_t step, const std::vector<double>& ranges) = 0;
};

class SimpleGrid_1 : public GridBuilder
{
public:
	virtual Grid generate_grid(uint8_t dimentions, uint16_t step, const std::vector<double>& ranges) override final;
};

class SimpleGrid_2 : public GridBuilder
{
public:
	virtual Grid generate_grid(uint8_t dimentions, uint16_t step, const std::vector<double>& ranges) override final;
};