/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   canvas.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaeed < tsaeed@student.42amman.com >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 22:20:00 by tsaeed            #+#    #+#             */
/*   Updated: 2025/09/15 22:40:43 by tsaeed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/**
 * Creates a new canvas with MLX42 window and image
 * @param width: Canvas width in pixels
 * @param height: Canvas height in pixels
 * @param title: Window title
 * @return: Pointer to canvas structure or NULL on failure
 */
t_canvas	*canvas_create(int width, int height, const char *title)
{
	t_canvas	*canvas;
	int			y;

	canvas = malloc(sizeof(t_canvas));
	if (!canvas)
		return (NULL);
	// Initialize MLX42 window
	canvas->mlx = mlx_init(width, height, title, true);
	if (!canvas->mlx)
	{
		free(canvas);
		return (NULL);
	}
	// Create MLX42 image buffer
	canvas->image = mlx_new_image(canvas->mlx, width, height);
	if (!canvas->image)
	{
		mlx_terminate(canvas->mlx);
		free(canvas);
		return (NULL);
	}
	// Set canvas dimensions
	canvas->width = width;
	canvas->height = height;
	// Allocate 2D pixel array for color storage
	canvas->pixels = malloc(sizeof(t_color *) * height);
	if (!canvas->pixels)
	{
		mlx_delete_image(canvas->mlx, canvas->image);
		mlx_terminate(canvas->mlx);
		free(canvas);
		return (NULL);
	}
	y = 0;
	while (y < height)
	{
		canvas->pixels[y] = malloc(sizeof(t_color) * width);
		if (!canvas->pixels[y])
		{
			while (--y >= 0)
				free(canvas->pixels[y]);
			free(canvas->pixels);
			mlx_delete_image(canvas->mlx, canvas->image);
			mlx_terminate(canvas->mlx);
			free(canvas);
			return (NULL);
		}
		y++;
	}
	// Initialize all pixels to black
	canvas_clear(canvas, color(0, 0, 0));
	return (canvas);
}

/**
 * Destroys the canvas and frees all resources
 * @param canvas: Canvas to destroy
 */
void	canvas_destroy(t_canvas *canvas)
{
	int	y;

	if (!canvas)
		return ;
	// Free pixel array
	if (canvas->pixels)
	{
		y = 0;
		while (y < canvas->height)
		{
			free(canvas->pixels[y]);
			y++;
		}
		free(canvas->pixels);
	}
	// Clean up MLX42 resources
	if (canvas->image)
		mlx_delete_image(canvas->mlx, canvas->image);
	if (canvas->mlx)
		mlx_terminate(canvas->mlx);
	free(canvas);
}

/**
 * Writes a color to a specific pixel on the canvas
 * @param canvas: Target canvas
 * @param x: X coordinate (0 to width-1)
 * @param y: Y coordinate (0 to height-1)
 * @param color: Color to write
 */
void	canvas_write_pixel(t_canvas *canvas, int x, int y, t_color color)
{
	uint32_t	rgba;

	if (!canvas || x < 0 || x >= canvas->width || y < 0 || y >= canvas->height)
		return ;
	// Store color in our pixel array
	canvas->pixels[y][x] = color;
	// Convert color to RGBA and put to MLX42 image
	rgba = color_to_rgba(color);
	mlx_put_pixel(canvas->image, x, y, rgba);
}

/**
 * Gets the color of a pixel at specified coordinates
 * @param canvas: Source canvas
 * @param x: X coordinate
 * @param y: Y coordinate
 * @return: Color at the specified pixel
 */
t_color	canvas_pixel_at(t_canvas *canvas, int x, int y)
{
	if (!canvas || x < 0 || x >= canvas->width || y < 0 || y >= canvas->height)
		return (color(0, 0, 0));
	return (canvas->pixels[y][x]);
}

/**
 * Converts a color (0.0-1.0 range) to RGBA format for MLX42
 * @param color: Color to convert
 * @return: RGBA value in format expected by MLX42
 */
uint32_t	color_to_rgba(t_color color)
{
	int r, g, b;
	// Clamp values to 0.0-1.0 range and convert to 0-255
	r = (int)(fmaxf(0.0f, fminf(1.0f, color.r)) * 255);
	g = (int)(fmaxf(0.0f, fminf(1.0f, color.g)) * 255);
	b = (int)(fmaxf(0.0f, fminf(1.0f, color.b)) * 255);
	// MLX42 expects RGBA format: (R << 24) | (G << 16) | (B << 8) | A
	return ((r << 24) | (g << 16) | (b << 8) | 255);
}

/**
 * Converts RGBA format back to color (for debugging/reading)
 * @param rgba: RGBA value
 * @return: Color structure
 */
t_color	rgba_to_color(uint32_t rgba)
{
	float r, g, b;
	r = ((rgba >> 24) & 0xFF) / 255.0f;
	g = ((rgba >> 16) & 0xFF) / 255.0f;
	b = ((rgba >> 8) & 0xFF) / 255.0f;
	return (color(r, g, b));
}

/**
 * Renders the canvas to the screen and starts the MLX loop
 * @param canvas: Canvas to render
 */
void	canvas_render(t_canvas *canvas)
{
	if (!canvas)
		return ;
	// Display the image in the window
	if (mlx_image_to_window(canvas->mlx, canvas->image, 0, 0) == -1)
	{
		printf("Error: Failed to display canvas\n");
		return ;
	}
	// Start the MLX event loop
	mlx_loop(canvas->mlx);
}

/**
 * Clears the entire canvas with a specified color
 * @param canvas: Canvas to clear
 * @param color: Color to fill the canvas with
 */
void	canvas_clear(t_canvas *canvas, t_color clear_color)
{
	int x, y;
	if (!canvas)
		return ;
	y = 0;
	while (y < canvas->height)
	{
		x = 0;
		while (x < canvas->width)
		{
			canvas_write_pixel(canvas, x, y, clear_color);
			x++;
		}
		y++;
	}
}
