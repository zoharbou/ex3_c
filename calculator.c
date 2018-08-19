/**
 * @file calculator.c
 * @author  Zohar Bouchnik <zohar.bouchnik@mail.huji.ac.il>
 * @version 1.0
 * @date 19 aug 2018
 *
 * @brief
 * a program that solves the heat equation in numerical form
 *
 * @section LICENSE
 * none
 *
 * @section DESCRIPTION
 *
 * Input  : the parameters of the calculate function
 * Process:
 * Output : the heat difference in the last round
 */

// ------------------------------ includes ------------------------------
#include <stdio.h>
#include "calculator.h"

// -------------------------- const definitions -------------------------

/**
 * @var the directions of the neighbors for a current cell
 *@brief names of the different directions for the cell's neighbors
 */
typedef enum Directions
{
    UP, DOWN, RIGHT, LEFT
} Direction;


#define TRUE 0
#define FALSE 1

// ------------------------------ functions -----------------------------

/**
 * this function calculates mod operation using floor other that rounding through zero.
 * (in positive numbers its the same as % but in negative num the result is different)
 * @param x the value we want to calculate an Integer
 * @param N the filed of mod to calculate. a non negative num
 * @return mod(x,N) the reminder after division of x in N.
 */
int myMod(int x, int N)
{
    return (x % N + N) % N;
}

/**
 * this function returns the value of the wanted neighbor of the given cell.
 * @param direction : the direction of the neighbor in relation to the given cell (up,down,right,left)
 * @param grid : the grid of all the cells holding their values
 * @param rowIndex : the row index of the cell we want to check
 * @param colIndex : the col index of the cell we want to check
 * @param n : the number of rows in the grid
 * @param m : the number of columns in the grid
 * @param isCyclic : 1 if its cyclic and 0 if its not. for cyclic we will use mod to get the neighbors
 * @return the value of the wanted neighbor
 */
double getNeighbor(Direction direction, double **grid, int rowIndex, int colIndex, size_t n, size_t m, int isCyclic)
{
    int rowNeighbor = rowIndex, colNeighbor = colIndex;
    switch (direction)
    {
        case UP:
            rowNeighbor++;
            break;
        case DOWN:
            rowNeighbor--;
            break;
        case RIGHT:
            colNeighbor++;
            break;
        case LEFT:
            colNeighbor--;
            break;
    }
    if (isCyclic)
    {
        rowNeighbor = myMod(rowNeighbor, n);
        colNeighbor = myMod(colNeighbor, m);
    }
    if (rowNeighbor > n || rowNeighbor < 0 || colNeighbor > m || colNeighbor < 0)
    {
        return 0;
    }
    return grid[rowNeighbor][colNeighbor];
}

/**
 * this function returns TRUE if the given cell is a source point and FALSE otherwise
 * @param rowIndex : the row index of the cell we want to check
 * @param colIndex : the col index of the cell we want to check
 * @param sources : the list of the source points
 * @param num_sources : the number of source points
 * @return TRUE if the given cell is a source point and FALSE otherwise
 */
int isSourcePoint(int rowIndex, int colIndex, source_point *sources, size_t num_sources)
{
    int i;
    for (i = 0; i < num_sources; ++i)
    {
        if (sources[i].x == rowIndex && sources[i].y == colIndex)
        {
            return TRUE;
        }
    }
    return FALSE;
}

/**
 * this function goes throw all the cells in the grid and if the cell is not a source point, it will
 * use the function given to calculate it's new value.
 * @param function : the function that calculates the new value of the cell
 * @param grid : the grid of all the cells holding their values
 * @param n : the number of rows in the grid
 * @param m : the number of columns in the grid
 * @param isCyclic : 1 if its cyclic and 0 if its not. for cyclic we will use mod to get the neighbors
 * @param sources : the list of the source points
* @param num_sources : the number of source points
 */
void updateAllValues(diff_func function, double **grid, size_t n, size_t m, int isCyclic, source_point *sources,
                     size_t num_sources)
{
    int row, col;
    double up, down, right, left;
    for (row = 0; row < n; ++row)
    {
        for (col = 0; col < m; ++col)
        {
            if (isSourcePoint(row, col, sources, num_sources) == FALSE)
            {
                up = getNeighbor(UP, grid, row, col, n, m, isCyclic);
                down = getNeighbor(DOWN, grid, row, col, n, m, isCyclic);
                right = getNeighbor(RIGHT, grid, row, col, n, m, isCyclic);
                left = getNeighbor(LEFT, grid, row, col, n, m, isCyclic);
                grid[row][col] = function(right, up, left, down);
            }
        }
    }
}

/**
 * this function sums all the values in the grid
 * @param grid : the grid of all the cells holding their values
 * @param n : the number of rows in the grid
 * @param m : the number of columns in the grid
 * @return the sum of all the values in the grid
 */
double getSumOfHeat(double **grid, size_t n, size_t m)
{
    int row, col;
    double sum = 0;
    for (row = 0; row < n; ++row)
    {
        for (col = 0; col < m; ++col)
        {
            sum += grid[row][col];
        }
    }
    return sum;
}

/**
 * this function calculates the heat equation.
 * @param function : the function that calculates the new value of the cell
 * @param grid : the grid of all the cells holding their values
 * @param n : the number of rows in the grid
 * @param m : the number of columns in the grid
 * @param sources : the list of the source points
 * @param num_sources : the number of source points
 * @param terminate : the termination value
 * @param n_iter : the number of iterations given
 * @param isCyclic : 1 if its cyclic and 0 if its not. for cyclic we will use mod to get the neighbors
 * @return the heat difference in the last round
 */
double calculate(diff_func function, double **grid, size_t n, size_t m, source_point *sources,
                 size_t num_sources, double terminate, unsigned int n_iter, int is_cyclic)
{
    double initialHeatAmount = getSumOfHeat(grid, n, m);
    double currHeatAmount = initialHeatAmount;
    if (n_iter > 0)
    { // the number of iterations is initialized with a positive value
        int i;
        for (i = 0; i < n_iter; ++i)
        {
            initialHeatAmount = currHeatAmount;
            updateAllValues(function, grid, n, m, is_cyclic, sources, num_sources);
            currHeatAmount = getSumOfHeat(grid, n, m);
        }
    }
    else
    { // n_iter is zero so we use the terminate value
        do
        {
            initialHeatAmount = currHeatAmount;
            updateAllValues(function, grid, n, m, is_cyclic, sources, num_sources);
            currHeatAmount = getSumOfHeat(grid, n, m);
        } while (currHeatAmount - initialHeatAmount >= terminate);
    }
    return currHeatAmount - initialHeatAmount;
}
