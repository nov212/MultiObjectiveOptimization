#include <iostream>
#include "Functions.h"
#include "Solver.h"
//#include <xlsxwriter.h>

//void export_to_excel(const Grid& grid, const char* file_name)
//{
//    // Создание файла Excel
//    lxw_workbook* workbook = workbook_new(file_name);
//    lxw_worksheet* worksheet = workbook_add_worksheet(workbook, NULL);
//
//    int row = 0;
//    int col = 0;
//
//    // Запись точек сетки в таблицу Excel
//    for (const auto& point : grid) {
//        col = 0;
//        for (const auto& coordinate : point) {
//            worksheet_write_number(worksheet, row, col, coordinate, NULL);
//            ++col;
//        }
//        ++row;
//    }
//
//    // Закрытие и сохранение файла Excel
//    workbook_close(workbook);
//}

int main()
{
	Solver s;
	std::list<Point> result;
	int iterations = 1;
	int step = 100;
	int dimensions = 2;
	auto func = func_3;

	auto grid = GridBuilder::simple_grid_1(dimensions, step, ranges_func_3);
	result = s.grid_method(grid, func);


	for (auto& p : result)
	{
		for (auto& c : p)
			std::cout << c << " ";
		std::cout << "\n";
	}
}   
