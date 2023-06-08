#pragma once
#include <vector>

std::vector<double> func_1(const std::vector<double>& point)
{
	std::vector<double> res(2);
	res[0] = pow(pow(point[0], 2) + pow(point[1], 2) + 1, -1);
	res[1] = pow(point[0], 2) + 3 * pow(point[1], 2) + 1;
	return res;
}

std::vector<double> func_2(const std::vector<double>& point)
{
	std::vector<double> res(2);
	res[0] = 4 - pow(point[0] - 2, 2);
	res[1] = abs(point[0] - 1);
	return res;
}

std::vector<double> func_3(const std::vector<double>& point)
{
	std::vector<double> res(1);
	res[0] = pow(point[0] - 9, 2)-2;
	res[1] = 6-0.5*point[0];
	return res;
}