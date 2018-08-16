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


typedef struct HeatSource
{
    int xCoordinate;
    int yCoordinate;
    float value;
} HeatSource;

// ------------------------------ function declarations -----------------------------


// ------------------------------ functions -----------------------------
int readSeparator(FILE *file)
{
    char currString[20];
    // find the separator
    fgets(currString, 20, file);
    // check to separator if its as expected
    if (strcmp(currString, SEPARATOR) == FALSE)
    {
        return FALSE;
    }
    return TRUE;
}

HeatSource *crateHeatSource(int xCoordinate, int yCoordinate, float value)
{
    return NULL;
}

int readFile(FILE *file)
{
    // Size of calculation area
    int n, m;
    if (fscanf(file, "%d , %d[^\n]", &n, &m) != 2)
    { // if the input is not valid
        return FALSE;
    }
    printf("%d %d\n", n, m);
    if (readSeparator(file) == FALSE)
    {
        return FALSE;
    }
    char currString[20];
    // pass to a new line
    fscanf(file, NEW_LINE_BUFF, currString);

    // List of coordinates of the heat sources and their value
    int xCoordinate, yCoordinate;
    float value;
    while (fscanf(file, " %d , %d , %f ", &xCoordinate, &yCoordinate, &value) == 3)
    {
        crateHeatSource(xCoordinate, yCoordinate, value);
        printf("%d %d %.2f\n", xCoordinate, yCoordinate, value);
    }
    if (readSeparator(file) == FALSE)
    {
        return FALSE;
    }

    // Actual number ending value in scientific writing
    char endingVal[20];
    if (fscanf(file, "%s", endingVal) != 1)
    {
        return FALSE;
    }

    // Number of iterations between prints - zero for end printing only
    int iterationsNum;
    if (fscanf(file, "%d", &iterationsNum) != 1)
    {
        return FALSE;
    }

    // Is circular (0 or 1)
    int isCircular;
    if (fscanf(file, "%d", &isCircular) != 1)
    {
        return FALSE;
    }

    printf("%s\n%d\n%d", endingVal, iterationsNum, isCircular);
    return TRUE;
}


int main()
{
    char fileName[100];
    char *toEnter = "C:\\Users\\Dell\\Desktop\\semester b\\c course\\ex3\\input.txt";
    FILE *file;
    memset(fileName, 0, 100);
    /*ask user for the name of the file*/
    printf("enter file name: ");
    gets(fileName);
    if ((file = fopen(fileName, "r")) == NULL)
    {
        printf(OPEN_FILE_ERROR);
        return (1);
    }
    if (readFile(file) == FALSE)
    {
        fprintf(stderr, "error while reading the file. the format was wrong");
    }
    fclose(file);
    return 0;
}
