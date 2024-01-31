/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_caster_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuzmenk <akuzmenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 17:38:59 by akuzmenk          #+#    #+#             */
/*   Updated: 2024/01/02 17:39:25 by akuzmenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	init_rays(t_rays *rays)
{
	rays->mp = 0;
	rays->mx = 0;
	rays->my = 0;
	rays->dof = 0;
	rays->rx = 0;
	rays->ry = 0;
	rays->ra = 0;
	rays->xo = 0;
	rays->yo = 0;
	rays->horizontal_x = 0;
	rays->horizontal_y = 0;
	rays->vertical_x = 0;
	rays->vertical_y = 0;
	rays->dis_v = 0;
	rays->dis_h = 0;
	rays->dis_fin = 0;
	rays->a_tan = 0;
	rays->n_tan = 0;
}
