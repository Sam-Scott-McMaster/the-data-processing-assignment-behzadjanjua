#include <stdio.h>
#include <stdlib.h>
#include "read_data.h"
#include "clean_data.h"

#include <stdio.h>

void output_data(float *data, int rows, int cols)
{
    // Loop through each row
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            // Print the float value rounded to 3 decimal places
            printf("%.3f", data[i * cols + j]);

            // Add a space after each value except the last in the row
            if (j < cols - 1)
            {
                printf(" ");
            }
        }
        // Move to the next line after each row
        printf("\n");
    }
}