/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaeed < tsaeed@student.42amman.com >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 13:40:28 by tsaeed            #+#    #+#             */
/*   Updated: 2025/10/15 18:27:26 by tsaeed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_sphere
sphere (void)
{
    static int next_id = 1;
    t_sphere s;

    s.id = next_id++;
    s.center = point (0, 0, 0);
    s.radius = 1.0;

    return (s);
}

/**
 * Calculates the discriminant for ray-sphere intersection
 * Uses quadratic formula discriminant: b² - 4ac
 * @param sphere: The sphere to intersect with
 * @param ray: The ray to test intersection
 * @return: Discriminant value (negative = no intersection)
 */
static float
calculate_discriminant (t_sphere sphere, t_ray ray)
{
    t_tuple sphere_to_ray;
    float a;
    float b;
    float c;

    sphere_to_ray = ft_subtuple (ray.origin, sphere.center);
    a = dot (ray.direction, ray.direction);
    b = 2 * dot (ray.direction, sphere_to_ray);
    c = dot (sphere_to_ray, sphere_to_ray) - (sphere.radius * sphere.radius);
    return (b * b - 4 * a * c);
}

/**
 * Calculates intersection t values when discriminant is non-negative
 * @param ray: The ray being tested
 * @param discriminant: Pre-calculated discriminant value
 * @param t1: Pointer to store first intersection t value
 * @param t2: Pointer to store second intersection t value
 */
static void
calculate_t_values (t_ray ray, float discriminant, float *t1, float *t2)
{
    t_tuple sphere_to_ray;
    float a;
    float b;
    float sqrt_discriminant;

    sphere_to_ray = ft_subtuple (ray.origin, point (0, 0, 0));
    a = dot (ray.direction, ray.direction);
    b = 2 * dot (ray.direction, sphere_to_ray);
    sqrt_discriminant = sqrt (discriminant);
    *t1 = (-b - sqrt_discriminant) / (2 * a);
    *t2 = (-b + sqrt_discriminant) / (2 * a);
}

/**
 * Finds intersections between a ray and a sphere
 * Returns collection of intersection points with t values
 * @param sphere: The sphere to intersect with
 * @param ray: The ray to test intersection
 * @return: Intersections structure containing count and t values
 */
t_intersections
intersect (t_sphere sphere, t_ray ray)
{
    t_intersections result;
    float discriminant;
    float t1;
    float t2;

    discriminant = calculate_discriminant (sphere, ray);
    if (discriminant < 0)
        {
            result.count = 0;
        }
    else
        {
            calculate_t_values (ray, discriminant, &t1, &t2);
            result.count = 2;
            result.xs[0].t = t1;
            result.xs[0].object = sphere;
            result.xs[1].t = t2;
            result.xs[1].object = sphere;
        }
    return (result);
}
