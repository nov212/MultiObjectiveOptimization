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
			current_point = point_set.begin();
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
		diff = res_2[i] - res_1[1];
		if ((diff > 0 && state == WORSE) || (diff < 0 && state == BETTER)) return NON_COMPARABLE;
		if (diff > 0 && state == DEFAULT) state = BETTER;
		if (diff < 0 && state == DEFAULT) state = WORSE;
	}

	if (state == DEFAULT) state = NON_COMPARABLE;

	return state;
}