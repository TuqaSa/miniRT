/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaeed < tsaeed@student.42amman.com >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 23:50:00 by tsaeed            #+#    #+#             */
/*   Updated: 2025/10/13 07:07:46 by tsaeed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/**
 * Creates a 4x4 matrix initialized to zero
 * @return: Zero-initialized 4x4 matrix
 */
t_matrix4
matrix4_create (void)
{
    t_matrix4 matrix;

    int i, j;
    i = 0;
    while (i < 4)
        {
            j = 0;
            while (j < 4)
                {
                    matrix.m[i][j] = 0.0;
                    j++;
                }
            i++;
        }
    return (matrix);
}

/**
 * Creates a 4x4 identity matrix
 * Identity matrix has 1.0 on the diagonal and 0.0 elsewhere
 * When multiplied with any matrix or tuple, returns the original unchanged
 * @return: 4x4 identity matrix
 */
t_matrix4
matrix4_identity (void)
{
    t_matrix4 matrix;
    int i;
    int j;

    i = 0;
    while (i < 4)
        {
            j = 0;
            while (j < 4)
                {
                    if (i == j)
                        matrix.m[i][j] = 1.0;
                    else
                        matrix.m[i][j] = 0.0;
                    j++;
                }
            i++;
        }
    return (matrix);
}

/**
 * Creates a 4x4 matrix from an array of values
 * Values should be provided in row-major order (row 0, then row 1, etc.)
 * @param values: Array of 16 double values
 * @return: 4x4 matrix with the specified values
 */
t_matrix4
matrix4_from_array (double values[16])
{
    t_matrix4 matrix;
    int index;

    int i, j;
    i = 0;
    index = 0;
    while (i < 4)
        {
            j = 0;
            while (j < 4)
                {
                    matrix.m[i][j] = values[index];
                    index++;
                    j++;
                }
            i++;
        }
    return (matrix);
}

/**
 * Prints a 4x4 matrix in a readable format
 * @param matrix: The 4x4 matrix to print
 */
void
matrix4_print (t_matrix4 matrix)
{
    int i, j;
    printf ("4x4 Matrix:\n");
    i = 0;
    while (i < 4)
        {
            printf ("| ");
            j = 0;
            while (j < 4)
                {
                    printf ("%8.2f ", matrix.m[i][j]);
                    j++;
                }
            printf ("|\n");
            i++;
        }
    printf ("\n");
}

/**
 * Compares two 4x4 matrices for equality using floating point epsilon
 * @param a: First 4x4 matrix
 * @param b: Second 4x4 matrix
 * @return: true if matrices are equal, false otherwise
 */
bool
matrix4_equal (t_matrix4 a, t_matrix4 b)
{
    int i, j;
    i = 0;
    while (i < 4)
        {
            j = 0;
            while (j < 4)
                {
                    if (!ft_fequal (a.m[i][j], b.m[i][j]))
                        return (false);
                    j++;
                }
            i++;
        }
    return (true);
}

/**
 * Multiplies two 4x4 matrices using the standard matrix multiplication
 * algorithm Following Ray Tracer Challenge: Mrc = Ar0*B0c + Ar1*B1c + Ar2*B2c +
 * Ar3*B3c This is equivalent to computing the dot product of each row-column
 * combination
 * @param a: First 4x4 matrix (left operand)
 * @param b: Second 4x4 matrix (right operand)
 * @return: Result of A * B as a new 4x4 matrix
 */
t_matrix4
matrix4_multiply (t_matrix4 a, t_matrix4 b)
{
    t_matrix4 result;

    int row, col;
    row = 0;
    while (row < 4)
        {
            col = 0;
            while (col < 4)
                {
                    // Mrc = Ar0*B0c + Ar1*B1c + Ar2*B2c + Ar3*B3c
                    result.m[row][col] = a.m[row][0] * b.m[0][col]
                                         + a.m[row][1] * b.m[1][col]
                                         + a.m[row][2] * b.m[2][col]
                                         + a.m[row][3] * b.m[3][col];
                    col++;
                }
            row++;
        }
    return (result);
}

/**
 * Multiplies a 4x4 matrix by a tuple (point or vector)
 * @param m: The 4x4 matrix
 * @param t: The tuple to multiply
 * @return: Resulting tuple after transformation
 */
t_tuple
matrix4_multiply_tuple (t_matrix4 m, t_tuple t)
{
    t_tuple result;

    result.x
        = m.m[0][0] * t.x + m.m[0][1] * t.y + m.m[0][2] * t.z + m.m[0][3] * t.w;
    result.y
        = m.m[1][0] * t.x + m.m[1][1] * t.y + m.m[1][2] * t.z + m.m[1][3] * t.w;
    result.z
        = m.m[2][0] * t.x + m.m[2][1] * t.y + m.m[2][2] * t.z + m.m[2][3] * t.w;
    result.w
        = m.m[3][0] * t.x + m.m[3][1] * t.y + m.m[3][2] * t.z + m.m[3][3] * t.w;
    return (result);
}

/**
 * Transposes a matrix in-place by modifying the original matrix
 * @param m: Pointer to the matrix to transpose
 */
void
transpose_matrix4 (t_matrix4 *m)
{
    t_matrix4 transposed;

    int i, j;
    i = 0;
    while (i < 4)
        {
            j = 0;
            while (j < 4)
                {
                    transposed.m[i][j] = m->m[j][i];
                    j++;
                }
            i++;
        }
    *m = transposed;
}

/**
 * Returns the transpose of a 4x4 matrix (functional version)
 * Following Ray Tracer Challenge: transpose turns rows into columns and columns
 * into rows
 * @param matrix: The 4x4 matrix to transpose
 * @return: New transposed 4x4 matrix
 */
t_matrix4
matrix4_transpose (t_matrix4 matrix)
{
    t_matrix4 result;

    int row, col;
    row = 0;
    while (row < 4)
        {
            col = 0;
            while (col < 4)
                {
                    // Transpose: result[row][col] = original[col][row]
                    result.m[row][col] = matrix.m[col][row];
                    col++;
                }
            row++;
        }
    return (result);
}

/**
 * Extracts a 3x3 submatrix from a 4x4 matrix by removing specified row and
 * column
 * @param m: The 4x4 matrix
 * @param row: Row index to remove (0-3)
 * @param col: Column index to remove (0-3)
 * @return: 3x3 submatrix
 */
t_matrix3
submatrix4 (t_matrix4 m, int row, int col)
{
    t_matrix3 result;

    int r, c;
    r = 0;
    while (r < 3)
        {
            c = 0;
            while (c < 3)
                {
                    result.m[r][c] = m.m[r + (r >= row)][c + (c >= col)];
                    c++;
                }
            r++;
        }
    return (result);
}

/**
 * Calculates the minor of a 4x4 matrix (determinant of 3x3 submatrix)
 * @param m: The 4x4 matrix
 * @param row: Row to remove for submatrix
 * @param col: Column to remove for submatrix
 * @return: Minor value (determinant of 3x3 submatrix)
 */
float
minor4 (t_matrix4 m, int row, int col)
{
    t_matrix3 submatrix;

    submatrix = submatrix4 (m, row, col);
    return (matrix3_determinant (submatrix));
}

/**
 * Calculates the cofactor of a 4x4 matrix
 * Cofactor = minor * (-1)^(row + col)
 * @param m: The 4x4 matrix
 * @param row: Row index
 * @param col: Column index
 * @return: Cofactor value
 */
float
cofactor4 (t_matrix4 m, int row, int col)
{
    float minor;

    minor = minor4 (m, row, col);
    // Apply sign based on position: (-1)^(row + col)
    if ((row + col) % 2 == 1)
        return (-minor);
    return (minor);
}

/**
 * Calculates the determinant of a 4x4 matrix using cofactor expansion
 * Following Ray Tracer Challenge: expand along first row
 * det = M[0,0]*cofactor(0,0) + M[0,1]*cofactor(0,1) + M[0,2]*cofactor(0,2) +
 * M[0,3]*cofactor(0,3)
 * @param m: The 4x4 matrix
 * @return: Determinant value
 */
float
matrix4_determinant (t_matrix4 m)
{
    float det;
    int col;

    det = 0.0;
    col = 0;
    // Expand along the first row
    while (col < 4)
        {
            det += m.m[0][col] * cofactor4 (m, 0, col);
            col++;
        }
    return (det);
}

/**
 * Checks if a 4x4 matrix is invertible
 * A matrix is invertible if its determinant is not zero
 * @param m: The 4x4 matrix to check
 * @return: true if invertible, false if not invertible (determinant = 0)
 */
bool
isinvertible (t_matrix4 m)
{
    float deter;

    deter = matrix4_determinant (m);
    return (deter != 0.0);
}

/**
 * Calculates the inverse of a 4x4 matrix using cofactor expansion
 * Following Ray Tracer Challenge algorithm:
 * 1. Calculate cofactor matrix
 * 2. Transpose it (by swapping row,col to col,row)
 * 3. Divide each element by the determinant
 * @param m: The 4x4 matrix to invert
 * @return: Inverse matrix, or zero matrix if not invertible
 */
t_matrix4
inverse (t_matrix4 m)
{
    t_matrix4 result;
    float determinant;
    float c;

    int row, col;
    // Initialize result matrix to zero
    result = matrix4_create ();
    // Check if matrix is invertible
    if (!isinvertible (m))
        {
            // Return zero matrix for non-invertible matrices
            return (result);
        }
    // Calculate determinant once to avoid repeated computation
    determinant = matrix4_determinant (m);
    // Calculate inverse using cofactor method with transpose
    row = 0;
    while (row < 4)
        {
            col = 0;
            while (col < 4)
                {
                    // Calculate cofactor
                    c = cofactor4 (m, row, col);
                    // Note: [col][row] instead of [row][col] accomplishes
                    // transpose
                    result.m[col][row] = c / determinant;
                    col++;
                }
            row++;
        }
    return (result);
}
