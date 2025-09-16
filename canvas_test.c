// /* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   canvas_test.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaeed < tsaeed@student.42amman.com >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 22:25:00 by tsaeed            #+#    #+#             */
/*   Updated: 2025/09/15 22:40:43 by tsaeed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	key_hook(mlx_key_data_t keydata, void *param)
{
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window((mlx_t *)param);
}

int	main(void)
{
	t_canvas	*canvas;
	float		intensity;
	t_color		gradient;
	t_color		test_pixel;

	t_color red, green, blue, white;
	int x, y;
	// Create a 400x300 canvas
	canvas = canvas_create(400, 300, "Canvas Test - Ray Tracing Setup");
	if (!canvas)
	{
		printf("Error: Failed to create canvas\n");
		return (1);
	}
	// Define some colors
	red = color(1.0, 0.0, 0.0);
	green = color(0.0, 1.0, 0.0);
	blue = color(0.0, 0.0, 1.0);
	white = color(1.0, 1.0, 1.0);
	printf("=== Canvas Test ===\n");
	printf("Drawing test patterns...\n");
	// Test 1: Draw colored quadrants
	// Top-left: Red
	for (y = 0; y < 150; y++)
	{
		for (x = 0; x < 200; x++)
		{
			canvas_write_pixel(canvas, x, y, red);
		}
	}
	// Top-right: Green
	for (y = 0; y < 150; y++)
	{
		for (x = 200; x < 400; x++)
		{
			canvas_write_pixel(canvas, x, y, green);
		}
	}
	// Bottom-left: Blue
	for (y = 150; y < 300; y++)
	{
		for (x = 0; x < 200; x++)
		{
			canvas_write_pixel(canvas, x, y, blue);
		}
	}
	// Bottom-right: White
	for (y = 150; y < 300; y++)
	{
		for (x = 200; x < 400; x++)
		{
			canvas_write_pixel(canvas, x, y, white);
		}
	}
	// Test 2: Draw a simple pattern in the center
	// Draw a small circle-like pattern
	for (y = 140; y < 160; y++)
	{
		for (x = 190; x < 210; x++)
		{
			// Create a gradient effect
			intensity = 1.0f - (float)((x - 200) * (x - 200) + (y - 150) * (y
						- 150)) / 200.0f;
			if (intensity > 0)
			{
				gradient = color(intensity, intensity * 0.5f, intensity * 0.8f);
				canvas_write_pixel(canvas, x, y, gradient);
			}
		}
	}
	printf("Test patterns drawn successfully!\n");
	printf("Canvas dimensions: %dx%d\n", canvas->width, canvas->height);
	printf("Press ESC to close the window.\n");
	// Test reading pixels
	test_pixel = canvas_pixel_at(canvas, 100, 75);
	printf("Pixel at (100, 75) - R: %.2f, G: %.2f, B: %.2f\n", test_pixel.r,
		test_pixel.g, test_pixel.b);
	// Set up key handler
	mlx_key_hook(canvas->mlx, key_hook, canvas->mlx);
	// Render the canvas (this will start the MLX loop)
	canvas_render(canvas);
	// Clean up
	canvas_destroy(canvas);
	printf("Canvas test completed successfully!\n");
	return (0);
}
