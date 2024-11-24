#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "read_data.h"

float *read_data(int *rows, int *cols)
{
    // Read the number of rows and columns
    scanf("%d %d", rows, cols);

    // Calculate the total size of the data array
    int size = (*rows) * (*cols);

    // Allocate memory for the data array
    float *data = malloc(size * sizeof(float));
    if (data == NULL)
    {
        printf("Memory allocation failed!\n");
        exit(1);
    }

    // Read float values directly into the array
    for (int i = 0; i < size; i++) // Iterate through every index
    {
        scanf("%f", &data[i]);
    }

    // Return the pointer to the allocated data
    return data;
}