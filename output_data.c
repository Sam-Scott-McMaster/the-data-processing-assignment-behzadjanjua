#include <stdio.h>
#include <stdlib.h>
#include "output_data.h"
/********************************
 * Outputs a 2D array of floating-point numbers in a formatted manner to standard output.
 * Behzad Janjua, McMaster University, Nov 25, 2024
 ********************************/

/********************************
 * Function: output_data
 * Description: Outputs a 2D float array to stdout, formatted with three decimal places.
 * Globals: None
 * Arguments:
 *   - data: Pointer to the 2D float array (flattened).
 *   - rows: Number of rows in the array.
 *   - cols: Number of columns in the array.
 * Outputs: Prints the array to stdout.
 * Returns: None
 ********************************/
void output_data(float *data, int rows, int cols)
{
    // Print the number of rows and columns as the first line
    printf("%d %d\n", rows, cols);

    // Loop through each row
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            // Print float value rounded to 3 decimal places
            printf("%.3f", data[i * cols + j]);

            // Add a space after each value except the last in the row
            if (j < cols - 1)
            {
                printf(" ");
            }
        }
        printf("\n"); // Move to the next line after each row
    }
}