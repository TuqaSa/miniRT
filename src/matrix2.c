/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaeed < tsaeed@student.42amman.com >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 23:50:00 by tsaeed            #+#    #+#             */
/*   Updated: 2025/10/10 00:15:50 by tsaeed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/**
 * Creates a 2x2 matrix initialized to zero
 * @return: Zero-initialized 2x2 matrix
 */
t_matrix2	matrix2_create(void)
{
	t_matrix2	matrix;

	int i, j;
	i = 0;
	while (i < 2)
	{
		j = 0;
		while (j < 2)
		{
			matrix.m[i][j] = 0.0;
			j++;
		}
		i++;
	}
	return (matrix);
}

/**
 * Creates a 2x2 matrix from an array of values
 * Values should be provided in row-major order
 * @param values: Array of 4 double values
 * @return: 2x2 matrix with the specified values
 */
t_matrix2	matrix2_from_array(double values[4])
{
	t_matrix2	matrix;
	int			index;

	int i, j;
	i = 0;
	index = 0;
	while (i < 2)
	{
		j = 0;
		while (j < 2)
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
 * Prints a 2x2 matrix in a readable format
 * @param matrix: The 2x2 matrix to print
 */
void	matrix2_print(t_matrix2 matrix)
{
	int i, j;
	printf("2x2 Matrix:\n");
	i = 0;
	while (i < 2)
	{
		printf("| ");
		j = 0;
		while (j < 2)
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
 * Compares two 2x2 matrices for equality using floating point epsilon
 * @param a: First 2x2 matrix
 * @param b: Second 2x2 matrix
 * @return: true if matrices are equal, false otherwise
 */
bool	matrix2_equal(t_matrix2 a, t_matrix2 b)
{
	int i, j;
	i = 0;
	while (i < 2)
	{
		j = 0;
		while (j < 2)
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
 * Calculates the determinant of a 2x2 matrix
 * Formula: det = a*d - b*c where matrix is |a b|
 *                                            |c d|
 * @param m: The 2x2 matrix
 * @return: Determinant value
 */
float	matrix2_determinant(t_matrix2 m)
{
	return (m.m[0][0] * m.m[1][1] - m.m[0][1] * m.m[1][0]);
}
