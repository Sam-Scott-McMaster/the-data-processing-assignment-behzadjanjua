#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "read_data.h"
/********************************
 * Provides functionality to read a 2D array of floating-point numbers from standard input
 * and allocate memory dynamically for the array.
 * Behzad Janjua, McMaster University, Nov 25, 2024
 ********************************/

/********************************
 * Function: read_data
 * Description: Reads a 2D float array from stdin, with dimensions specified as input.
 * Globals: None
 * Arguments:
 *   - rows: Pointer to an integer to store the number of rows.
 *   - cols: Pointer to an integer to store the number of columns.
 * Outputs: Dynamically allocated float array read from stdin.
 * Returns: Pointer to the array or exits on failure.
 ********************************/
float *read_data(int *rows, int *cols)
{
    // Read dimensions (rows and columns)
    scanf("%d %d", rows, cols);

    // Calculate total size of the array
    int size = (*rows) * (*cols);

    // Allocate memory for the array
    float *data = malloc(size * sizeof(float));
    if (data == NULL)
    {
        printf("Memory allocation failed!\n");
        exit(1); // Exit program on memory failure
    }

    // Read values into the array
    for (int i = 0; i < size; i++)
    {
        scanf("%f", &data[i]);
    }

    return data; // Return pointer to the allocated data
}