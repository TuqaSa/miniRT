/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transformations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaeed < tsaeed@student.42amman.com >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 23:50:00 by tsaeed            #+#    #+#             */
/*   Updated: 2025/10/13 07:17:54 by tsaeed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include <math.h>

/**
 * Creates a 4x4 translation matrix
 * Translation moves points by adding x, y, z to their coordinates
 * Vectors are unaffected because their w component is 0
 * @param x: Amount to translate in x direction
 * @param y: Amount to translate in y direction
 * @param z: Amount to translate in z direction
 * @return: 4x4 translation matrix
 */
t_matrix4
translation (float x, float y, float z)
{
    t_matrix4 matrix;

    matrix = matrix4_identity ();
    /* Set translation values */
    matrix.m[0][3] = x; /* x translation */
    matrix.m[1][3] = y; /* y translation */
    matrix.m[2][3] = z; /* z translation */
    return (matrix);
}

/**
 * Creates a 4x4 scaling matrix
 * Scaling multiplies coordinates by x, y, z factors
 * Unlike translation, scaling affects both points and vectors
 * @param x: Scaling factor for x coordinate
 * @param y: Scaling factor for y coordinate
 * @param z: Scaling factor for z coordinate
 * @return: 4x4 scaling matrix
 */
t_matrix4
scaling (float x, float y, float z)
{
    t_matrix4 matrix;

    matrix = matrix4_create ();
    /* Set scaling values on the diagonal */
    matrix.m[0][0] = x;   /* x scaling */
    matrix.m[1][1] = y;   /* y scaling */
    matrix.m[2][2] = z;   /* z scaling */
    matrix.m[3][3] = 1.0; /* homogeneous coordinate (always 1) */
    return (matrix);
}

/**
 * Creates a 4x4 rotation matrix for rotation around the X axis
 * Rotation follows left-hand rule: point thumb along +X axis, fingers curl
 * in rotation direction
 * @param radians: Angle to rotate in radians (positive = clockwise when
 * looking along +X axis)
 * @return: 4x4 rotation matrix around X axis
 */
t_matrix4
rotation_x (float radians)
{
    t_matrix4 matrix;
    float cos_r;
    float sin_r;

    cos_r = cos (radians);
    sin_r = sin (radians);
    matrix = matrix4_identity ();
    /* Set rotation values (X axis rotation matrix) */
    matrix.m[1][1] = cos_r;  /* cos(r) */
    matrix.m[1][2] = -sin_r; /* -sin(r) */
    matrix.m[2][1] = sin_r;  /* sin(r) */
    matrix.m[2][2] = cos_r;  /* cos(r) */
    return (matrix);
}

/**
 * Creates a 4x4 rotation matrix for rotation around the Y axis
 * Rotation follows left-hand rule: point thumb along +Y axis, fingers curl
 * in rotation direction
 * @param radians: Angle to rotate in radians (positive = clockwise when
 * looking along +Y axis)
 * @return: 4x4 rotation matrix around Y axis
 */
t_matrix4
rotation_y (float radians)
{
    t_matrix4 matrix;
    float cos_r;
    float sin_r;

    cos_r = cos (radians);
    sin_r = sin (radians);
    matrix = matrix4_identity ();
    /* Set rotation values (Y axis rotation matrix) */
    matrix.m[0][0] = cos_r;  /* cos(r) */
    matrix.m[0][2] = sin_r;  /* sin(r) */
    matrix.m[2][0] = -sin_r; /* -sin(r) */
    matrix.m[2][2] = cos_r;  /* cos(r) */
    return (matrix);
}

/**
 * Creates a 4x4 rotation matrix for rotation around the Z axis
 * Rotation follows left-hand rule: point thumb along +Z axis, fingers curl
 * in rotation direction
 * @param radians: Angle to rotate in radians (positive = clockwise when
 * looking along +Z axis)
 * @return: 4x4 rotation matrix around Z axis
 */
t_matrix4
rotation_z (float radians)
{
    t_matrix4 matrix;
    float cos_r;
    float sin_r;

    cos_r = cos (radians);
    sin_r = sin (radians);
    matrix = matrix4_identity ();
    /* Set rotation values (Z axis rotation matrix) */
    matrix.m[0][0] = cos_r;  /* cos(r) */
    matrix.m[0][1] = -sin_r; /* -sin(r) */
    matrix.m[1][0] = sin_r;  /* sin(r) */
    matrix.m[1][1] = cos_r;  /* cos(r) */
    return (matrix);
}

/**
 * Creates a 4x4 shearing matrix
 * Shearing transforms each component in proportion to the other two components
 * @param params: Structure containing all 6 shearing parameters
 *   params.xy: x in proportion to y (how much to move x based on y value)
 *   params.xz: x in proportion to z (how much to move x based on z value)
 *   params.yx: y in proportion to x (how much to move y based on x value)
 *   params.yz: y in proportion to z (how much to move y based on z value)
 *   params.zx: z in proportion to x (how much to move z based on x value)
 *   params.zy: z in proportion to y (how much to move z based on y value)
 * @return: 4x4 shearing matrix
 */
t_matrix4
shearing (t_shear params)
{
    t_matrix4 matrix;

    matrix = matrix4_identity ();
    /* Set shearing values */
    matrix.m[0][1] = params.xy; /* x in proportion to y */
    matrix.m[0][2] = params.xz; /* x in proportion to z */
    matrix.m[1][0] = params.yx; /* y in proportion to x */
    matrix.m[1][2] = params.yz; /* y in proportion to z */
    matrix.m[2][0] = params.zx; /* z in proportion to x */
    matrix.m[2][1] = params.zy; /* z in proportion to y */
    return (matrix);
}

/* ========================================================================= */
/* FLUENT API FOR TRANSFORMATION CHAINING                                   */
/* ========================================================================= */

/**
 * Creates a new transformation builder starting with identity matrix
 * This is the entry point for fluent API transformation chaining
 * @return: Transform builder initialized with identity matrix
 */
t_transform_builder
transform_identity (void)
{
    t_transform_builder builder;

    builder.matrix = matrix4_identity ();
    return (builder);
}

/**
 * Chains a translation transformation to the current builder
 * @param builder: Current transformation builder
 * @param x: Translation amount in x direction
 * @param y: Translation amount in y direction
 * @param z: Translation amount in z direction
 * @return: Updated transformation builder with translation applied
 */
t_transform_builder
transform_translate (t_transform_builder builder, float x, float y, float z)
{
    t_matrix4 translation_matrix;

    translation_matrix = translation (x, y, z);
    builder.matrix = matrix4_multiply (translation_matrix, builder.matrix);
    return (builder);
}

/**
 * Chains a scaling transformation to the current builder
 * @param builder: Current transformation builder
 * @param x: Scaling factor for x coordinate
 * @param y: Scaling factor for y coordinate
 * @param z: Scaling factor for z coordinate
 * @return: Updated transformation builder with scaling applied
 */
t_transform_builder
transform_scale (t_transform_builder builder, float x, float y, float z)
{
    t_matrix4 scaling_matrix;

    scaling_matrix = scaling (x, y, z);
    builder.matrix = matrix4_multiply (scaling_matrix, builder.matrix);
    return (builder);
}

/**
 * Chains an X-axis rotation to the current builder
 * @param builder: Current transformation builder
 * @param radians: Angle to rotate around X-axis in radians
 * @return: Updated transformation builder with X rotation applied
 */
t_transform_builder
transform_rotate_x (t_transform_builder builder, float radians)
{
    t_matrix4 rotation_matrix;

    rotation_matrix = rotation_x (radians);
    builder.matrix = matrix4_multiply (rotation_matrix, builder.matrix);
    return (builder);
}

/**
 * Chains a Y-axis rotation to the current builder
 * @param builder: Current transformation builder
 * @param radians: Angle to rotate around Y-axis in radians
 * @return: Updated transformation builder with Y rotation applied
 */
t_transform_builder
transform_rotate_y (t_transform_builder builder, float radians)
{
    t_matrix4 rotation_matrix;

    rotation_matrix = rotation_y (radians);
    builder.matrix = matrix4_multiply (rotation_matrix, builder.matrix);
    return (builder);
}

/**
 * Chains a Z-axis rotation to the current builder
 * @param builder: Current transformation builder
 * @param radians: Angle to rotate around Z-axis in radians
 * @return: Updated transformation builder with Z rotation applied
 */
t_transform_builder
transform_rotate_z (t_transform_builder builder, float radians)
{
    t_matrix4 rotation_matrix;

    rotation_matrix = rotation_z (radians);
    builder.matrix = matrix4_multiply (rotation_matrix, builder.matrix);
    return (builder);
}

/**
 * Chains a shearing transformation to the current builder
 * @param builder: Current transformation builder
 * @param params: Shearing parameters structure
 * @return: Updated transformation builder with shearing applied
 */
t_transform_builder
transform_shear (t_transform_builder builder, t_shear params)
{
    t_matrix4 shearing_matrix;

    shearing_matrix = shearing (params);
    builder.matrix = matrix4_multiply (shearing_matrix, builder.matrix);
    return (builder);
}

/**
 * Extracts the final transformation matrix from the builder
 * @param builder: Transformation builder to extract matrix from
 * @return: Final combined transformation matrix
 */
t_matrix4
transform_build (t_transform_builder builder)
{
    return (builder.matrix);
}
