/**
 * @file
 * @author  Zohar Bouchnik <zohar.bouchnik@mail.huji.ac.il>
 * @version 1.0
 * @date 01 oct 2018
 *
 * @brief
 *
 * @section LICENSE
 * none
 *
 * @section DESCRIPTION
 *
 * Input  :
 * Process:
 * Output :
 */

// ------------------------------ includes ------------------------------
#include <stdio.h>

// -------------------------- const definitions -------------------------

typedef double (*diff_func)(double right, double top, double left, double bottom);

typedef struct point{

}point;


/**
 * @var
 *@brief
 */


// ------------------------------ function declarations -----------------------------


// ------------------------------ functions -----------------------------


// the calculate func
double calculate(diff_func function, double **grid, size_t n, size_t m, point *sources,
                 size_t num_sources, double terminate, int n_iter, int is_cyclic){

}
