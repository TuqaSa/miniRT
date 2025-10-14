/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaeed < tsaeed@student.42amman.com >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 22:00:23 by tsaeed            #+#    #+#             */
/*   Updated: 2025/10/14 13:26:24 by tsaeed           ###   ########.fr       */
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

// Matrix structures - Fixed-size arrays for performance
typedef struct s_matrix4
{
    double m[4][4];
} t_matrix4;

typedef struct s_matrix3
{
    double m[3][3];
} t_matrix3;

typedef struct s_matrix2
{
    double m[2][2];
} t_matrix2;

typedef struct s_shear
{
    float xy;
    float xz;
    float yx;
    float yz;
    float zx;
    float zy;
} t_shear;

typedef struct s_ray
{
    t_tuple origin;
    t_tuple direction;
} t_ray;

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
t_matrix4 matrix4_create (void);
t_matrix4 matrix4_identity (void);
t_matrix3 matrix3_create (void);
t_matrix2 matrix2_create (void);
t_matrix4 matrix4_from_array (double values[16]);
t_matrix3 matrix3_from_array (double values[9]);
t_matrix2 matrix2_from_array (double values[4]);
void matrix4_print (t_matrix4 matrix);
void matrix3_print (t_matrix3 matrix);
void matrix2_print (t_matrix2 matrix);
bool matrix4_equal (t_matrix4 a, t_matrix4 b);
bool matrix3_equal (t_matrix3 a, t_matrix3 b);
bool matrix2_equal (t_matrix2 a, t_matrix2 b);
t_matrix4 matrix4_multiply (t_matrix4 a, t_matrix4 b);
t_tuple matrix4_multiply_tuple (t_matrix4 m, t_tuple t);
void transpose_matrix4 (t_matrix4 *m);
t_matrix4 matrix4_transpose (t_matrix4 matrix);

// Determinant functions
float matrix2_determinant (t_matrix2 m);
float matrix3_determinant (t_matrix3 m);
float matrix4_determinant (t_matrix4 m);
t_matrix3 submatrix4 (t_matrix4 m, int row, int col);
t_matrix2 submatrix3 (t_matrix3 m, int row, int col);
float minor3 (t_matrix3 m, int row, int col);
float minor4 (t_matrix4 m, int row, int col);
float cofactor (t_matrix3 m, int row, int col);
float cofactor4 (t_matrix4 m, int row, int col);

// Matrix inversion functions
bool isinvertible (t_matrix4 m);
t_matrix4 inverse (t_matrix4 m);

// Transformation functions
t_matrix4 translation (float x, float y, float z);
t_matrix4 scaling (float x, float y, float z);
t_matrix4 rotation_x (float radians);
t_matrix4 rotation_y (float radians);
t_matrix4 rotation_z (float radians);
t_matrix4 shearing (t_shear params);

// Fluent API for transformation chaining
typedef struct s_transform_builder
{
    t_matrix4 matrix;
} t_transform_builder;

t_transform_builder transform_identity (void);
t_transform_builder transform_translate (t_transform_builder builder, float x,
                                         float y, float z);
t_transform_builder transform_scale (t_transform_builder builder, float x,
                                     float y, float z);
t_transform_builder transform_rotate_x (t_transform_builder builder,
                                        float radians);
t_transform_builder transform_rotate_y (t_transform_builder builder,
                                        float radians);
t_transform_builder transform_rotate_z (t_transform_builder builder,
                                        float radians);
t_transform_builder transform_shear (t_transform_builder builder,
                                     t_shear params);
t_matrix4 transform_build (t_transform_builder builder);

// Ray operations
t_ray create_ray (t_tuple origin, t_tuple direction);
t_tuple position(t_ray ray, float t);

#endif
//
