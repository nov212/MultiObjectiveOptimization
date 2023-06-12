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
	static Grid simple_grid_1(uint8_t dimenion, uint16_t n_points, const std::vector<double>& ranges);
	static Grid simple_grid_2(uint8_t dimenion, uint16_t n_points, const std::vector<double>& ranges);
	static Grid uniform_distribution_grid_1(uint8_t dimenion, uint16_t n_points, const std::vector<double>& ranges, double alpha);
	static Grid uniform_distribution_grid_2(uint8_t dimenion, uint16_t n_points, const std::vector<double>& ranges);
};
