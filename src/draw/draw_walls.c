/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_walls.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuzmenk <akuzmenk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 12:08:27 by akuzmenk          #+#    #+#             */
/*   Updated: 2024/01/15 19:00:55 by akuzmenk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

float	fix_fisheye(t_data *data)
{
	float	ca;

	ca = data->rays->ra - data->player->p_angle;
	if (ca < 0)
	{
		ca += 2 * PI;
	}
	if (ca > 2 * PI)
	{
		ca -= 2 * PI;
	}
	return (ca);
}

void	set_walls_size(t_data *data)
{
	float	ca;

	if (data->rays->dis_h < data->rays->dis_v)
	{
		data->textures_data->tex_x = fmod(data->rays->rx, data->map->x_len);
	}
	else
	{
		data->textures_data->tex_x = fmod(data->rays->ry, data->map->x_len);
	}
	data->textures_data->tex_x = data->textures_data->tex_x \
	/ data->map->x_len * data->textures_data->tex->tex_width;
	ca = fix_fisheye(data);
	data->rays->dis_fin = data->rays->dis_fin * cos(ca);
	data->textures_data->tex_height = data->map->y_len \
	* (WINDOW_HEIGHT / 2 * 3) / (data->rays->dis_fin - 1);
	data->textures_data->wall_bottom = (WINDOW_HEIGHT / 2) \
	+ (data->textures_data->tex_height / 2);
	data->textures_data->wall_top = (WINDOW_HEIGHT / 2) \
	- (data->textures_data->tex_height / 2);
	data->rays->ry = data->textures_data->wall_top;
	data->textures_data->draw_end = data->textures_data->x \
	+ (WINDOW_WIDTH / FOV);
}

void	help_init_draw_walls(t_data *data)
{
	data->textures_data->offs = (float) data->textures_data->tex->tex_height \
	/ (float)data->textures_data->tex_height;
	data->textures_data->tex_yi = 0;
	data->rays->ry = data->textures_data->wall_top;
	data->textures_data->tex_xi = (int) data->textures_data->tex_x;
	data->textures_data->mod_ofs = 0;
}

static void	help_draw_walls(t_data *data)
{
	data->textures_data->tex_x += (data->textures_data->offs / 2);
	if (data->textures_data->tex_x > data->textures_data->tex->tex_width)
		data->textures_data->tex_x = 0;
}

void	draw_walls(t_data *data, int number_rays)
{
	help_init_draw_walls(data);
	while (data->rays->ry > -1 * HUGE_NUMBER && data->rays->ry < WINDOW_HEIGHT \
	&& data->rays->ry <= data->textures_data->wall_bottom)
	{
		if (data->textures_data->tex_xi >= data->textures_data->tex->tex_width)
			data->textures_data->tex_xi = 0;
		if (data->textures_data->tex_yi >= data->textures_data->tex->tex_height)
			data->textures_data->tex_yi = 0;
		if (data->rays->rx >= 0 && data->rays->ry >= 0 \
		&& data->rays->rx < WINDOW_WIDTH && data->rays->ry < WINDOW_HEIGHT)
			my_mlx_pixel_put(data->img, number_rays, data->rays->ry, \
			data->textures_data->tex->tex_data[data->textures_data->tex_yi] \
			[data->textures_data->tex_xi]);
		data->rays->ry++;
		if (data->textures_data->mod_ofs < 1)
			data->textures_data->mod_ofs = data->textures_data->mod_ofs \
			+ data->textures_data->offs;
		else
		{
			data->textures_data->tex_yi += (int)data->textures_data->mod_ofs;
			data->textures_data->mod_ofs = data->textures_data->offs \
			+ fmod(data->textures_data->mod_ofs, 1);
		}
	}
	help_draw_walls(data);
}
