/**
 * @file reader.c
 * @author  Zohar Bouchnik <zohar.bouchnik@mail.huji.ac.il>
 * @version 1.0
 * @date 19 aug 2018
 *
 * @brief the reader of the input file. it analyzes the data and pass it to calculation
 *
 * @section LICENSE
 * none
 *
 * @section DESCRIPTION
 *the reader of the input file. it analyzes the data and pass it to calculation
 * Input  : a file of the data
 * Process: analyze the data and read the file
 * Output : prints the results
 */

// ------------------------------ includes ------------------------------
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include "calculator.h"
#include "heat_eqn.h"

// -------------------------- const definitions -------------------------

/**
 * @var an error massage
 *@brief for the case that the number of args given is wrong
 */
char *ARGS_ERROR = "One argument expected.\n";

/**
 * the number of args expected in this program
 */
int NUM_OF_ARGS = 2;

/**
 *@var an error massage
 *@brief for the case that the file was writen in a bad format or the input given was not a legal input
 */
char *INPUT_FILE_ERROR = "Error while reading the file- the input is not valid";

/**
 * @var an error massage
 *@brief for the case that the file fail to open
 */

char *OPEN_FILE_ERROR = "Error! opening file";
/**
 * @brief the sign of the separation between the parts of the data in the given file
 */
char *SEPARATOR = "----";

/**
 * @brief a new line sign
 */
char NEW_LINE = '\n';

/**
 * @brief this is an error massage for the case that the malloc/realloc fails to allocate memory
 */
char *MEMORY_ERROR = "Fail to allocate memory";

/**
 * the initial value for a cell in the grid
 */
int INIT_VAL = 0;

/**
 * @brief true and false signs- for readability of the program
 */
#define TRUE 0
#define FALSE 1


// ------------------------------ functions -----------------------------

/**
 * this function moves the file pointer to a new line.
 * @param file the file we want to read
 */
void newLine(FILE *file)
{
    int curr;
    do
    {
        curr = fgetc(file);
    } while (curr != NEW_LINE);
}


/**
 * this function reads the next line in the given file and finds out if its a separator or not
 * @param file the file we read
 * @return TRUE if the line was a separator line, FALSE otherwise
 */
int readSeparator(FILE *file)
{
    char currString[20];
    // find the separator
    fgets(currString, 20, file);
    // check to separator if its as expected
    if (strncmp(currString, SEPARATOR, 3) != 0)
    {
        return FALSE;
    }
    return TRUE;
}

/**
 * this function inits the source point with the given values
 * @param xCoordinate the x coordinate for the point
 * @param yCoordinate the y coordinate for the point
 * @param value the value of the point
 * @param point the point we want to initialize
 */
void initSourcePoint(int xCoordinate, int yCoordinate, float value, source_point *point)
{
    point->x = xCoordinate;
    point->y = yCoordinate;
    point->value = value;
}

/**
 * this function reads from the file the number of rows and columns of the grid
 * @param n the number of rows pointer
 * @param m the number of columns pointer
 * @param file the file we read
 * @return TRUE for a successful reading of the data and false otherwise
 */
int getSizeOfCalcArea(size_t *n, size_t *m, FILE *file)
{
    int rows, cols;
    if (fscanf(file, "%d , %d", &rows, &cols) != 2 || rows <= 0 || cols <= 0)
    { // if the input is not valid
        return FALSE;
    }
    *n = (size_t) rows;
    *m = (size_t) cols;
    newLine(file);
    return TRUE;
}

/**
 * this function reads the source points from the file
 * @param file the file we want to read
 * @param numOfSourcePoints the number of source points that the reader finds
 * @return TRUE for a successful reading of the data and false otherwise
 */
//TODO CHECK THE INPUT OF THE POINTS- MAYBE OUT OF THE BOARD
source_point *getSourcePoints(FILE *file, size_t *numOfSourcePoints)
{
    size_t currNumOfPoints = 0;
    int xCoordinate, yCoordinate;
    float value;
    source_point *sourcePoints = (source_point *) malloc(sizeof(source_point) * (currNumOfPoints));
    if (sourcePoints == NULL)
    { // fail to allocate memory
        return NULL;
    }
    while (fscanf(file, " %d , %d , %f ", &xCoordinate, &yCoordinate, &value) == 3)
    {
        sourcePoints = realloc(sourcePoints, sizeof(source_point) * (currNumOfPoints + 1));
        if (sourcePoints == NULL)
        { // fail to allocate memory
            return NULL;
        }
        initSourcePoint(xCoordinate, yCoordinate, value, &sourcePoints[currNumOfPoints++]);
    }
    *numOfSourcePoints = currNumOfPoints;
    return sourcePoints;
}

/**
 * this function reads from the file the ending value given
 * @param file the file we want to read
 * @param endingVal the ending val pointer to init
 * @return TRUE for a successful reading of the data and false otherwise
 */
int getEndingVal(FILE *file, double *endingVal)
{
    // Actual number ending value in scientific writing
    char endingValStr[20];
    if (fscanf(file, "%s", endingValStr) != 1)
    {
        return FALSE;
    }
    *endingVal = strtod(endingValStr, NULL); // turn to a double
    return TRUE;
}

/**
 * this function reads the number of iterations between prints - zero for end printing only, from the file.
 * @param file : the file we want to read
 * @param iterationsNum : the number of iterations pointer to init
 * @return TRUE for a successful reading of the data and false otherwise
 */
int getIterationsNum(FILE *file, unsigned int *iterationsNum)
{
    int curr;
    if (fscanf(file, "%d", &curr) != 1 || curr < 0)
    { // if number of iteration is a negative number than its not valid
        return FALSE;
    }
    *iterationsNum = (unsigned int) curr;
    return TRUE;
}

/**
 * this function reads from the file the flag is cyclic. 0 for not cyclic and 1 for cyclic
 * @param file the file we want to read from
 * @param isCyclic the pointer to the flag we want to init
 * @return TRUE for a successful reading of the data and false otherwise
 */
int getIsCyclic(FILE *file, int *isCyclic)
{
    if (fscanf(file, "%d", isCyclic) != 1 || (*isCyclic != 0 && *isCyclic != 1))
    { // not a valid input
        return FALSE;
    }
    return TRUE;
}

/**
 * this function builds the grid- allocates memory for it and returns TRUE if it succeeded
 * @param grid : the pointer for the grid we want to build
 * @param rows : the number of rows of the grid
 * @param columns : the number of columns of the grid
 * @return TRUE for a successful allocating and false otherwise
 */
int buildGrid(double ***grid, size_t rows, size_t columns)
{
    *grid = (double **) malloc(rows * sizeof(double *));
    if (*grid == NULL)
    {
        return FALSE;
    }
    for (int i = 0; i < rows; ++i)
    {
        (*grid)[i] = (double *) malloc(columns * sizeof(double));
        if ((*grid)[i] == NULL)
        {
            return FALSE;
        }
    }
    return TRUE;
}

/**
 * this function inits the grid values to zero and adds the the grid the source points values
 * @param grid : the grid of all the cells holding their values
 * @param numOfRows : the number of rows in the grid
 * @param numOfCol : the number of columns in the grid
 * @param sources : the list of all the source points
 * @param numOfSources : the number of source points
 */
void initGrid(double **grid, size_t numOfRows, size_t numOfCol, source_point *sources, int numOfSources)
{
    int row, col;
    for (row = 0; row < numOfRows; ++row)
    {
        for (col = 0; col < numOfCol; ++col)
        {
            grid[row][col] = INIT_VAL;
        }
    }
    int i;
    for (i = 0; i < numOfSources; ++i)
    { // init source points in the grid
        grid[sources[i].x][sources[i].y] = sources[i].value;
    }
}

/**
 * this function free the memory allocated to the grid
 * @param grid : the grid of all the cells holding their values
 * @param numOfRows : the number of rows in the grid
 */
void freeGrid(double ***grid, size_t numOfRows)
{
    for (int i = 0; i < numOfRows; i++)
        free((*grid)[i]);
    free(*grid);
}

/**
 * this function prints the grid cells one by one and the result given from "calculate"
 * @param grid : the grid of all the cells holding their values
 * @param n : the number of rows in the grid
 * @param m : the number of columns in the grid
 * @param result : the result of calculate function
 */
void printResults(double **grid, size_t n, size_t m, double result)
{
    int i, j;
    printf("%lf\n", result);
    for (i = 0; i < n; ++i)
    {
        for (j = 0; j < m; ++j)
        {
            printf("%2.4lf,", grid[i][j]);
        }
        printf("\n");
    }
}

/**
 * this function activates the calculation and prints it
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
void activateCalc(diff_func function, double **grid, size_t n, size_t m, source_point *sources,
                  size_t num_sources, double terminate, unsigned int n_iter, int is_cyclic)
{
    double result;
    do
    {
        result = calculate(function, grid, n, m, sources, num_sources, terminate, n_iter, is_cyclic);
        printResults(grid, n, m, result);
    } while (result >= terminate);
    freeGrid(&grid, n);
    free(sources);
}

/**
 * this function checks if the given points from the input file are in the board limits
 * @param n the number of rows in the grid
 * @param m the number of columns in the grid
 * @param sources the list of given source points
 * @param sourcePointsNum the number of source points
 * @return TRUE if all the points are valid and false otherwise
 */
int areSourcesInBoard(size_t n, size_t m, source_point *sources, size_t sourcePointsNum)
{
    int i;
    for (i = 0; i < sourcePointsNum; ++i)
    {
        if (sources[i].x >= n || sources[i].x < 0 || sources[i].y >= m || sources[i].y < 0)
        {
            return FALSE;
        }
    }
    return TRUE;
}

/**
 *this function reads line by line the given file and init the values of what it read
 *for all the pointers that are its parameters
 * @param file the file to read
 * @param n a pointer for the number of rows
 * @param m a pointer for the number of columns
 * @param sourcePoints a pointer for the list of source points
 * @param numOfSourcePoints a pointer for the number of source points
 * @param endingVal a pointer for the ending val
 * @param iterationsNum a pointer for the number of iterations
 * @param isCyclic a pointer for the is cyclic flag
 * @return FALSE for a problem while reading the file input. TRUE otherwise
 */
int readLines(FILE *file, size_t *n, size_t *m, source_point **sourcePoints, size_t *numOfSourcePoints,
              double *endingVal, unsigned int *iterationsNum, int *isCyclic)
{
    if (getSizeOfCalcArea(n, m, file) == FALSE || readSeparator(file) == FALSE)
    {
        return FALSE;
    }
    *sourcePoints = getSourcePoints(file, numOfSourcePoints);
    if (*sourcePoints == NULL)
    {
        fprintf(stderr, "%s", MEMORY_ERROR);
        return FALSE;
    }
    if (areSourcesInBoard(*n, *m, *sourcePoints, *numOfSourcePoints) == FALSE)
    {
        return FALSE;
    }
    if (readSeparator(file) == FALSE || getEndingVal(file, endingVal) == FALSE ||
        getIterationsNum(file, iterationsNum) || getIsCyclic(file, isCyclic) == FALSE)
    {
        return FALSE;
    }
    return TRUE;
}

/**
 * this function reads the file given, analyzes the results and prints them
 * @param file the file we want to read
 * @return TRUE for a successful reading, FALSE otherwise
 */
int readFile(FILE *file)
{
    // parameters we want to read from the file:
    size_t n, m;
    source_point *sourcePoints = NULL;
    size_t numOfSourcePoints;
    double endingVal;
    unsigned int iterationsNum;
    int isCyclic;

    if (readLines(file, &n, &m, &sourcePoints, &numOfSourcePoints, &endingVal, &iterationsNum, &isCyclic) == FALSE)
    {
        free(sourcePoints);
        return FALSE;
    }

    double **grid;
    if (buildGrid(&grid, n, m) == FALSE)
    {
        fprintf(stderr, "%s", MEMORY_ERROR);
        freeGrid(&grid, numOfSourcePoints);
        free(sourcePoints);
        return FALSE;
    }
    initGrid(grid, n, m, sourcePoints, numOfSourcePoints);
    activateCalc(heat_eqn, grid, n, m, sourcePoints, numOfSourcePoints, endingVal, iterationsNum, isCyclic);
    return TRUE;
}

/**
 * the main function that runs the program
 * @param argc the number of argument given
 * @param argv the list of arguments- the file address
 * @return 0 for proper run- 1 otherwise
 */
int main(int argc, char *argv[])
{
    if (argc != NUM_OF_ARGS)
    {
        printf("%s", ARGS_ERROR);
        return (1);
    }
    char *fileName = argv[1];
    FILE *file;
    if ((file = fopen(fileName, "r")) == NULL) // open only for reading
    {
        printf("%s", OPEN_FILE_ERROR);
        return (1);
    }
    if (readFile(file) == FALSE)
    {
        fprintf(stderr, "%s", INPUT_FILE_ERROR);
        fclose(file);
        return (1);
    }
    fclose(file);
    return 0;
}
