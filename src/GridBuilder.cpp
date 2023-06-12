#include "GridBuilder.h"
#include <random>
#include<cmath>

Grid GridBuilder::simple_grid_1(uint8_t dimension, uint16_t n_points, const std::vector<double>& ranges)
{
	Grid grid;
	Point new_point(dimension, 0);
	int step = std::pow(n_points, (double)1 / dimension);
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

Grid GridBuilder::simple_grid_2(uint8_t dimension, uint16_t n_points, const std::vector<double>& ranges)
{
	Grid grid;
	int step = std::pow(n_points, (double)1 / dimension);
	double precision = 0.001;
	double max_val = std::round((step - 0.5) / (precision * step)) * precision;
	double default_val = std::round((double)1 / (2 * step * precision)) * precision;
	double add = std::round((double)1 / (step * precision)) * precision;
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
			new_point[pos] += add;
			new_point[pos] = std::round(new_point[pos] / precision) * precision;
			grid.push_back(new_point);
		}
	}

	for (auto& point : grid)
		for (size_t j = 0, k = 0; j < dimension && k < ranges.size(); j++, k += 2)
			point[j] = (ranges[k + 1] - ranges[k]) * point[j] + ranges[k];

	return grid;
}

Grid GridBuilder::uniform_distribution_grid_1(uint8_t dimension, uint16_t n_points, const std::vector<double>& ranges, double alpha)
{
	// Создание генератора псевдослучайных чисел
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<double> dis(-alpha, alpha);  // Распределение для случайного смещения

	Grid grid;
	int step = std::pow(n_points, (double)1 / dimension);
	double precision = 0.001;
	double max_val = std::round((step - 0.5) / (precision *step)) * precision;
	double default_val = std::round((double)1 / (2 * step* precision)) * precision;
	double add = std::round((double)1 / (step * precision))* precision;
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
			new_point[pos] += add;
			new_point[pos] = std::round(new_point[pos] / precision) * precision;
			grid.push_back(new_point);
		}
	}

	for (auto& point : grid)
		for (size_t j = 0, k = 0; j < dimension && k < ranges.size(); j++, k += 2)
			point[j] = (ranges[k + 1] - ranges[k]) * point[j] + ranges[k]+dis(gen);

	return grid;
}

Grid GridBuilder::uniform_distribution_grid_2(uint8_t dimension, uint16_t n_points, const std::vector<double>& ranges)
{
	std::list<double>::iterator min_val_iter;
	int min;
	std::vector<std::vector<double>> coordinates(dimension);
	std::vector<double> new_coordinates;
	std::vector<double> range_length;

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<double> dis(-1.0, 1.0);
	std::vector<double> random_coordinates(n_points);

	for (int i = 0; i < ranges.size(); i += 2)
		range_length.push_back(ranges[i + 1] - ranges[i]);

	// повторяем процедуру для каждой координаты
	for (int dim = 0; dim < dimension; dim++)
	{
		// располагаем точки на одинаковом расстоянии друг от друга
		// создаём ряд случайно сгенерированных точек на отрезке
		double step = range_length[dim] / (n_points - 1);
		std::list<double> one_coordinate_distribution;
		for (int i = 0; i < n_points; i++)
		{
			one_coordinate_distribution.push_back(ranges[2*dim] + step * i);
			random_coordinates[i] = dis(gen);
		}

		for (int i = 0; i < n_points; i++)
		{
			min_val_iter = one_coordinate_distribution.begin();
			min = abs(*min_val_iter - random_coordinates[i]);

			for (auto it = ++one_coordinate_distribution.begin(); it != one_coordinate_distribution.end(); ++it)
				if (abs(*it - random_coordinates[i]) < min)
				{
					min_val_iter = it;
					min = abs(*min_val_iter - random_coordinates[i]);
				}

			new_coordinates.push_back(*min_val_iter);
			one_coordinate_distribution.erase(min_val_iter);
		}
		coordinates[dim] = new_coordinates;
		new_coordinates.clear();
	}

	std::list<std::vector<double>> grid;
	for (int i = 0; i < n_points; i++)
	{
		std::vector<double> point;
		for (int j = 0; j < dimension; j++)
			point.push_back(coordinates[j][i]);
		grid.push_back(point);
	}

	return grid;
}