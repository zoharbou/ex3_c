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
#include <malloc.h>
#include <mem.h>
#include "calculator.h"
#include "heat_eqn.h"

// -------------------------- const definitions -------------------------

/**
 * @var an error massage
 *@brief for the case that the file fail to open
 */

char *OPEN_FILE_ERROR = "Error! opening file";

char *SEPARATOR = "----";
char *NEW_LINE_BUFF = "%[^\n]";

#define TRUE 0
#define FALSE 1

// ------------------------------ functions -----------------------------
int readSeparator(FILE *file) {
    char currString[20];
    // find the separator
    fgets(currString, 20, file);
    // check to separator if its as expected
    if (strcmp(currString, SEPARATOR) == FALSE) {
        return FALSE;
    }
    return TRUE;
}

void initSourcePoint(int xCoordinate, int yCoordinate, float value, source_point *point) {
    point->x = xCoordinate;
    point->y = yCoordinate;
    point->value = value;
}

void newLine(FILE *file) {
    char currString[20];
    fscanf(file, NEW_LINE_BUFF, currString);
}

int getSizeOfCalcArea(size_t *n, size_t *m, FILE *file) {
    if (fscanf(file, "%u , %u[^\n]", n, m) != 2) { // if the input is not valid
        return FALSE;
    }
    return TRUE;

}

//TODO check NULL for all cases
source_point *getSourcePoints(FILE *file, size_t *numOfSourcePoints) {
    size_t currNumOfPoints = 0;
    int xCoordinate, yCoordinate;
    float value;
    source_point *sourcePoints = (source_point *) malloc(sizeof(source_point) * (currNumOfPoints));
    while (fscanf(file, " %d , %d , %f ", &xCoordinate, &yCoordinate, &value) == 3) {
        sourcePoints = realloc(sourcePoints, sizeof(source_point) * (currNumOfPoints + 1));
        initSourcePoint(xCoordinate, yCoordinate, value, &sourcePoints[currNumOfPoints++]);
    }
    *numOfSourcePoints = currNumOfPoints;
    return sourcePoints;
}

int getEndingVal(FILE *file, double *endingVal) {
    // Actual number ending value in scientific writing
    char endingValStr[20];
    if (fscanf(file, "%s", endingValStr) != 1) {
        return FALSE;
    }
    *endingVal = strtod(endingValStr, NULL);
    return TRUE;
}

int getIterationsNum(FILE *file, unsigned int *iterationsNum) {
    // Number of iterations between prints - zero for end printing only
    if (fscanf(file, "%u", iterationsNum) != 1) {
        return FALSE;
    }
    return TRUE;
}

int getIsCyclic(FILE *file, int *isCyclic) {
    if (fscanf(file, "%d", isCyclic) != 1) {
        return FALSE;
    }
    return TRUE;
}

double **buildGrid(size_t rows, size_t columns) {
    int i;
    double **grid = (double **) malloc(rows * sizeof(double *));
    for (i = 0; i < rows; i++) {
        grid[i] = (double *) malloc(columns * sizeof(double));
    }
    return grid;
}

void freeGrid(double **grid, size_t numOfRows) {
    int i;
    for (i = 0; i < numOfRows; i++) {
        free(grid[i]);
        grid[i] = NULL;
    }
    free(grid);
    grid = NULL;
}

int readFile(FILE *file) {
    size_t n, m;
    source_point *sourcePoints;
    double endingVal;
    unsigned int iterationsNum;
    int isCyclic;

    if (getSizeOfCalcArea(&n, &m, file) == FALSE || readSeparator(file) == FALSE) {
        return FALSE;
    }
    newLine(file); // pass to a new line in the file
    size_t numOfSourcePoints; // counter for the source points
    sourcePoints = getSourcePoints(file, &numOfSourcePoints);
    free(sourcePoints);

    if (readSeparator(file) == FALSE || getEndingVal(file, &endingVal) == FALSE ||
        getIterationsNum(file, &iterationsNum) || getIsCyclic(file, &isCyclic) == FALSE) {
        return FALSE;
    }
    double **grid = buildGrid(n, m);
    calculate(heat_eqn, grid, n, m, sourcePoints, numOfSourcePoints, endingVal, iterationsNum, isCyclic);
    freeGrid(grid, n);
    return TRUE;
}


int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("One argument expected.\n");
        return (1);
    }
    char *fileName = argv[1];
    FILE *file;
    if ((file = fopen(fileName, "r")) == NULL) {
        printf("%s", OPEN_FILE_ERROR);
        return (1);
    }
    if (readFile(file) == FALSE) {
        fprintf(stderr, "error while reading the file. the format was wrong");
    }
    fclose(file);
    return 0;
}
