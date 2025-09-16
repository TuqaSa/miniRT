/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaeed < tsaeed@student.42amman.com >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 19:55:00 by tsaeed            #+#    #+#             */
/*   Updated: 2025/09/16 23:18:25 by tsaeed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_matrix * matrix_create (int rows, int cols)
{
    t_matrix *matrix;
    int i;

    if (rows <= 0 || cols <= 0)
        return (NULL);

    matrix = malloc (sizeof (t_matrix));
    if (!matrix)
        return (NULL);

    matrix->rows = rows;
    matrix->cols = cols;

    matrix->data = malloc (rows * sizeof (float *));
    if (!matrix->data)
        {
            free (matrix);
            return (NULL);
        }
    i = 0;
    while (i < rows)
        {
            matrix->data[i] = malloc (cols * sizeof (float));
            if (!matrix->data[i])
                {
                    while (--i >= 0)
                        free (matrix->data[i]);
                    free (matrix->data);
                    free (matrix);
                    return (NULL);
                }
            int j = 0;
            while (j < cols)
                {
                    matrix->data[i][j] = 0.0f;
                    j++;
                }
            i++;
        }

    return (matrix);
}

/**
 * Destroys a matrix and frees all memory
 * @param matrix: Matrix to destroy
 */
void
matrix_destroy (t_matrix *matrix)
{
    int i;

    if (!matrix)
        return;

    if (matrix->data)
        {
            i = 0;
            while (i < matrix->rows)
                {
                    free (matrix->data[i]);
                    i++;
                }
            free (matrix->data);
        }

    free (matrix);
}

/**
 * Sets a value at specified position in the matrix
 * @param matrix: Target matrix
 * @param row: Row index (0-based)
 * @param col: Column index (0-based)
 * @param value: Value to set
 */
void
matrix_set (t_matrix *matrix, int row, int col, float value)
{
    if (!matrix || row < 0 || row >= matrix->rows || col < 0
        || col >= matrix->cols)
        return;

    matrix->data[row][col] = value;
}

/**
 * Gets a value from specified position in the matrix
 * @param matrix: Source matrix
 * @param row: Row index (0-based)
 * @param col: Column index (0-based)
 * @return: Value at specified position, or 0.0 if invalid
 */
float
matrix_get (t_matrix *matrix, int row, int col)
{
    if (!matrix || row < 0 || row >= matrix->rows || col < 0
        || col >= matrix->cols)
        return (0.0f);

    return (matrix->data[row][col]);
}

/**
 * Creates a matrix from a flat array of values (row-major order)
 * @param rows: Number of rows
 * @param cols: Number of columns
 * @param values: Array of values in row-major order
 * @return: Pointer to initialized matrix or NULL on failure
 */
t_matrix *
matrix_from_array (int rows, int cols, float values[])
{
    t_matrix *matrix;
    int i, j, index;

    matrix = matrix_create (rows, cols);
    if (!matrix)
        return (NULL);

    index = 0;
    i = 0;
    while (i < rows)
        {
            j = 0;
            while (j < cols)
                {
                    matrix->data[i][j] = values[index];
                    index++;
                    j++;
                }
            i++;
        }

    return (matrix);
}
