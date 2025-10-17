/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaeed < tsaeed@student.42amman.com >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 21:38:20 by tsaeed            #+#    #+#             */
/*   Updated: 2025/10/17 20:31:53 by tsaeed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#include "miniRT.h"
#include <math.h>

void
key_hook (mlx_key_data_t keydata, void *param)
{
    if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
        mlx_close_window ((mlx_t *)param);
}

float **
creatmatrix (int rows, int cols)
{
    float **matrix;
    int i;

    matrix = malloc (rows * sizeof (float *));
    if (!matrix)
        return (NULL);
    while (i < cols)
        {
            matrix[i] = malloc (sizeof (float *) * cols);
            if (!matrix[i])
                {
                    while (--i >= 0)
                        free (matrix[i]);
                    free (matrix);
                    return (NULL);
                }
            i++;
        }
    return (matrix);
}

void
printmatrix (float **matrix, int rows, int cols)
{
    int i;
    int j;

    i = 0;
    while (i < rows)
        {
            j = 0;
            while (j < cols)
                {
                    printf ("%.2f ", matrix[i][j]);
                    j++;
                }
            printf ("\n");
            i++;
        }
}

float **
fillmatrix (float **matrix, int rows, int cols, float value)
{
    int i;
    int j;

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

int
main (void)
{
    // Scene geometry
    const int canvas_width = 400;
    const int canvas_height = 400;
    const float wall_z = 10.0f;
    const float wall_size = 7.0f;
    const float pixel_size = wall_size / canvas_width;

    // Camera and sphere
    t_tuple ray_origin = point (0, 0, -7);
    t_sphere sphere_obj = sphere (); // Unit sphere at origin

    // Optional transformations - try these one at a time!
     set_transform(&sphere_obj, scaling(1, 0.5, 1));     // Ellipse
    // set_transform(&sphere_obj, scaling(0.5, 1, 1));     // Narrow ellipse
    // set_transform(&sphere_obj, translation(1, 0, 0));   // Move right
    // set_transform(&sphere_obj, rotation_z(M_PI / 4));   // Rotate

    // Colors
    t_color red = color (1, 1, 0);
    t_color black = color (0, 0, 0);

    // Create canvas
    t_canvas *canvas
        = canvas_create (canvas_width, canvas_height, "Sphere Silhouette");

    printf ("Rendering sphere silhouette...\n");
    printf ("Canvas: %dx%d pixels\n", canvas_width, canvas_height);
    printf ("Wall distance: %.1f units\n", wall_z);
    printf ("Wall size: %.1f units\n", wall_size);
    printf ("Pixel size: %.4f units\n", pixel_size);

    // Ray casting loop
    for (int y = 0; y < canvas_height; y++)
        {
            // Show progress
            if (y % 50 == 0)
                {
                    printf ("Rendering row %d/%d...\n", y, canvas_height);
                }

            // Convert canvas Y to world Y coordinate
            float world_y = wall_size / 2 - pixel_size * y;

            for (int x = 0; x < canvas_width; x++)
                {
                    // Convert canvas X to world X coordinate
                    float world_x = -wall_size / 2 + pixel_size * x;

                    // Point on the wall that this pixel represents
                    t_tuple wall_point = point (world_x, world_y, wall_z);

                    // Create ray from camera to wall point
                    t_tuple ray_direction
                        = normalize (ft_subtuple (wall_point, ray_origin));
                    t_ray ray = create_ray (ray_origin, ray_direction);

                    // Test intersection with sphere
                    t_intersections xs = intersect (sphere_obj, ray);
                    t_intersection hit_result;

                    if (hit (xs, &hit_result))
                        {
                            // Ray hit the sphere - color it red
                            canvas_write_pixel (canvas, x, y, red);
                        }
                    else
                        {
                            // Ray missed - color it black
                            canvas_write_pixel (canvas, x, y, black);
                        }
                }
        }

    printf ("Rendering complete! Displaying result...\n");
    printf ("You should see a red circle on black background.\n");
    printf ("Press ESC or close window to exit.\n");

    // Set up key handler for closing window
    mlx_key_hook (canvas->mlx, key_hook, canvas->mlx);

    // Display the canvas
    canvas_render (canvas);

    // Clean up
    canvas_destroy (canvas);

    printf ("Program completed successfully!\n");
    return (0);
}
