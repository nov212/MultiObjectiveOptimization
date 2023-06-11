#pragma once
#include "GridBuilder.h"

class Solver
{
public:
	std::list<Point> grid_method(GridBuilder& grid_builder, std::vector<double>(*func)(const Point&), 
									uint32_t iterations, uint16_t step, const std::vector<double>& ranges);
	Grid parallel_grid_method(const Grid& grid, Grid::iterator begin, Grid::iterator end, std::vector<double>(*func)(const Point&));
	Grid normal_distribution();
private:
	enum cmp_state_t
	{
		DEFAULT = -2,
		WORSE = -1,
		NON_COMPARABLE = 0,
		BETTER = 1
	};

	/// <summary>
	/// Определяет какая из двух точек безусловно лучше или являются ли они несравнимыми.
	/// Функция сравнивает значения критериев в точках и возвращает результат сравнения в виде целого числа со знаком.
	/// </summary>
	/// <param name="p1">Первая сравниваемая точка</param>
	/// <param name="p2">Вторая сравниваемая точка</param>
	/// <param name="func">Критерий задачи</param>
	/// <returns>
	/// 0 - точки несравнимы;
	/// 1 - p1 безусловно лучше p2;
	/// -1 - p2 безусловно лучше p1;
	/// </returns>
	int8_t compare(const Point& p1, const Point& p2, std::vector<double> (*func)(const Point&));
};