/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaeed < tsaeed@student.42amman.com >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 21:33:41 by tsaeed            #+#    #+#             */
/*   Updated: 2025/09/15 22:08:25 by tsaeed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

float
magnitude (t_tuple v)
{
    float mag;

    mag = sqrt (v.x * v.x + v.y * v.y + v.z * v.z);
    return (mag);
}

t_tuple
normalize (t_tuple v)
{
    t_tuple norm;
    float mag;

    mag = magnitude (v);
    if (mag < EPSILON)
        {
            perror ("Warning: Attempting to normalize a zero vector\n");
            return ((t_tuple){ 0, 0, 0, 0 });
        }
    norm = ft_divtuple (v, mag);
    return (norm);
}

float
dot (t_tuple a, t_tuple b)
{
    float dot_product;

    dot_product = a.x * b.x + a.y * b.y + a.z * b.z;
    return (dot_product);
}

t_tuple
cross (t_tuple a, t_tuple b)
{
    t_tuple cross_product;

    cross_product.x = a.y * b.z - a.z * b.y;
    cross_product.y = a.z * b.x - a.x * b.z;
    cross_product.z = a.x * b.y - a.y * b.x;
    cross_product.w = 0.0;
    return (cross_product);
}

t_tuple
reflect (t_tuple incident, t_tuple normal)
{
    t_tuple reflected;
    float dot_product;

    dot_product = dot (incident, normal);
    reflected
        = ft_subtuple (incident, ft_multuple (normal, 2.0f * dot_product));
    return (reflected);
}
