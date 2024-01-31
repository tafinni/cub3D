/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda_algorithm.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfinni <tfinni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 11:25:30 by akuzmenk          #+#    #+#             */
/*   Updated: 2024/01/03 15:59:10 by tfinni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	fix_ray_len_overflow(t_data *data)
{
	if (data->rays->rx < 0 || data->rays->rx > WINDOW_WIDTH)
	{
		data->rays->rx = data->player->x;
	}
	if (data->rays->ry < 0 || data->rays->ry > WINDOW_HEIGHT)
	{
		data->rays->ry = data->player->y;
	}
}

float	ray_distance(t_data *data)
{
	float	distance;

	distance = sqrt((data->rays->rx - data->player->x) \
	* (data->rays->rx - data->player->x) + (data->rays->ry - data->player->y) \
	* (data->rays->ry - data->player->y));
	return (distance);
}

void	check_a_wall(t_data *data, char flag_vertical_horizontal)
{
	data->rays->dof = 8;
	if (flag_vertical_horizontal == 'v')
	{
		data->rays->vertical_x = data->rays->rx;
		data->rays->vertical_y = data->rays->ry;
		data->rays->dis_v = ray_distance(data);
	}
	if (flag_vertical_horizontal == 'h')
	{
		data->rays->horizontal_x = data->rays->rx;
		data->rays->horizontal_y = data->rays->ry;
		data->rays->dis_h = ray_distance(data);
	}
}

void	check_hit_with_dda(t_data *data, char flag_v_h)
{
	while (data->rays->dof < 8 && data->rays->rx >= 0 && data->rays->ry >= 0)
	{
		if (data->rays->ry >= data->map->y_len * GRID_SIZE && flag_v_h == 'v')
			data->rays->ry = data->map->y_len * GRID_SIZE - 0.00001;
		if (data->rays->ry >= data->map->y_len * GRID_SIZE && flag_v_h == 'h')
			data->rays->ry = data->map->y_len * GRID_SIZE - 0.5;
		data->rays->mx = (int) data->rays->rx / GRID_SIZE;
		data->rays->my = (int) data->rays->ry / GRID_SIZE;
		data->rays->mp = data->rays->my * data->map->x_len + data->rays->mx;
		if (data->rays->my < data->map->y_len && data->rays->mx < \
		data->map->x_len && data->rays->mp < data->map->x_len * \
		data->map->y_len && data->map->map[data->rays->my] \
		[data->rays->mx] == '1' && data->rays->mx >= 0 && data->rays->my >= 0)
			check_a_wall(data, flag_v_h);
		else
		{
			data->rays->rx += data->rays->xo;
			data->rays->ry += data->rays->yo;
		}
		if (data->rays->rx > WINDOW_WIDTH || data->rays->ry > WINDOW_HEIGHT)
			break ;
	}
	fix_ray_len_overflow(data);
}
