#include "GridBuilder.h"

Grid SimpleGrid_1::generate_grid(uint8_t dimentions, uint16_t step, const std::vector<double>& ranges)
{
	Grid grid;
	double max_val = 1;
	double default_val = 0;
	double add = (double)1 / (step-1);
	Point new_point(dimentions, default_val);
	grid.push_back(new_point);
	bool stop = false;
	int pos = dimentions - 1;

	while (!stop)
	{
		pos = dimentions - 1;
		while (pos >= 0 && new_point[pos] == max_val) pos--;
		if (pos < 0) stop = true;
		if (!stop)
		{
			for (int i = pos + 1; i < dimentions; i++)
				new_point[i] = default_val;
			new_point[pos] += add;
			grid.push_back(new_point);
		}
	}

	for (auto& point : grid)
		for (size_t j = 0, k = 0; j < dimentions && k < ranges.size(); j++, k += 2)
			point[j] = (ranges[k + 1] + ranges[k]) * point[j] + ranges[k];

	return grid;
}

Grid SimpleGrid_2::generate_grid(uint8_t dimentions, uint16_t step, const std::vector<double>& ranges)
{
	Grid grid;
	double max_val = (step - 0.5) / step;
	double default_val = (double)1 / (2 * step);
	double add = (double)1 / step;
	Point new_point(dimentions, default_val);
	grid.push_back(new_point);
	bool stop = false;
	int pos = dimentions - 1;

	while (!stop)
	{
		pos = dimentions - 1;
		while (pos >= 0 && new_point[pos] == max_val) pos--;
		if (pos < 0) stop = true;
		if (!stop)
		{
			for (int i = pos + 1; i < dimentions; i++)
				new_point[i] = default_val;
			new_point[pos]+=add;
			grid.push_back(new_point);
		}
	}

	for (auto& point : grid)
		for (size_t j = 0, k = 0; j < dimentions && k < ranges.size(); j++, k += 2)
			point[j] = (ranges[k + 1] + ranges[k]) * point[j] + ranges[k];

	return grid;
}