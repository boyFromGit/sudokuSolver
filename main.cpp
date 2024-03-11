#include <iostream>
#include <array>
using namespace std;

// grid size
const int N = 9;

using Grid = array<array<int, N>, N>;

void printGrid(Grid grid)
{
    for (size_t i = 0; i < N; i++)
    {
        if (i % 3 == 0)
        {
            cout << " -------------------------" << endl;
        }
        for (size_t j = 0; j < N; j++)
        {
            if (j % 3 == 0)
            {
                cout << " | ";
            }
            else
            {
                cout << ' ';
            }
            cout << grid[i][j];
        }
        cout << " |" << endl;
    }
    cout << " -------------------------" << endl;
}

// checks if a value is valid in a specific cell
bool isSafe(Grid grid, int row, int col, int value)
{
    // check the row for that value
    for (size_t i = 0; i < N; i++)
    {
        if (grid[row][i] == value)
        {
            return false;
        }
    }

    // check the column for that value
    for (size_t i = 0; i < N; i++)
    {
        if (grid[i][col] == value)
        {
            return false;
        }
    }

    int start_row = row - row % 3;
    int start_col = col - col % 3;

    // check the box for that value
    for (size_t i = start_row; i < start_row + 3; i++)
    {
        for (size_t j = start_col; j < start_col + 3; j++)
        {
            if (grid[i][j] == value)
            {
                return false;
            }
        }
    }
    return true;
}

bool solveSudoku(Grid &grid, int row, int col)
{
    // check if at the end of sudoku
    if (row == N - 1 && col == N)
    {
        return true;
    }

    // check if at the end of a row
    if (col == N)
    {
        row++;
        col = 0;
    }

    // check if there is already a number inside the current cell (0 indicates there is no number)
    if (grid[row][col] != 0)
    {
        return solveSudoku(grid, row, col + 1);
    }

    // test every number and backtrack if something went wrong
    for (size_t i = 1; i <= N; i++)
    {
        if (isSafe(grid, row, col, i))
        {
            grid[row][col] = i;
            if (solveSudoku(grid, row, col + 1))
            {
                return true;
            }
        }
        grid[row][col] = 0;
    }
    return false;
}

int main()
{
    Grid grid{{
        {5, 3, 0, 0, 7, 0, 0, 0, 0},
        {6, 0, 0, 1, 9, 5, 0, 0, 0},
        {0, 9, 8, 0, 0, 0, 0, 6, 0},
        {8, 0, 0, 0, 6, 0, 0, 0, 3},
        {4, 0, 0, 8, 0, 3, 0, 0, 1},
        {7, 0, 0, 0, 2, 0, 0, 0, 6},
        {0, 6, 0, 0, 0, 0, 2, 8, 0},
        {0, 0, 0, 4, 1, 9, 0, 0, 5},
        {0, 0, 0, 0, 8, 0, 0, 7, 9},
    }};

    if (solveSudoku(grid, 0, 0))
    {
        printGrid(grid);
    }
    else
    {
        cout << "There is no possible solution for this sudoku.";
    }

    return 0;
}
