/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaeed < tsaeed@student.42amman.com >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 21:38:20 by tsaeed            #+#    #+#             */
/*   Updated: 2025/10/13 11:29:29 by tsaeed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef M_PI
	#define M_PI 3.14159265358979323846
#endif

#include "miniRT.h"
#include <math.h>

void	key_hook(mlx_key_data_t keydata, void *param)
{
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window((mlx_t *)param);
}

float	**creatmatrix(int rows, int cols)
{
	float	**matrix;
	int		i;

	matrix = malloc(rows * sizeof(float *));
	if (!matrix)
		return (NULL);
	while (i < cols)
	{
		matrix[i] = malloc(sizeof(float *) * cols);
		if (!matrix[i])
		{
			while (--i >= 0)
				free(matrix[i]);
			free(matrix);
			return (NULL);
		}
		i++;
	}
	return (matrix);
}

void	printmatrix(float **matrix, int rows, int cols)
{
	int	i;
	int	j;

	i = 0;
	while (i < rows)
	{
		j = 0;
		while (j < cols)
		{
			printf("%.2f ", matrix[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
}

float	**fillmatrix(float **matrix, int rows, int cols, float value)
{
	int	i;
	int	j;

	i = 0;
	while (i < rows)
	{
		j = 0;
		while (j < cols)
		{
			matrix[i][j] = value;
			j++;
		}
		i++;
	}
	return (matrix);
}

int	main(void)
{
	t_canvas *canves;
	int canves_x;
	int canves_y;
	int center_x = 375;
	int center_y = 375;
	int radius = 375;
	int i;
	t_tuple staritng_point;
	t_tuple rotated_point;
	float angle ;
	t_matrix4 rotation;
	t_color color1;

	color1 = color(1,0,0);

	canves = canvas_create(750,750,"Clock");
	staritng_point = point(0 , -radius, 0);

	i = 0;
	while(i < 12)
	{
		angle = i  * (M_PI / 6);
		rotation = rotation_z(angle);
		rotated_point = matrix4_multiply_tuple(rotation,staritng_point);

		canves_x = (int)(rotated_point.x + center_x);
		canves_y = (int)(-rotated_point.y + center_y);

		canvas_write_pixel(canves,canves_x,canves_y,color1);
		i++;
	}

	// Set up key handler for closing window
	mlx_key_hook(canves->mlx, key_hook, canves->mlx);
	// Display the canvas
	canvas_render(canves);
	// Clean up
	canvas_destroy(canves);
	printf("Program completed successfully!\n");
	return (0);
}
