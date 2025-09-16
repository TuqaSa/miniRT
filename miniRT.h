/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaeed < tsaeed@student.42amman.com >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 22:00:23 by tsaeed            #+#    #+#             */
/*   Updated: 2025/09/16 23:02:14 by tsaeed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
#define MINIRT_H

#include "MLX42/include/MLX42/MLX42.h"
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define EPSILON 1e-5

typedef struct s_tuple
{
    float x;
    float y;
    float z;
    float w;
} t_tuple;

typedef struct s_projectile
{
    t_tuple position;
    t_tuple velocity;
} t_projectile;

typedef struct s_environment
{
    t_tuple gravity;
    t_tuple wind;
} t_environment;

typedef struct s_color
{
    float r;
    float g;
    float b;
} t_color;

typedef struct s_canvas
{
    int width;
    int height;
    mlx_t *mlx;
    mlx_image_t *image;
    t_color **pixels;
} t_canvas;

typedef struct s_matrix
{
    int rows;
    int cols;
    float **data;
} t_matrix;

// Function prototypes
// Tuple operations
t_tuple point (float x, float y, float z);
t_tuple vector (float x, float y, float z);
void print_value (t_tuple p);
bool ft_fequal (float a, float b);
bool ft_tequal (t_tuple a, t_tuple b);

// Tuple arithmetic
t_tuple ft_addtuple (t_tuple a, t_tuple b);
t_tuple ft_subtuple (t_tuple a, t_tuple b);
t_tuple ft_negtuple (t_tuple a);
t_tuple ft_multuple (t_tuple a, float b);
t_tuple ft_divtuple (t_tuple a, float b);

// Vector operations
float magnitude (t_tuple v);
t_tuple normalize (t_tuple v);
float dot (t_tuple a, t_tuple b);
t_tuple cross (t_tuple a, t_tuple b);
t_tuple reflect (t_tuple incident, t_tuple normal);

// Simulation functions
t_projectile tick (t_environment env, t_projectile proj);
t_projectile create_projectile (t_tuple position, t_tuple velocity);
t_environment create_environment (t_tuple gravity, t_tuple wind);
void print_projectile (t_projectile proj);
void print_environment (t_environment env);

// Color operations
t_color color (float r, float g, float b);
t_color addcolor (t_color a, t_color b);
t_color subcolor (t_color a, t_color b);
t_color multcolor (t_color a, float b);
t_color hadamard (t_color a, t_color b);

// Canvas operations
t_canvas *canvas_create (int width, int height, const char *title);
void canvas_destroy (t_canvas *canvas);
void canvas_write_pixel (t_canvas *canvas, int x, int y, t_color color);
t_color canvas_pixel_at (t_canvas *canvas, int x, int y);
uint32_t color_to_rgba (t_color color);
t_color rgba_to_color (uint32_t rgba);
void canvas_render (t_canvas *canvas);
void canvas_clear (t_canvas *canvas, t_color color);

// Matrix operations
t_matrix *matrix_create (int rows, int cols);
void matrix_destroy (t_matrix *matrix);
void matrix_set (t_matrix *matrix, int row, int col, float value);
float matrix_get (t_matrix *matrix, int row, int col);
t_matrix *matrix_from_array (int rows, int cols, float values[]);

#endif
