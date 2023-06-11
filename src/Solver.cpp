#include "Solver.h"

std::list<Point> Solver::grid_method(const Grid& grid, std::vector<double>(*func)(const Point&))
{
	if (grid.size() == 0)
		return {};

	if (grid.size() == 1)
		return { grid.front() };

	Grid point_set(grid.begin(), grid.end());
	Grid::iterator current_point = point_set.begin();
	Grid::iterator grid_iter;
	Grid::iterator tmp;
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
				tmp = current_point;
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
