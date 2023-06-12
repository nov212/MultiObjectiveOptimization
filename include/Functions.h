#pragma once
#include <vector>

std::vector<double> func_1(const std::vector<double>& point)
{
	std::vector<double> res(2);
	res[0] = 4 - pow(point[0] - 2, 2);
	res[1] = abs(point[0] - 1);
	return res;
}
std::vector<double> ranges_func_1 = {0, 4};
int dimension_func_1 = 1;

std::vector<double> func_2(const std::vector<double>& point)
{
	std::vector<double> res(2);
	res[0] = pow(point[0] - 9, 2)-2;
	res[1] = 6-0.5*point[0];
	return res;
}
std::vector<double> ranges_func_2 = { 0, 16 };
int dimension_func_2 = 1;

std::vector<double> func_3(const std::vector<double>& point)
{
	std::vector<double> res(2);
	res[0] = pow(pow(point[0], 2) + pow(point[1], 2) + 1, -1);
	res[1] = pow(point[0], 2) + 3 * pow(point[1], 2) + 1;
	return res;
}
std::vector<double> ranges_func_3 = { -3, 3, -3, 3 };
int dimension_func_3 = 2;

std::vector<double> func_4(const std::vector<double>& point)
{
	std::vector<double> res(2);
	res[0] = sqrt(point[0]*point[1]);
	res[1] = 2 - point[0] - point[1];
	return res;
}
std::vector<double> ranges_func_4 = { 0, 1, 0, 1 };
int dimension_func_4 = 2;

std::vector<double> func_5(const std::vector<double>& point)
{
	std::vector<double> res(2);
	res[0] = pow(point[0], 2) + pow(point[1], 2);
	res[1] = 2 - point[0] - point[1];
	return res;
}
std::vector<double> ranges_func_5 = { 0, 1, 0, 1 };
int dimension_func_5 = 2;

std::vector<double> func_6(const std::vector<double>& point)
{
	std::vector<double> res(2);
	res[0] = pow(point[0], 2) + pow(point[1], 2);
	res[1] = 5 - point[0] - point[1];
	return res;
}
std::vector<double> ranges_func_6 = { 0, 2, 0, 1 };
int dimension_func_6 = 2;