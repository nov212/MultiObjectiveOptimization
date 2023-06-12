#include <iostream>
#include "Functions.h"
#include "Solver.h"
#include <xlsxwriter.h>

/*
* func_1
* f1 = 4 - (x - 2)^2
* f2 = |x - 1|
* D = [0, 4]
* solution [0, 1]
* 
* func_2
* f1 = (x - 9)^2 - 2
* f2 = 6 - 0.5x
* D = [0; 16]
* solution [9, 16]
* 
* func_3
* f1 = 1/(x1^2 + x2^2 + 1)
* f2 = x1^2 + 3x2^2 + 1
* D = x1, x2 [-3; 3]
* solution x1 = -3 x2 = [-3; 3] ; x1 = [-3; 3] x2 = 0; x1 = 3 x2 = [-3; 3]
* 
* func_4
* f1 = sqrt(x1*x2)
* f2 = 2 - x1 - x2
* D = x1, x2 [0; 1]
* solution x1 = [0; 1] x2 = 1; x1 = 1 x2 = [0; 1]
* 
* func_5
* f1 = x1^2 + x2^2
* f2 = 2 - x1 - x2
* D = x1, x2 [0; 1]
* solution x1 = [0; 1] x2 = x1
* 
* func_6
* f1 = x1^2 + x2^2
* f2 = 5 - x1 - x2
* D = x1 [0; 2] x2 [0; 1]
* solution x1 [0, 1] x2 = x1; x1 [1; 2] x2 = 1
*/

void export_to_excel(const Grid& grid, const char* file_name)
{
    // Создание файла Excel
    lxw_workbook* workbook = workbook_new(file_name);
    lxw_worksheet* worksheet = workbook_add_worksheet(workbook, NULL);

    int row = 0;
    int col = 0;

    // Запись точек сетки в таблицу Excel
    for (const auto& point : grid) {
        col = 0;
        for (const auto& coordinate : point) {
            worksheet_write_number(worksheet, row, col, coordinate, NULL);
            ++col;
        }
        ++row;
    }

    // Закрытие и сохранение файла Excel
    workbook_close(workbook);
}

int main()
{
	Solver s;
	std::list<Point> result;
	int iterations = 1;
	int step_1 = 100;
    int step_2 = 10;
	int dimensions = 2;
	auto func = func_3;

    std::vector<double> length_1;
    for (int i = 0; i < ranges_func_1.size(); i += 2)
        length_1.push_back((ranges_func_1[i + 1] - ranges_func_1[i]) / step_1);
    double alpha_1 = *std::min(length_1.begin(), length_1.end());
    alpha_1 /= 2;
    auto grid = GridBuilder::uniform_distribution_grid_2(dimension_func_1, 100, ranges_func_1);
	result = s.grid_method(grid, func_1);
    export_to_excel(result, "m4_1000_1_func_1.xlsx");

    std::vector<double> length_2;
    for (int i = 0; i < ranges_func_2.size(); i += 2)
        length_2.push_back((ranges_func_2[i + 1] - ranges_func_2[i]) / step_1);
    double alpha_2 = *std::min(length_2.begin(), length_2.end());
    alpha_2 /= 2;
    grid = GridBuilder::uniform_distribution_grid_2(dimension_func_2, 100, ranges_func_2);
    result = s.grid_method(grid, func_2);
    export_to_excel(result, "m4_1000_1_func_2.xlsx");

    std::vector<double> length_3;
    for (int i = 0; i < ranges_func_3.size(); i += 2)
        length_3.push_back((ranges_func_3[i + 1] - ranges_func_3[i]) / step_2);
    double alpha_3 = *std::min(length_3.begin(), length_3.end());
    alpha_3 /= 2;
    grid = GridBuilder::uniform_distribution_grid_2(dimension_func_3, 100, ranges_func_3);
    result = s.grid_method(grid, func_3);
    export_to_excel(result, "m4_1000_1_func_3.xlsx");

    std::vector<double> length_4;
    for (int i = 0; i < ranges_func_3.size(); i += 2)
        length_4.push_back((ranges_func_3[i + 1] - ranges_func_4[i]) / step_2);
    double alpha_4 = *std::min(length_4.begin(), length_4.end());
    alpha_4 /= 2;
    grid = GridBuilder::uniform_distribution_grid_2(dimension_func_4, 1000, ranges_func_4);
    result = s.grid_method(grid, func_4);
    export_to_excel(result, "m4_1000_1_func_4.xlsx");

    std::vector<double> length_5;
    for (int i = 0; i < ranges_func_5.size(); i += 2)
        length_5.push_back((ranges_func_5[i + 1] - ranges_func_5[i]) / step_2);
    double alpha_5 = *std::min(length_5.begin(), length_5.end());
    alpha_5 /= 2;
    grid = GridBuilder::uniform_distribution_grid_2(dimension_func_5, 100, ranges_func_5);
    result = s.grid_method(grid, func_5);
    export_to_excel(result, "m4_1000_1_func_5.xlsx");

    std::vector<double> length_6;
    for (int i = 0; i < ranges_func_6.size(); i += 2)
        length_6.push_back((ranges_func_6[i + 1] - ranges_func_6[i]) / step_2);
    double alpha_6 = *std::min(length_6.begin(), length_6.end());
    alpha_6 /= 2;
    grid = GridBuilder::uniform_distribution_grid_2(dimension_func_6, 100, ranges_func_6);
    result = s.grid_method(grid, func_6);
    export_to_excel(result, "m4_1000_1_func_6.xlsx");

    //std::vector<double> length_3;
    //for (int i = 0; i < ranges_func_3.size(); i += 2)
    //    length_3.push_back((ranges_func_3[i + 1] - ranges_func_3[i]) / step_2);
    //double alpha_3 = *std::min(length_3.begin(), length_3.end());
    //alpha_3 /= 2;
    //std::cout << alpha_3;
    //auto grid = GridBuilder::uniform_distribution_grid_2(dimension_func_3, 25, {-3, 3, -3, 3});
    ////result = s.grid_method(grid, func_1);
    //export_to_excel(grid, "grid.xlsx");
}   
