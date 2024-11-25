#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "read_data.h"
#include "clean_data.h"
#include "output_data.h"

int main(int argc, char *argv[])
{
    int rows, cols;
    int new_rows; // For storing updated row count in case of deletion
    float *data = NULL;
    float *cleaned_data = NULL;

    // Check for the "-d" flag in the arguments
    int use_delete_strategy = 0; // Default to imputation
    if (argc > 1 && strcmp(argv[1], "-d") == 0)
    {
        use_delete_strategy = 1;
    }

    // Step 1: Read data
    data = read_data(&rows, &cols);
    if (data == NULL)
    {
        fprintf(stderr, "Failed to read data.\n");
        return EXIT_FAILURE;
    }

    // Step 2: Clean the data
    if (use_delete_strategy)
    {
        // Use deletion strategy
        cleaned_data = clean_delete(data, rows, cols, &new_rows);
        if (cleaned_data == NULL)
        {
            fprintf(stderr, "Failed to clean data using deletion strategy.\n");
            free(data); // Free the original data
            return EXIT_FAILURE;
        }
    }
    else
    {
        // Use imputation strategy
        clean_impute(data, rows, cols);
        cleaned_data = data; // No new memory allocated, so cleaned_data points to original
        new_rows = rows;     // Row count remains unchanged
    }

    // Step 3: Output the cleaned data
    output_data(cleaned_data, new_rows, cols);

    // Step 4: Free allocated memory
    if (cleaned_data != data)
    {
        free(cleaned_data); // Only free cleaned_data if it was newly allocated
    }
    free(data);

    return EXIT_SUCCESS;
}