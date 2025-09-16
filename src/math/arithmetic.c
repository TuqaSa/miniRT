/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arithmetic.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaeed < tsaeed@student.42amman.com >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 21:33:46 by tsaeed            #+#    #+#             */
/*   Updated: 2025/09/15 21:33:47 by tsaeed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_tuple	ft_addtuple(t_tuple a, t_tuple b)
{
	t_tuple	c;

	if (a.w == 1.0f && b.w == 1.0f)
	{
		perror("Warning: Attempting to add two points is mathematically "
				"invalid\n");
		return ((t_tuple){0, 0, 0, 0});
	}
	c.x = a.x + b.x;
	c.y = a.y + b.y;
	c.z = a.z + b.z;
	c.w = a.w + b.w;
	return (c);
}
t_tuple	ft_subtuple(t_tuple a, t_tuple b)
{
	t_tuple	c;

	c.x = a.x - b.x;
	c.y = a.y - b.y;
	c.z = a.z - b.z;
	c.w = a.w - b.w;
	return (c);
}

t_tuple	ft_negtuple(t_tuple a)
{
	t_tuple	c;

	c.x = -a.x;
	c.y = -a.y;
	c.z = -a.z;
	c.w = -a.w;
	return (c);
}
t_tuple	ft_multuple(t_tuple a, float b)
{
	t_tuple	c;

	c.x = a.x * b;
	c.y = a.y * b;
	c.z = a.z * b;
	c.w = a.w * b;
	return (c);
}

t_tuple	ft_divtuple(t_tuple a, float b)
{
	t_tuple	c;

	if (b == 0.0f)
	{
		perror("Error: Division by zero\n");
		return ((t_tuple){0, 0, 0, 0});
	}
	c.x = a.x / b;
	c.y = a.y / b;
	c.z = a.z / b;
	c.w = a.w / b;
	return (c);
}
