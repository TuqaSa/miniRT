/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsaeed < tsaeed@student.42amman.com >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 21:38:20 by tsaeed            #+#    #+#             */
/*   Updated: 2025/09/15 22:08:27 by tsaeed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_projectile
tick (t_environment env, t_projectile proj)
{
    t_tuple new_position;
    t_tuple new_velocity;

    new_position = ft_addtuple (proj.position, proj.velocity);
    new_velocity
        = ft_addtuple (proj.velocity, ft_addtuple (env.gravity, env.wind));
    return ((t_projectile){ new_position, new_velocity });
}

t_projectile
create_projectile (t_tuple position, t_tuple velocity)
{
    return ((t_projectile){ position, velocity });
}

t_environment
create_environment (t_tuple gravity, t_tuple wind)
{
    return ((t_environment){ gravity, wind });
}

void
print_projectile (t_projectile proj)
{
    printf ("Projectile:\n");
    printf ("  Position: ");
    print_value (proj.position);
    printf ("  Velocity: ");
    print_value (proj.velocity);
}

void
print_environment (t_environment env)
{
    printf ("Environment:\n");
    printf ("  Gravity: ");
    print_value (env.gravity);
    printf ("  Wind: ");
    print_value (env.wind);
}
