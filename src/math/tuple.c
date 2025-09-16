/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tuple.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaeed < tsaeed@student.42amman.com >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 21:21:08 by tsaeed            #+#    #+#             */
/*   Updated: 2025/09/15 21:33:39 by tsaeed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_tuple	point(float x, float y, float z)
{
	t_tuple	p;

	p.x = x;
	p.y = y;
	p.z = z;
	p.w = 1.0;
	return (p);
}

t_tuple	vector(float x, float y, float z)
{
	t_tuple	v;

	v.x = x;
	v.y = y;
	v.z = z;
	v.w = 0.0;
	return (v);
}
void	print_value(t_tuple p)
{
	printf("x = %f, y = %f, z = %f , w = %f\n", p.x, p.y, p.z, p.w);
}

bool	ft_fequal(float a, float b)
{
	return (fabs(a - b) < EPSILON);
}

bool	ft_tequal(t_tuple a, t_tuple b)
{
	if (!ft_fequal(a.x, b.x))
		return (false);
	if (!ft_fequal(a.y, b.y))
		return (false);
	if (!ft_fequal(a.z, b.z))
		return (false);
	if (!ft_fequal(a.w, b.w))
		return (false);
	return (true);
}
