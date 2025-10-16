/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaeed < tsaeed@student.42amman.com >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 12:42:11 by tsaeed            #+#    #+#             */
/*   Updated: 2025/10/15 19:20:14 by tsaeed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_ray
create_ray (t_tuple origin, t_tuple direction)
{
    t_ray ray;

    ray.origin = origin;
    ray.direction = direction;

    return (ray);
}

t_tuple
position (t_ray ray, float t)
{
    t_tuple scaled_directon;

    scaled_directon = ft_multuple (ray.direction, t);
    scaled_directon = ft_addtuple (ray.origin, scaled_directon);

    return (scaled_directon);
}

t_ray   transform (t_ray ray, t_matrix4 matrix)
{
    t_ray transformed_ray;

    transformed_ray.origin = matrix4_multiply_tuple (matrix, ray.origin);
    transformed_ray.direction = matrix4_multiply_tuple (matrix, ray.direction);
    return (transformed_ray);
}
