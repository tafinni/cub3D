/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_caster.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuzmenk <akuzmenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 12:07:57 by akuzmenk          #+#    #+#             */
/*   Updated: 2024/01/02 15:02:32 by akuzmenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	create_horizontal_ray(t_data *data)
{
	if (data->rays->ra < PI)
	{
		data->rays->ry = ((int)data->player->y - \
		(int)data->player->y % GRID_SIZE) - 0.0001;
		data->rays->rx = (data->player->y - data->rays->ry) \
		* data->rays->a_tan + data->player->x;
		data->rays->yo = -GRID_SIZE;
		data->rays->xo = -data->rays->yo * data->rays->a_tan;
	}
	if (data->rays->ra > PI)
	{
		data->rays->ry = ((int)data->player->y - \
		(int)data->player->y % GRID_SIZE) + GRID_SIZE;
		data->rays->rx = (data->player->y - data->rays->ry) \
		* data->rays->a_tan + data->player->x;
		data->rays->yo = GRID_SIZE;
		data->rays->xo = -data->rays->yo * data->rays-> a_tan;
	}
	if (data->rays->ra == 0 || data->rays->ra == PI)
	{
		data->rays->rx = data->player->x;
		data->rays->ry = data->player->y;
		data->rays->dof = 8;
	}
	check_hit_with_dda(data, 'h');
}

void	create_vertical_ray(t_data *data)
{
	if (data->rays->ra < PI / 2 || data->rays->ra > 3 * PI / 2)
	{
		data->rays->rx = (int)data->player->x - \
		(int)data->player->x % GRID_SIZE - 0.0001;
		data->rays->ry = (data->player->x - data->rays->rx) \
		* data->rays->n_tan + data->player->y;
		data->rays->xo = -GRID_SIZE;
		data->rays->yo = -data->rays->xo * data->rays->n_tan;
	}
	if (data->rays->ra > PI / 2 && data->rays->ra < PI * 3 / 2)
	{
		data->rays->rx = ((int)data->player->x - \
		(int)data->player->x % GRID_SIZE) + GRID_SIZE;
		data->rays->ry = (data->player->x - data->rays->rx) \
		* data->rays->n_tan + data->player->y;
		data->rays->xo = GRID_SIZE;
		data->rays->yo = -data->rays->xo * data->rays->n_tan;
	}
	if (data->rays->ra == 0 || data->rays->ra == PI)
	{
		data->rays->rx = data->player->x;
		data->rays->ry = data->player->y;
		data->rays->dof = 8;
	}
	check_hit_with_dda(data, 'v');
}

void	choose_wall_texture(t_data *data)
{
	if (data->rays->dis_h < data->rays->dis_v)
	{
		data->rays->dis_fin = data->rays->dis_h;
		data->rays->rx = data->rays->horizontal_x;
		data->rays->ry = data->rays->horizontal_y;
		if (data->player->y < data->rays->ry)
			data->textures_data->tex = &data->south;
		else
			data->textures_data->tex = &data->north;
		return ;
	}
	else if (data->rays->dis_v < data->rays->dis_h)
	{
		data->rays->dis_fin = data->rays->dis_v;
		data->rays->rx = data->rays->vertical_x;
		data->rays->ry = data->rays->vertical_y;
		if (data->player->x < data->rays->rx)
			data->textures_data->tex = &data->east;
		else
			data->textures_data->tex = &data->west;
		return ;
	}
}

void	run_raycaster(t_data *data)
{
	data->rays->dof = 0;
	data->rays->a_tan = -1 / tan(data->rays->ra);
	data->rays->horizontal_x = data->player->x;
	data->rays->horizontal_y = data->player->y;
	data->rays->dis_h = HUGE_NUMBER;
	create_horizontal_ray(data);
	data->rays->dof = 0;
	data->rays->n_tan = -tan(data->rays->ra);
	data->rays->dis_v = HUGE_NUMBER;
	data->rays->vertical_x = data->player->x;
	data->rays->vertical_y = data->player->y;
	create_vertical_ray(data);
	choose_wall_texture(data);
}

void	start_raycaster(t_data *data)
{
	int		number_rays;
	float	delta_angles;

	number_rays = 0;
	init_rays(data->rays);
	delta_angles = FOV * DEG_TO_RAD / WINDOW_WIDTH;
	data->rays->ra = data->player->p_angle - (DEG_TO_RAD * FOV / 2);
	if (data->rays->ra < 0)
		data->rays->ra += 2 * PI;
	if (data->rays->ra > 2 * PI)
		data->rays->ra -= 2 * PI;
	while (number_rays < WINDOW_WIDTH)
	{
		run_raycaster(data);
		set_walls_size(data);
		draw_walls(data, number_rays);
		data->rays->ra += delta_angles;
		if (data->rays->ra < 0)
			data->rays->ra += 2 * PI;
		if (data->rays->ra > 2 * PI)
			data->rays->ra -= 2 * PI;
		number_rays++;
	}
}
