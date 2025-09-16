/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaeed < tsaeed@student.42amman.com >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 21:38:20 by tsaeed            #+#    #+#             */
/*   Updated: 2025/09/16 19:54:30 by tsaeed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include <math.h>

void
key_hook (mlx_key_data_t keydata, void *param)
{
    if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
        mlx_close_window ((mlx_t *)param);
}

float ** creatmatrix (int rows, int cols)
{
    float ** matrix;
    int i;

    matrix = malloc(rows * sizeof(float *));
    if(!matrix)
        return NULL;
    while(i < cols)
    {
        matrix[i] = malloc(sizeof(float *) * cols);
        if(!matrix[i])
        {
            while(--i >= 0)
                free(matrix[i]);
            free(matrix);
            return NULL;
        }
        i++;
    }
    return matrix;
}

void printmatrix (float ** matrix, int rows, int cols)
{
    int i;
    int j;

    i = 0;
    while(i < rows)
    {
        j = 0;
        while(j < cols)
        {
            printf("%.2f ", matrix[i][j]);
            j++;
        }
        printf("\n");
        i++;


    }
}

float ** fillmatrix (float ** matrix, int rows, int cols , float value)
{
    int i;
    int j;

    i = 0;
    while(i < rows)
    {
        j = 0;
        while(j < cols)
        {
            matrix[i][j] = value;
            j++;
        }
        i++;
    }
    return matrix;
}


int
main (void)
{

    float **matrix = creatmatrix(3, 3);
    if (!matrix)
    {
        printf("Error: Failed to create matrix\n");
        return (1);
    }
    fillmatrix(matrix, 3, 3, 0.0);
    printmatrix(matrix, 3, 3);

    t_projectile proj;
    t_environment env;
    t_canvas *canvas;
    t_color projectile_color;
    int tick_count;
    int canvas_x, canvas_y;

    printf ("=== Projectile Trajectory Visualization ===\n");

    // Create canvas with book's recommended dimensions (900x550)
    canvas = canvas_create (900, 550,
                            "Projectile Trajectory - Ray Tracing Challenge");
    if (!canvas)
        {
            printf ("Error: Failed to create canvas\n");
            return (1);
        }

    // Clear canvas with black background
    canvas_clear (canvas, color (0, 0, 0));

    // Set up projectile with book's recommended parameters
    // start = point(0, 1, 0)
    // velocity = normalize(vector(1, 1.8, 0)) * 11.25
    t_tuple start_pos = point (0, 1, 0);
    t_tuple velocity_dir = normalize (vector (1, 1.8, 0));
    t_tuple velocity = ft_multuple (velocity_dir, 11.25);
    proj = create_projectile (start_pos, velocity);

    // Environment with book's recommended parameters
    // gravity = vector(0, -0.1, 0)
    // wind = vector(-0.01, 0, 0)
    env = create_environment (vector (0, -0.1, 0), vector (-0.01, 0, 0));

    // Color for the projectile trail (bright red)
    projectile_color = color (1.0, 0.0, 0.0);

    printf ("Initial setup:\n");
    print_projectile (proj);
    printf ("Velocity magnitude: %.3f\n", magnitude (proj.velocity));
    print_environment (env);
    printf ("Canvas size: %dx%d\n", canvas->width, canvas->height);
    printf ("\nSimulating trajectory...\n");

    tick_count = 0;

    // Simulate and plot trajectory
    while (proj.position.y > 0 && tick_count < 2000)
        {
            // Convert world coordinates to canvas coordinates
            // World: x increases right, y increases up
            // Canvas: x increases right, y increases down (y=0 at top)

            // Convert float coordinates to integers
            canvas_x = (int)proj.position.x;
            canvas_y
                = canvas->height - (int)proj.position.y; // Flip Y coordinate

            // Check bounds before plotting
            if (canvas_x >= 0 && canvas_x < canvas->width && canvas_y >= 0
                && canvas_y < canvas->height)
                {
                    canvas_write_pixel (canvas, canvas_x, canvas_y,
                                        projectile_color);
                }

            // Print progress every 50 ticks
            if (tick_count % 50 == 0)
                {
                    printf ("Tick %4d: World(%.2f, %.2f) -> Canvas(%d, %d)\n",
                            tick_count, proj.position.x, proj.position.y,
                            canvas_x, canvas_y);
                }

            // Advance simulation
            proj = tick (env, proj);
            tick_count++;
        }

    printf ("\nSimulation complete!\n");
    printf ("Total ticks: %d\n", tick_count);
    printf ("Final position: ");
    print_value (proj.position);
    printf ("Trajectory plotted on canvas.\n");
    printf ("Press ESC to close the window.\n");

    // Set up key handler for closing window
    mlx_key_hook (canvas->mlx, key_hook, canvas->mlx);

    // Display the canvas
    canvas_render (canvas);

    // Clean up
    canvas_destroy (canvas);
    printf ("Program completed successfully!\n");

    return (0);
}
