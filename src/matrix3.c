/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaeed < tsaeed@student.42amman.com >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 23:50:00 by tsaeed            #+#    #+#             */
/*   Updated: 2025/10/10 00:15:53 by tsaeed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/**
 * Creates a 3x3 matrix initialized to zero
 * @return: Zero-initialized 3x3 matrix
 */
t_matrix3	matrix3_create(void)
{
	t_matrix3	matrix;

	int i, j;
	i = 0;
	while (i < 3)
	{
		j = 0;
		while (j < 3)
		{
			matrix.m[i][j] = 0.0;
			j++;
		}
		i++;
	}
	return (matrix);
}

/**
 * Creates a 3x3 matrix from an array of values
 * Values should be provided in row-major order
 * @param values: Array of 9 double values
 * @return: 3x3 matrix with the specified values
 */
t_matrix3	matrix3_from_array(double values[9])
{
	t_matrix3	matrix;
	int			index;

	int i, j;
	i = 0;
	index = 0;
	while (i < 3)
	{
		j = 0;
		while (j < 3)
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
 * Prints a 3x3 matrix in a readable format
 * @param matrix: The 3x3 matrix to print
 */
void	matrix3_print(t_matrix3 matrix)
{
	int i, j;
	printf("3x3 Matrix:\n");
	i = 0;
	while (i < 3)
	{
		printf("| ");
		j = 0;
		while (j < 3)
		{
			printf("%8.2f ", matrix.m[i][j]);
			j++;
		}
		printf("|\n");
		i++;
	}
	printf("\n");
}

/**
 * Compares two 3x3 matrices for equality using floating point epsilon
 * @param a: First 3x3 matrix
 * @param b: Second 3x3 matrix
 * @return: true if matrices are equal, false otherwise
 */
bool	matrix3_equal(t_matrix3 a, t_matrix3 b)
{
	int i, j;
	i = 0;
	while (i < 3)
	{
		j = 0;
		while (j < 3)
		{
			if (!ft_fequal(a.m[i][j], b.m[i][j]))
				return (false);
			j++;
		}
		i++;
	}
	return (true);
}

/**
 * Extracts a 2x2 submatrix from a 3x3 matrix by removing specified row and
 * column
 * @param m: The 3x3 matrix
 * @param row: Row index to remove (0-2)
 * @param col: Column index to remove (0-2)
 * @return: 2x2 submatrix
 */
t_matrix2	submatrix3(t_matrix3 m, int row, int col)
{
	t_matrix2	result;

	int r, c;
	r = 0;
	while (r < 2)
	{
		c = 0;
		while (c < 2)
		{
			result.m[r][c] = m.m[r + (r >= row)][c + (c >= col)];
			c++;
		}
		r++;
	}
	return (result);
}

/**
 * Calculates the minor of a 3x3 matrix (determinant of 2x2 submatrix)
 * @param m: The 3x3 matrix
 * @param row: Row to remove for submatrix
 * @param col: Column to remove for submatrix
 * @return: Minor value (determinant of 2x2 submatrix)
 */
float	minor3(t_matrix3 m, int row, int col)
{
	t_matrix2	result;
	float		minor;

	result = submatrix3(m, row, col);
	minor = matrix2_determinant(result);
	return (minor);
}

/**
 * Calculates the cofactor of a 3x3 matrix
 * Cofactor = minor * (-1)^(row + col)
 * If row + col is odd, negate the minor
 * @param m: The 3x3 matrix
 * @param row: Row index
 * @param col: Column index
 * @return: Cofactor value
 */
float	cofactor(t_matrix3 m, int row, int col)
{
	float	minor;

	minor = minor3(m, row, col);
	// Apply sign based on position: (-1)^(row + col)
	if ((row + col) % 2 == 1)
		return (-minor);
	return (minor);
}

/**
 * Calculates the determinant of a 3x3 matrix using cofactor expansion
 * Following Ray Tracer Challenge: expand along first row
 * det = M[0,0]*cofactor(0,0) + M[0,1]*cofactor(0,1) + M[0,2]*cofactor(0,2)
 * @param m: The 3x3 matrix
 * @return: Determinant value
 */
float	matrix3_determinant(t_matrix3 m)
{
	float	det;
	int		col;

	det = 0.0;
	col = 0;
	// Expand along the first row
	while (col < 3)
	{
		det += m.m[0][col] * cofactor(m, 0, col);
		col++;
	}
	return (det);
}
