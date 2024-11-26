#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "clean_data.h"
/********************************
 * Implements the data cleaning strategies for machine learning datasets, including
 * deletion of rows with NaN values and imputation of NaN values with column averages.
 * Behzad Janjua, McMaster University, Nov 25, 2024
 ********************************/

/********************************
 * Function: clean_delete
 * Description: Removes rows containing NaN values from a 2D float array.
 * Globals: None
 * Arguments:
 *  - data: Pointer to the 2D float array (flattened).
 *   - rows: Number of rows in the array.
 *   - cols: Number of columns in the array.
 *   - new_rows: Pointer to an integer where the new row count will be stored.
 * Outputs: Dynamically allocated float array with rows containing NaN removed.
 * Returns: Pointer to the cleaned array or NULL if allocation fails.
 ********************************/
float *clean_delete(float *data, int rows, int cols, int *new_rows)
{
    // Allocate memory for the worst-case scenario (all rows are valid)
    float *filtered_data = malloc(rows * cols * sizeof(float));
    if (filtered_data == NULL)
    {
        // Memory allocation failed; return NULL
        printf("Memory allocation failed!\n");
        return NULL;
    }

    int valid_row_count = 0; // Counter for valid rows

    // Iterate through each row
    for (int row = 0; row < rows; row++)
    {
        int has_nan = 0; // Flag to indicate presence of NaN in the row

        // Check all columns in the current row for NaN
        for (int col = 0; col < cols; col++)
        {
            if (isnan(data[row * cols + col])) // Check if current element is NaN
            {
                has_nan = 1; // Mark row as invalid
                break;       // Exit the column loop early
            }
        }

        // If no NaN found, copy the row to the filtered array
        if (!has_nan)
        {
            for (int col = 0; col < cols; col++)
            {
                filtered_data[valid_row_count * cols + col] = data[row * cols + col];
            }
            valid_row_count++; // Increment count of valid rows
        }
    }

    // Reallocate memory to fit the actual number of valid rows
    filtered_data = realloc(filtered_data, valid_row_count * cols * sizeof(float));
    if (filtered_data == NULL)
    {
        // Memory reallocation failed; return NULL
        printf("Memory reallocation failed!\n");
        return NULL;
    }

    *new_rows = valid_row_count; // Update the new row count
    return filtered_data;        // Return pointer to cleaned data
}

/********************************
 * Function: clean_impute
 * Description: Replaces NaN values in a 2D float array with the column average.
 * Globals: None
 * Arguments:
 *   - data: Pointer to the 2D float array (flattened).
 *   - rows: Number of rows in the array.
 *   - cols: Number of columns in the array.
 * Outputs: Updates the input array in-place with NaN values replaced.
 * Returns: None
 ********************************/
void clean_impute(float *data, int rows, int cols)
{
    // Iterate through each column
    for (int col = 0; col < cols; col++)
    {
        float col_sum = 0.0; // Accumulator for the column sum
        int valid_count = 0; // Counter for valid (non-NaN) values

        // First pass: Calculate column sum and count valid values
        for (int row = 0; row < rows; row++)
        {
            int index = row * cols + col; // 1D index in the flattened array
            if (!isnan(data[index]))      // Check if value is valid
            {
                col_sum += data[index]; // Add to sum
                valid_count++;          // Increment valid count
            }
        }

        // Calculate column average
        float col_avg = (valid_count > 0) ? (col_sum / valid_count) : 0.0;

        // Second pass: Replace NaN values with the column average
        for (int row = 0; row < rows; row++)
        {
            int index = row * cols + col; // 1D index in the flattened array
            if (isnan(data[index]))       // Check if value is NaN
            {
                data[index] = col_avg; // Replace with column average
            }
        }
    }
}