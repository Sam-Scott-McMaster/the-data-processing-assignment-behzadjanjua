#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "clean_data.h"

// Function to remove rows containing NaN values
float *clean_delete(float *data, int rows, int cols, int *new_rows)
{
    // Allocate memory for the worst-case scenario (all rows are valid)
    float *filtered_data = malloc(rows * cols * sizeof(float));
    if (filtered_data == NULL)
    {
        printf("Memory allocation failed!\n");
        return NULL;
    }

    int valid_row_count = 0; // Track the number of valid rows

    // Iterate through each row
    for (int row = 0; row < rows; row++)
    {
        int has_nan = 0; // Reset flag for each new row

        // Check the row for NaN
        for (int col = 0; col < cols; col++)
        {
            if (isnan(data[row * cols + col]))
            {
                has_nan = 1; // Mark the row as invalid
                break;       // Stop checking further columns in this row
            }
        }

        // If the row is valid, copy it to the filtered array
        if (!has_nan)
        {
            for (int col = 0; col < cols; col++)
            {
                filtered_data[valid_row_count * cols + col] = data[row * cols + col];
            }
            valid_row_count++; // Increment valid row count
        }
    }

    // Reallocate memory to fit only the valid rows
    filtered_data = realloc(filtered_data, valid_row_count * cols * sizeof(float));
    if (filtered_data == NULL)
    {
        printf("Memory reallocation failed!\n");
        return NULL;
    }

    *new_rows = valid_row_count; // Update the number of valid rows
    return filtered_data;        // Return the filtered array
}

void clean_impute(float *data, int rows, int cols)
{
    // Outer loop: Iterate through each column in the 2D array
    for (int col = 0; col < cols; col++)
    {
        // Initialize variables to calculate the column's average
        float col_sum = 0.0; // Variable to store the sum of all valid (non-NaN) values in the column
        int valid_count = 0; // Counter to track the number of valid (non-NaN) values in the column

        // First pass: Traverse the rows of the current column to compute sum and count
        for (int row = 0; row < rows; row++)
        {
            // Calculate the 1D index for the current element in the flattened 2D array
            int index = row * cols + col;

            // Check if the current element is a valid (non-NaN) float value
            if (!isnan(data[index])) // Use the <math.h> function isnan to test for NaN
            {
                col_sum += data[index]; // Add the value of the element to the column sum
                valid_count++;          // Increment the counter for valid (non-NaN) values
            }
        }

        // Compute the column average using the sum and count of valid values
        // If valid_count > 0, calculate the average normally; otherwise, set it to 0.0
        float col_avg; // Declare the variable for the column average
        if (valid_count > 0)
        {
            col_avg = col_sum / valid_count; // Calculate the average if there are valid values
        }
        else
        {
            col_avg = 0.0; // Set the average to 0.0 if no valid values exist
        }

        // Second pass: Replace all NaN values in the column with the computed column average
        for (int row = 0; row < rows; row++)
        {
            // Calculate the 1D index for the current element in the flattened 2D array
            int index = row * cols + col;

            // Check if the current element is NaN
            if (isnan(data[index])) // Use isnan to identify NaN values
            {
                data[index] = col_avg; // Replace NaN with the computed column average
            }
        }
    }
}