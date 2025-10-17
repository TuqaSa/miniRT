/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaeed < tsaeed@student.42amman.com >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 21:20:13 by tsaeed            #+#    #+#             */
/*   Updated: 2025/10/17 23:31:34 by tsaeed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_tuple
normal_at (t_sphere sphere, t_tuple world_point)
{
    t_matrix4 inverse_transform;
    t_tuple object_point;
    t_tuple object_normal;
    t_matrix4 transpose_inverse;
    t_tuple world_normal;

    inverse_transform = inverse (sphere.transform);
    object_point = matrix4_multiply_tuple (inverse_transform, world_point);
    object_normal = ft_subtuple (object_point, point (0, 0, 0));
    transpose_inverse = matrix4_transpose (inverse_transform);
    world_normal = matrix4_multiply_tuple (transpose_inverse, object_normal);
    world_normal.w = 0;
    return (normalize (world_normal));
}
