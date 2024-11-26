#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "read_data.h"
#include "clean_data.h"
#include "output_data.h"
/********************************
 * Main entry point for the clean utility. Handles reading data, invoking cleaning functions,
 * and outputting cleaned data based on the selected cleaning strategy.
 * Behzad Janjua, McMaster University, Nov 25, 2024
 ********************************/

/********************************
 * Function: main
 * Description: Main entry point for the program. Handles data cleaning based on the strategy (deletion or imputation).
 * Globals: None
 * Arguments:
 *   - argc: Number of command-line arguments.
 *   - argv: Array of command-line arguments.
 * Outputs: Prints cleaned data to stdout.
 * Returns: Exit code (EXIT_SUCCESS or EXIT_FAILURE).
 ********************************/
int main(int argc, char *argv[])
{
    int rows;                   // Number of rows in the dataset
    int cols;                   // Number of columns in the dataset
    int new_rows;               // Updated number of rows (after cleaning)
    float *data = NULL;         // Pointer to the original dataset
    float *cleaned_data = NULL; // Pointer to the cleaned dataset

    // Check if the "-d" flag is provided for deletion strategy
    int use_delete_strategy = 0; // Default cleaning strategy is imputation
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

    // Step 2: Clean data based on the selected strategy
    if (use_delete_strategy)
    {
        // Apply deletion strategy
        cleaned_data = clean_delete(data, rows, cols, &new_rows);
        if (cleaned_data == NULL)
        {
            fprintf(stderr, "Failed to clean data using deletion strategy.\n");
            free(data); // Free original memory
            return EXIT_FAILURE;
        }
    }
    else
    {
        // Apply imputation strategy
        clean_impute(data, rows, cols);
        cleaned_data = data; // No new allocation; cleaned_data points to the original
        new_rows = rows;     // Row count remains unchanged
    }

    // Step 3: Output cleaned data
    output_data(cleaned_data, new_rows, cols);

    // Step 4: Free allocated memory
    if (cleaned_data != data)
    {
        free(cleaned_data); // Free cleaned_data only if it was newly allocated
    }
    free(data); // Free original data memory

    return EXIT_SUCCESS; // Successful program termination
}