#include "GridBuilder.h"
#include <random>

Grid SimpleGrid_1::generate_grid(uint8_t dimension, uint16_t step, const std::vector<double>& ranges)
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
		while (pos >= 0 && new_point[pos] == ranges[2 * pos + 1]) pos--;
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

Grid SimpleGrid_2::generate_grid(uint8_t dimension, uint16_t step, const std::vector<double>& ranges)
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
		while (pos >= 0 && new_point[pos] == max_val) pos--;
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

Grid UniformDistributionGrid::generate_grid(uint8_t dimension, uint16_t step, const std::vector<double>& ranges)
{
	/*
	 генерация случайного смещения для каждой точки, используя std::uniform_real_distribution<double> dis(-0.4, 0.4).
	 Это распределение генерирует случайные значения в диапазоне [-0.4, 0.4], которые затем добавляются к координатам точек.
	 Это позволяет создать некоторое разнообразие и разделить точки, чтобы они не слишком сильно накладывались при проекции на одну из осей.
	 */
	int numPointsX = 5;  // Количество точек по оси X
	int numPointsY = 4;  // Количество точек по оси Y

	Grid grid;  // Вектор для хранения точек сетки

	// Создание генератора псевдослучайных чисел
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<double> dis(-0.4, 0.4);  // Распределение для случайного смещения

	// Генерация и добавление точек в сетку
	for (int i = 0; i < numPointsX; ++i) {
		for (int j = 0; j < numPointsY; ++j) {
			double x = static_cast<double>(i) + dis(gen);
			double y = static_cast<double>(j) + dis(gen);
			grid.emplace_back(x, y);
		}
	}
}

//Grid generateGridPoints(int dimension, double step, std::vector<double> ranges) {
//    std::list<std::vector<double>> gridPoints;  // Список для хранения точек сетки
//
//    // Создание генератора псевдослучайных чисел
//    std::random_device rd;
//    std::mt19937 gen(rd());
//    std::uniform_real_distribution<double> dis(0, 0.4);  // Распределение для случайного смещения
//	std::vector<double> grid_step(dimension);
//
//	for (int i = 0, j = 0; i < dimension && j < ranges.size(); i++, j+=2)
//		grid_step[i] = (ranges[j+1] - ranges[j])/step;
//
//    std::vector<uint16_t> divisions(dimension, 1);  // Количество делений по каждой оси
//
//    // Генерация и добавление точек в сетку
//    std::vector<double> point(dimension, 0.0);
//    for (double i = 0.0; i < 1.0; i += step) {
//        for (int j = 0; j < dimension; ++j) {
//            point[j] = i + dis(gen);
//        }
//
//        gridPoints.push_back(point);
//
//        // Генерация остальных точек сетки
//         for (int k = 0; k < dimension; ++k) {
//             if (i + step <= 1.0) {
//                 point[k] = i + step + dis(gen);
//                 gridPoints.push_back(point);
//             }
//         }
//    }
//
//    return gridPoints;
//}


Grid generateGridPoints(int dimension, double step, std::vector<double> ranges) {
	// Создание генератора псевдослучайных чисел
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<double> dis(0, 0.4);  // Распределение для случайного смещения

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
		while (pos >= 0 && new_point[pos] == ranges[2 * pos + 1]) pos--;
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