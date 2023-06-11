#include "Solver.h"

std::list<Point> Solver::grid_method(GridBuilder& grid_builder, std::vector<double>(*func)(const Point&),
										uint32_t iterations, uint16_t step, const std::vector<double>& ranges)
{
	Grid point_set;
	auto divisions = step;
	Grid::iterator grid_iter;
	int8_t compare_res;

	for (int iter = 0; iter < iterations; iter++)
	{
		point_set = grid_builder.generate_grid(ranges.size() / 2, divisions, ranges);
		auto current_point = point_set.begin();
		while (current_point != point_set.end())
		{
			grid_iter = ++point_set.begin();
			while (grid_iter != point_set.end())
			{
				compare_res = compare(*current_point, *grid_iter, func);
				if (compare_res == WORSE)
				{
					point_set.erase(current_point);
					current_point = grid_iter;
				}
				else
					if (compare_res == BETTER)
					{
						grid_iter = point_set.erase(grid_iter);
						continue;
					}
				grid_iter++;
			}
			current_point++;
		}

		divisions = 2 * divisions - 1;
	}

	return point_set;
}

int8_t Solver::compare(const Point& p1, const Point& p2, std::vector<double>(*func)(const Point&))
{
	auto res_1 = func(p1);
	auto res_2 = func(p2);
	double diff = 0;
	int8_t state = DEFAULT;

	for (int i = 0; i < res_1.size(); i++)
	{
		diff = res_2[i] - res_1[i];
		if ((diff > 0 && state == WORSE) || (diff < 0 && state == BETTER)) return NON_COMPARABLE;
		if (diff > 0 && state == DEFAULT) state = BETTER;
		else
			if (diff < 0 && state == DEFAULT) state = WORSE;
	}

	if (state == DEFAULT) state = NON_COMPARABLE;

	return state;
}

Grid Solver::parallel_grid_method(const Grid& grid, Grid::iterator begin, Grid::iterator end, std::vector<double>(*func)(const Point&))
{
	if (grid.size() == 0)
		return {};

	if (grid.size() == 1)
		return { grid.front()};

	Grid point_set(begin, end);
	Grid::iterator current_point = point_set.begin();
	Grid::iterator grid_iter;
	int8_t compare_res = DEFAULT;

	while (current_point != point_set.end())
	{
		grid_iter = current_point;
		grid_iter++;
		while (grid_iter != point_set.end())
		{
			compare_res = compare(*current_point, *grid_iter, func);
			if (compare_res == WORSE)
			{
				Grid::iterator tmp = current_point;
				tmp++;
				point_set.erase(current_point);
				current_point = tmp;
				grid_iter = current_point;
			}
			else
				if (compare_res == BETTER)
				{
					grid_iter = point_set.erase(grid_iter);
					continue;
				}
			grid_iter++;
		}

		current_point++;
	}

	return point_set;
}
