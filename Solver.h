#pragma once
#include "GridBuilder.h"

class Solver
{
public:
	std::list<Point> grid_method(GridBuilder& grid_builder, std::vector<double>(*func)(const Point&), 
									uint32_t iterations, uint16_t step, const std::vector<double>& ranges);
private:
	enum cmp_state_t
	{
		DEFAULT = -2,
		WORSE = -1,
		NON_COMPARABLE = 0,
		BETTER = 1
	};

	/// <summary>
	/// ���������� ����� �� ���� ����� ���������� ����� ��� �������� �� ��� ������������.
	/// ������� ���������� �������� ��������� � ������ � ���������� ��������� ��������� � ���� ������ ����� �� ������.
	/// </summary>
	/// <param name="p1">������ ������������ �����</param>
	/// <param name="p2">������ ������������ �����</param>
	/// <param name="func">�������� ������</param>
	/// <returns>
	/// 0 - ����� ����������;
	/// 1 - p1 ���������� ����� p2;
	/// -1 - p2 ���������� ����� p1;
	/// </returns>
	int8_t compare(const Point& p1, const Point& p2, std::vector<double> (*func)(const Point&));
};