#include "GridBuilder.h"
#include <random>

Grid GridBuilder::simple_grid_1(uint8_t dimension, uint16_t step, const std::vector<double>& ranges)
{
	Grid grid;
	Point new_point(dimension, 0);
	std::vector<double> steps(dimension);

	for (int i = 0, j = 0; i < dimension && j < ranges.size(); i++, j += 2)
	{
		new_point[i] = ranges[j];
		steps[i] = (ranges[j + 1] - ranges[j]) / (step - 1);
	}

	grid.push_back(new_point);
	bool stop = false;
	int pos = dimension - 1;

	while (!stop)
	{
		pos = dimension - 1;
		while (pos >= 0 && new_point[pos] >= ranges[2 * pos + 1]) pos--;
		if (pos < 0) stop = true;
		if (!stop)
		{
			for (int i = pos + 1; i < dimension; i++)
				new_point[i] = ranges[2 * i];
			new_point[pos] += steps[pos];
			grid.push_back(new_point);
		}
	}

	return grid;
}

Grid GridBuilder::simple_grid_2(uint8_t dimension, uint16_t step, const std::vector<double>& ranges)
{
	Grid grid;
	double max_val = (step - 0.5) / step;
	double default_val = (double)1 / (2 * step);
	double add = (double)1 / step;
	Point new_point(dimension, default_val);
	grid.push_back(new_point);
	bool stop = false;
	int pos = dimension - 1;

	while (!stop)
	{
		pos = dimension - 1;
		while (pos >= 0 && new_point[pos] >= max_val) pos--;
		if (pos < 0) stop = true;
		if (!stop)
		{
			for (int i = pos + 1; i < dimension; i++)
				new_point[i] = default_val;
			new_point[pos]+=add;
			grid.push_back(new_point);
		}
	}

	for (auto& point : grid)
		for (size_t j = 0, k = 0; j < dimension && k < ranges.size(); j++, k += 2)
			point[j] = (ranges[k + 1] - ranges[k]) * point[j] + ranges[k];

	return grid;
}

Grid GridBuilder::uniform_distribution_grid(uint8_t dimension, uint16_t step, const std::vector<double>& ranges, double alpha) 
{
	// Создание генератора псевдослучайных чисел
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<double> dis(-alpha, alpha);  // Распределение для случайного смещения

	Grid grid;
	double max_val = (step - 0.5) / step;
	double default_val = (double)1 / (2 * step);
	double add = (double)1 / step;
	Point new_point(dimension, default_val);
	grid.push_back(new_point);
	bool stop = false;
	int pos = dimension - 1;

	std::vector<double> steps(dimension);
	for (int i = 0, j = 0; i < dimension && j < ranges.size(); i++, j += 2)
	{
		new_point[i] = ranges[j];
		steps[i] = (ranges[j + 1] - ranges[j]) / (step - 1);
	}

	while (!stop)
	{
		pos = dimension - 1;
		while (pos >= 0 && new_point[pos] >= max_val) pos--;
		if (pos < 0) stop = true;
		if (!stop)
		{
			for (int i = pos + 1; i < dimension; i++)
				new_point[i] = default_val;
			new_point[pos] += add;
			grid.push_back(new_point);
		}
	}

	for (auto& point : grid)
		for (size_t j = 0, k = 0; j < dimension && k < ranges.size(); j++, k += 2)
			point[j] = (ranges[k + 1] - ranges[k]) * point[j] + ranges[k] + dis(gen);

	return grid;
}