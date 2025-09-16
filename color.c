/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaeed < tsaeed@student.42amman.com >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 22:12:12 by tsaeed            #+#    #+#             */
/*   Updated: 2025/09/15 22:13:16 by tsaeed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_color	color(float r, float g, float b)
{
	t_color	col;

	col.r = r;
	col.g = g;
	col.b = b;
	return (col);
}

t_color	addcolor(t_color a, t_color b)
{
	t_color	c;

	c.r = a.r + b.r;
	c.g = a.g + b.g;
	c.b = a.b + b.b;
	return (c);
}
t_color	subcolor(t_color a, t_color b)
{
	t_color	c;

	c.r = a.r - b.r;
	c.g = a.g - b.g;
	c.b = a.b - b.b;
	return (c);
}
t_color	multcolor(t_color a, float b)
{
	t_color	c;

	c.r = a.r * b;
	c.g = a.g * b;
	c.b = a.b * b;
	return (c);
}
t_color	hadamard(t_color a, t_color b)
{
	t_color	c;

	c.r = a.r * b.r;
	c.g = a.g * b.g;
	c.b = a.b * b.b;
	return (c);
}
