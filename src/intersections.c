/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaeed < tsaeed@student.42amman.com >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 00:00:00 by tsaeed            #+#    #+#             */
/*   Updated: 2025/10/15 18:29:24 by tsaeed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_intersection  intersection (float t, t_sphere object)
{
    t_intersection i;

    i.t = t;
    i.object = object;
    return (i);
}

static void sort_intersections (t_intersections *result)
{
    int i;
    int j;
    t_intersection temp;

    i = 0;
    while (i < result->count - 1)
        {
            j = 0;
            while (j < result->count - i - 1)
                {
                    if (result->xs[j].t > result->xs[j + 1].t)
                        {
                            temp = result->xs[j];
                            result->xs[j] = result->xs[j + 1];
                            result->xs[j + 1] = temp;
                        }
                    j++;
                }
            i++;
        }
}

static void fill_intersections (t_intersections *result, int count, va_list args)
{
    int i;

    i = 0;
    while (i < count)
        {
            result->xs[i] = va_arg (args, t_intersection);
            i++;
        }
}

t_intersections intersections (int count, ...)
{
    t_intersections result;
    va_list args;

    result.count = count;
    va_start (args, count);
    fill_intersections (&result, count, args);
    va_end (args);
    sort_intersections (&result);
    return (result);
}

int hit (t_intersections xs, t_intersection *result)
{
    int i;

    i = 0;
    while (i < xs.count)
        {
            if (xs.xs[i].t >= 0)
                {
                    *result = xs.xs[i];
                    return (1);
                }
            i++;
        }
    return (0);
}
